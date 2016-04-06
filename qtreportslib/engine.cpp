#include <QPrintDialog>
#include <QPainter>
#include <QDebug>
#include <QPrintPreviewWidget>
#include <QPrintPreviewDialog>
#include "converters/convertertopdf.hpp"
#include "converters/convertertohtml.hpp"
#include "replacer.hpp"
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

    void    Engine::close()
    {
        m_isOpened = false;
        m_compiledPath.clear();
        m_report.clear();
    }

    bool	Engine::setParameters( const QMap< QString, QVariant > & parameters )
    {
        if( m_report.isNull() )
        {
            m_lastError = "Report is empty. Please open report file";
            return false;
        }

        m_report->setParameters( parameters );

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

        if( !prepareDB() )
        {
            m_lastError = "Error in prepare db process: " + m_lastError;
            return false;
        }

        m_report->setRowCount( m_processedDB.getMaxRowCount() );

        for( auto && field : m_report->getFields() )
        {
            auto name = field->getName();
            auto value = m_processedDB.getColumn( name );
            m_report->setFieldData( name, value );
        }

        m_processedDB.setParameters( m_report->getParameters() );

        return true;
    }

    bool    Engine::setDataSource( const QMap< QString, QVector< QVariant > > & source )
    {
        //Need check parameters
        //m_dataSource = columnsSet;

        if( !prepareDataSource( source ) )
        {
            m_lastError = "Error in prepare data source: " + m_lastError;
            return false;
        }
        
        m_report->setRowCount( m_processedDB.getMaxRowCount() );

        for( auto && field : m_report->getFields() )
        {
            auto name = field->getName();
            auto value = m_processedDB.getColumn( name );
            m_report->setFieldData( name, value );
        }

        return true;
    }

    bool    Engine::setQuery( const QString & query )
    {
        //Need check parameters
        auto queries = query.split( ";", QString::SkipEmptyParts );
        executeQueries( queries );

        m_lastError = query;
        return true;
    }

    bool    Engine::addScript( const QString & script )
    {
        //Need check parameters
        m_scripts.append( script );

        return true;
    }

    bool    Engine::setDataModel( const QAbstractItemModel & model )
    {
        //Need check parameters
        Q_UNUSED( model )
        return true;
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

    QWidgetPtr	Engine::createWidget()
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

    QWidgetPtr	Engine::createLayout()
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
        if( m_report.isNull() )
        {
            m_lastError = "Report is empty. Please open report file";
            return false;
        }

        QPrinter printer;
        QPrintPreviewDialog preview( &printer );
        connect(
            &preview, &QPrintPreviewDialog::paintRequested,
            this, &Engine::drawPreview
            );
        preview.exec();

        return true;
    }

    void	Engine::drawPreview( QPrinter * printer )
    {
        auto temp = m_report->getOrientation();
        m_report->setOrientation( printer->orientation() );
        detail::ConverterToQWidget converter( m_report );
        auto result = converter.convert( detail::ConverterToQWidget::WidgetType::Report );
        m_report->setOrientation( temp );
        if( !result )
        {
            m_lastError = converter.getLastError();
            return;
        }

        auto widgets = converter.getPages();
        if( widgets.isEmpty() )
        {
            m_lastError = "Cannot print widget: all pages is empty";
            return;
        }

        auto widget = widgets.value( 0 );

        QRectF rect = printer->pageRect();
        QPainter painter( printer );
        qreal scale = rect.width() / widget->width();

        widget->resize( widget->width(), rect.height() / scale );
        painter.scale( scale, scale );

        for( int i = 0; i < widgets.size(); ++i )
        {
            i != 0 ? printer->newPage() : 0;
            widget = widgets.value( i );
            if( widget.isNull() )
            {
                m_lastError = "Error in print process: printed widget is empty";
                return;
            }

            //Magic
            widget->show();
            widget->hide();
            widget->render( &painter );
        }
    }

    bool    Engine::prepareDB() {
        return setQuery( m_report->getQuery() );
    }

    bool    Engine::prepareDataSource( const QMap< QString, QVector< QVariant > > & source )
    {
        QMapIterator< QString, QVector< QVariant > > iterator( source );
        while( iterator.hasNext() )
        {
            iterator.next();
            auto field = m_report->getField( iterator.key() );
            if( field.isNull() )
            {
                m_lastError = "Report not have column: " + iterator.key();
                return false;
            }

            field->setData( iterator.value() );
        }

        return true;
    }

    void    Engine::fillColumnsFromReport()
    {
        for( auto && field : m_report->getFields() )
        {
            m_processedDB.addEmptyColumn( field->getName() );
        }
    }

    void    Engine::executeQueries( const QStringList & queries )
    {
        for( auto && query : queries )
        {
            auto model = new QSqlQueryModel();
            model->setQuery( query, m_dbConnection );
            for( int row = 0; row < model->rowCount(); row++ )
            {
                QSqlRecord rec = model->record( row );
                for( int col = 0; col < rec.count(); col++ )
                {
                    m_processedDB.appendColumnData( rec.fieldName( col ), rec.field( col ).value() );
                }
            }
        }
    }

    bool    Engine::isOpened() const
    {
        return m_isOpened;
    }

    detail::ReportPtr	Engine::getReport() const
    {
        return m_report;
    }
	
    const QString   Engine::getLastError() const
    {
        return m_lastError;
    }

}
