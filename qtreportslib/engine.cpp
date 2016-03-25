#include <QPrintDialog>
#include <QPainter>
#include <QPrintPreviewWidget>
#include <QPrintPreviewDialog>
#include "converters/convertertopdf.hpp"
#include "converters/convertertohtml.hpp"
#include "engine.hpp"

namespace qtreports
{

    Engine::Engine( QObject * parent ) :
        QObject( parent ),
        m_isOpened( false )
    {}

    Engine::Engine( const QString & path, QObject * parent ) :
        Engine( parent )
    {
        open( path );
    }

    Engine::~Engine() {}

    bool	Engine::open( const QString & path )
    {
        detail::Parser parser;
        bool result = parser.parse( path );
        if( !result )
        {
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

    bool	Engine::setParameters( const QMap< QString, QString > & map )
    {
        if( m_report.isNull() )
        {
            m_lastError = "Report is empty. Please open report file";
            return false;
        }

        auto detail = m_report->getDetail();
        if( detail.isNull() )
        {
            m_lastError = "Report->Detail is empty. Please open report file";
            return false;
        }

        for( auto && band : detail->getBands() )
        {
            for( auto && textField : band->getTextFields() )
            {
                auto text = textField->getText();
                text = text.replace( "\n", "" ).replace( "\r", "" ).replace( " ", "" );
                if( text.startsWith( "$P{" ) && text.contains( "}" ) )
                {
                    auto name = text.split( "{" ).at( 1 ).split( "}" ).at( 0 );
                    textField->setText( map[ name ] );
                }
            }
        }

        return true;
    }

    bool	Engine::setConnection( const QSqlDatabase & connection )
    {
        if( !connection.isOpen() )
        {
            m_lastError = "Connection not open";
            return false;
        }

        if( m_report.isNull() )
        {
            m_lastError = "Report is empty. Please open report file";
            return false;
        }

        m_dbConnection = connection;

        prepareDB();

        return true;
    }

    void Engine::addQuery( const QString & queryName, const QString & query )
    {
        m_dbQueries[ queryName ] = query;
    }

    void Engine::addScript( const QString & script )
    {
        m_scripts.append( script );
    }

    bool	Engine::createPDF( const QString & path )
    {
        if( m_report.isNull() )
        {
            m_lastError = "Report is empty. Please open report file";
            return false;
        }

        detail::ConverterToPDF converter( m_report );
        auto result = converter.convert( path );
        if( !result )
        {
            m_lastError = converter.getLastError();
            return false;
        }

        return true;
    }

    bool	Engine::createHTML( const QString & path )
    {
        if( m_report.isNull() )
        {
            m_lastError = "Report is empty. Please open report file";
            return false;
        }

        detail::ConverterToHTML converter( m_report );
        auto result = converter.convert( path );
        if( !result )
        {
            m_lastError = converter.getLastError();
            return false;
        }

        return true;
    }

    const QWidgetPtr	Engine::createWidget()
    {
        if( m_report.isNull() )
        {
            m_lastError = "Report is empty. Please open report file";
            return QWidgetPtr();
        }

        detail::ConverterToQWidget converter( m_report );
        auto result = converter.convert( detail::ConverterToQWidget::WidgetType::Report );
        if( !result )
        {
            m_lastError = converter.getLastError();
            return QWidgetPtr();
        }

        return converter.getQWidget();
    }

    const QWidgetPtr	Engine::createLayout()
    {
        if( m_report.isNull() )
        {
            m_lastError = "Report is empty. Please open report file";
            return QWidgetPtr();
        }

        detail::ConverterToQWidget converter( m_report );
        auto result = converter.convert( detail::ConverterToQWidget::WidgetType::Layout );
        if( !result )
        {
            m_lastError = converter.getLastError();
            return QWidgetPtr();
        }

        return converter.getQWidget();
    }

    bool	Engine::print()
    {
        QPrinter printer;

        m_printedWidget = createWidget();
        if( m_printedWidget.isNull() )
        {
            m_lastError = "Cannot create widget. Error: " + m_lastError;
            return false;
        }

        m_printedWidget->resize( 595, 595 );

        //Magic
        m_printedWidget->show();
        m_printedWidget->hide();

        QPrintPreviewDialog preview( &printer );
        connect(
            &preview, &QPrintPreviewDialog::paintRequested,
            this, &Engine::drawPreview
            );
        preview.exec();

        m_printedWidget.clear();

        return true;
    }

    void	Engine::drawPreview( QPrinter * printer )
    {
        if( m_printedWidget.isNull() )
        {
            return;
        }

        QRectF rect = printer->pageRect();
        QPainter painter( printer );
        qreal scale = rect.width() / m_printedWidget->width();

        m_printedWidget->resize( m_printedWidget->width(), rect.height() / scale );
        painter.scale( scale, scale );

        auto height = m_printedWidget->height() * scale;
        int count = static_cast< int >( std::ceil( height / rect.height() ) );
        for( int i = 0; i < count; ++i )
        {
            i != 0 ? printer->newPage() : 0;
            m_printedWidget->render( &painter, QPoint( 0, - i * rect.height() / scale ) );
        }
    }

    void    Engine::prepareDB()
    {
        QMapIterator <QString, QString> queriesIterator( m_dbQueries );

        while( queriesIterator.hasNext() )
        {
            queriesIterator.next();
            m_processedDB.addExecutedQuery( queriesIterator.key(), executeQuery( queriesIterator.value() ) );
        }
    }

    detail::QSqlQueryModelPtr   Engine::executeQuery( const QString &query )
    {
        detail::QSqlQueryModelPtr model( new QSqlQueryModel() );
        model->setQuery( query, m_dbConnection );
        return model;
    }

    bool			    Engine::isOpened() const
    {
        return m_isOpened;
    }

    const QString		Engine::getLastError() const
    {
        return m_lastError;
    }

}
