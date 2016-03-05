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
        m_isCompiled( false ) {}

    Engine::~Engine() {}

    bool	Engine::compile( const QString & path ) {
        detail::Parser parser;
        bool result = parser.parse( path );
        if( !result ) {
            m_lastError = parser.getLastError();
            return false;
        }

        m_isCompiled = true;
        m_compiledPath = path;

        prepareDB();

        m_report = parser.getReport();
        return true;
    }

    bool	Engine::setParameters( const QMap< QString, QString > & map ) {
        if( m_report.isNull() ) {
            m_lastError = "Report is empty. Please create report from compile()";
            return false;
        }

        auto detail = m_report->getDetail();
        if( detail.isNull() ) {
            m_lastError = "Report->Detail is empty. Please create report from compile()";
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
            m_lastError = "Report is empty. Please create report from compile()";
            return false;
        }

        ConverterToPDF converter( m_report );
        auto result = converter.convert( path );
        if( !result ) {
            m_lastError = converter.getLastError();
            return false;
        }

        return true;
    }

    bool	Engine::createHTML( const QString & path ) {
        if( m_report.isNull() ) {
            m_lastError = "Report is empty. Please create report from compile()";
            return false;
        }

        ConverterToHTML converter( m_report );
        auto result = converter.convert( path );
        if( !result ) {
            m_lastError = converter.getLastError();
            return false;
        }

        return true;
    }

    const QWidgetPtr	Engine::createWidget() {
        if( m_report.isNull() ) {
            m_lastError = "Report is empty. Please create report from compile()";
            return QWidgetPtr();
        }

        ConverterToQWidget converter( m_report );
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
        QRectF rect = printer->pageRect();
        QPainter painter( printer );
        double xscale = rect.width() / m_widget->width();
        double yscale = rect.height() / m_widget->height();
        double scale = std::min( xscale, yscale );
        painter.translate(
            0, rect.height() / 2 - scale * m_widget->height() / 2
            );
        painter.scale( scale, scale );
        m_widget->render( &painter );
    }

    void    Engine::prepareDB() {
        QMapIterator <QString, QString> queriesIterator( m_dbQueries );

        while( queriesIterator.hasNext() ) {
            queriesIterator.next();
            m_processedDB.addExecutedQuery( queriesIterator.key(), executeQuery( queriesIterator.value() ) );
        }
    }

    QSqlQueryModelPtr   Engine::executeQuery( const QString &query ) {
        QSqlQueryModelPtr model( new QSqlQueryModel() );
        model->setQuery( query, m_dbConnection );
        return model;
    }

    bool			    Engine::isCompiled() const {
        return m_isCompiled;
    }

    const QString		Engine::getLastError() const {
        return m_lastError;
    }

}
