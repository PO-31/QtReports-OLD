#include <QPrintDialog>
#include <QPainter>
#include <QPrintPreviewWidget>
#include <QPrintPreviewDialog>
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
        auto text = m_report->getDetail()->getBands()[ 0 ]->getTextFields()[ 0 ]->getText();
        m_report->getDetail()->getBands()[ 0 ]->getTextFields()[ 0 ]->setText( map[ "title" ] );
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
        Converter converter( m_report );
        auto result = converter.toPDF( path );
        if( !result ) {
            m_lastError = converter.getLastError();
            return false;
        }

        return true;
    }

    bool	Engine::createHTML( const QString & path ) {
        Converter converter( m_report );
        auto result = converter.toHTML( path );
        if( !result ) {
            m_lastError = converter.getLastError();
            return false;
        }

        return true;
    }

    const QWidgetPtr	Engine::createWidget() const {
        return Converter( m_report ).toQWidget();
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
