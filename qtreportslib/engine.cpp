#include <QPrintDialog>
#include <QPainter>
#include <QDebug>
#include <QPrintPreviewWidget>
#include <QPrintPreviewDialog>
#include "converters/convertertopdf.hpp"
#include "converters/convertertohtml.hpp"
#include "engine.hpp"

namespace qtreports
{

    Engine::Engine( QObject * parent ) :
        QObject( parent ),
        m_isOpened( false ),
        m_connectionIsSet( false ),
        m_dataSourceIsSet( false )
    {}

    Engine::Engine( const QString & path, QObject * parent ) :
        Engine( parent )
    {
        open( path );
    }

    Engine::~Engine() {}

    bool	Engine::open( const QString & path )
    {
        if( isOpened() )
        {
            close();
        }

        detail::Parser parser;
        if( !parser.parse( path ) )
        {
            m_lastError = "Parsing error: " + parser.getLastError();
            return false;
        }

        m_isOpened = true;
        m_compiledPath = path;
        m_report = parser.getReport();

        fillColumnsFromReport(); //MB as ProcessedDB::createColumns( ReportPtr )

        return true;
    }

    bool    Engine::close()
    {
        m_isOpened = false;
        m_compiledPath.clear();
        m_report.clear();

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
        m_connectionIsSet = true;

        prepareDB();
        m_report->setRowCount( 9 ); //m_processedDB.getField()

        for( auto && field : m_report->getFields() )
        {
            QVector < QVariant > tmp_vec;
            if (m_processedDB.getColumn( field->getName(), tmp_vec))
            {
                m_report->setFieldData( field->getName(), tmp_vec );
            }
        }

        return true;
    }

    void Engine::setDataSource(const QMap<QString, QVector<QVariant> > &columnsSet)
    {
        m_dataSource = columnsSet;
        m_dataSourceIsSet = true;

        prepareDataSource();
    }

    void Engine::setQuery(const QString &query)
    {
        m_queriesList = query.split(";", QString::SkipEmptyParts);
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
        setQuery(m_report.data()->getQuery());
        executeQueries();
    }

    void Engine::prepareDataSource()
    {
        QMapIterator <QString, QVector <QVariant> > iterator(m_dataSource);
        while(iterator.hasNext()) {
            iterator.next();
            m_processedDB.addFieldData(iterator.key(), iterator.value());
        }
    }

    void    Engine::fillColumnsFromReport()
    {

        QMap <QString, detail::FieldPtr> fieldMap = m_report.data()->getFields();
        QMapIterator <QString, detail::FieldPtr> fieldIterator(fieldMap);
        while(fieldIterator.hasNext()) {
            fieldIterator.next();
            m_processedDB.addColumn(fieldIterator.key());
        }

        /*for( auto && field : m_report->getFields() )
        {
            m_processedDB.addColumn( field->getName() );
        }*/
    }

    void Engine::executeQueries()
    {
        /*
        QStringListIterator iterator(m_queriesList);
        while(iterator.hasNext()) {
            QString query = iterator.next();
            QSqlQueryModel * model = new QSqlQueryModel();
        */
        for( auto && query : m_queriesList )
        {
            auto model = new QSqlQueryModel();
            model->setQuery( query, m_dbConnection );
            for( int row = 0; row < model->rowCount(); row++ )
            {
                QSqlRecord rec = model->record( row );
                for( int col = 0; col < rec.count(); col++ )
                {
                    m_processedDB.addFieldData( rec.fieldName( col ), rec.field( col ).value() );
                }
            }
        }
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
