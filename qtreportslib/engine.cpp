#include <QPrintDialog>
#include <QPainter>
#include <QPrintPreviewWidget>
#include <QPrintPreviewDialog>
#include "converters/convertertopdf.hpp"
#include "converters/convertertohtml.hpp"
#include "engine.hpp"

namespace qtreports {

    Engine::Engine( QObject * parent ) :
        QObject( parent ),
        m_isOpened( false ) {}

    Engine::Engine( const QString & path, QObject * parent ) :
        Engine( parent ) {
        open( path );
    }

    Engine::~Engine() {}

    bool	Engine::open( const QString & path ) {
        detail::Parser parser;
        bool result = parser.parse( path );
        if( !result ) {
            m_isOpened = false;
            m_compiledPath.clear();
            m_report.clear();
            m_lastError = parser.getLastError();
            return false;
        }

        m_isOpened = true;
        m_compiledPath = path;

        prepareDB();

        m_report = parser.getReport();
        return true;
    }

    bool	Engine::setParameters( const QMap< QString, QString > & map ) {
        if( m_report.isNull() ) {
            m_lastError = "Report is empty. Please open report file";
            return false;
        }

        auto detail = m_report->getDetail();
        if( detail.isNull() ) {
            m_lastError = "Report->Detail is empty. Please open report file";
            return false;
        }

        for( auto && band : detail->getBands() ) {
            for( auto && textField : band->getTextFields() ) {
                auto text = textField->getText();
                text = text.replace( "\n", "" ).replace( "\r", "" ).replace( " ", "" );
                if( text.startsWith( "$P{" ) && text.contains( "}" ) ) {
                    auto name = text.split( "{" ).at( 1 ).split( "}" ).at( 0 );
                    textField->setText( map[ name ] );
                }
            }
        }

        return true;
    }

    bool	Engine::setConnection( const QSqlDatabase & connection ) {
        if( !connection.isOpen() ) {
            m_lastError = "Connection not open";
            return false;
        }

        m_dbConnection = connection;

        return true;
    }

    void Engine::addQuery( const QString & queryName, const QString & query ) {
        m_dbQueries[ queryName ] = query;
    }

    void Engine::addScript( const QString & script ) {
        m_scripts.append( script );
    }

    bool	Engine::createPDF( const QString & path ) {
        if( m_report.isNull() ) {
            m_lastError = "Report is empty. Please open report file";
            return false;
        }

        detail::ConverterToPDF converter( m_report );
        auto result = converter.convert( path );
        if( !result ) {
            m_lastError = converter.getLastError();
            return false;
        }

        return true;
    }

    bool	Engine::createHTML( const QString & path ) {
        if( m_report.isNull() ) {
            m_lastError = "Report is empty. Please open report file";
            return false;
        }

        detail::ConverterToHTML converter( m_report );
        auto result = converter.convert( path );
        if( !result ) {
            m_lastError = converter.getLastError();
            return false;
        }

        return true;
    }

    const QWidgetPtr	Engine::createWidget() {
        if( m_report.isNull() ) {
            m_lastError = "Report is empty. Please open report file";
            return QWidgetPtr();
        }

        detail::ConverterToQWidget converter( m_report );
        auto result = converter.convert();
        if( !result ) {
            m_lastError = converter.getLastError();
            return QWidgetPtr();
        }

        return converter.getQWidget();
    }

    bool	Engine::print() {
        QPrinter printer;

        QPrintPreviewDialog preview( &printer );
        connect(
            &preview, &QPrintPreviewDialog::paintRequested,
            this, &Engine::drawPreview
        );
        preview.exec();

        return true;
    }

    void	Engine::drawPreview( QPrinter * printer ) {
        auto widget = createWidget();
        if( widget.isNull() ) {
            return;
        }

        QRectF rect = printer->pageRect();
        QPainter painter( printer );
        qreal scale = rect.width() / widget->width();
        
        widget->resize( widget->width(), rect.height() / scale );
        painter.scale( scale, scale ); 

        painter.translate( 0, rect.height() / 2 - scale * widget->height() / 2 );
        widget->render( &painter );

        auto height = widget->height() * scale;
        int count = static_cast< int >( std::ceil( height / rect.height() ) );
        for( int i = 1; i < count; ++i ) {
            printer->newPage();
            painter.translate( 0, - height / count );
            widget->render( &painter );
        }
    }

    void    Engine::prepareDB() {
        QMapIterator <QString, QString> queriesIterator( m_dbQueries );

        while( queriesIterator.hasNext() ) {
            queriesIterator.next();
            m_processedDB.addExecutedQuery( queriesIterator.key(), executeQuery( queriesIterator.value() ) );
        }
    }

    detail::QSqlQueryModelPtr   Engine::executeQuery( const QString &query ) {
        detail::QSqlQueryModelPtr model( new QSqlQueryModel() );
        model->setQuery( query, m_dbConnection );
        return model;
    }

    bool			    Engine::isOpened() const {
        return m_isOpened;
    }

    const QString		Engine::getLastError() const {
        return m_lastError;
    }

}
