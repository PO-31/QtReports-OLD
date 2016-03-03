#include <QPdfWriter>
#include <QPrintDialog>
#include <QPainter>
#include <QPrintPreviewWidget>
#include <QPrintPreviewDialog>
//#include <QTextBrowser>
#include <QFile>
//#include <QTextStream>
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

		m_widget = parser.getWidget();
		return true;
	}

	bool	Engine::setParameters( const QMap< QString, QString > & map ) {
		//QString or QVariant?
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

    void Engine::addQuery(const QString & queryName, const QString & query) {
        m_dbQueries[queryName] = query;
    }

    void Engine::addScript(const QString & script) {
        m_scripts.append(script);
    }

	bool	Engine::createPDF( const QString & path ) {
		QPdfWriter writer( path );
		//Very small, need resize to page size.
		m_widget->render( &writer );
		return true;
	}

	bool	Engine::createHTML( const QString & path ) {
		auto isCopied = QFile::copy( m_compiledPath, path );
		if( !isCopied ) {
			m_lastError = "Can not create html file";
			return false;
		}

		return true;
		/*
		auto browser = dynamic_cast< QTextBrowser * >( m_widget.data() );
		QFile file( path );
		file.open(
		QIODevice::OpenModeFlag::WriteOnly |
		QIODevice::OpenModeFlag::Text |
		QIODevice::OpenModeFlag::Truncate
		);

		if( !file.isOpen() ) {
		m_lastError = "The file can not be opened";
		return false;
		}

		QTextStream stream( &file );
		stream << browser->toHtml();

		return true;
		*/
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

    void Engine::prepareDB() {
        QMapIterator <QString, QString> queriesIterator(m_dbQueries);

        while(queriesIterator.hasNext()) {
            queriesIterator.next();
            m_processedDB.addExecutedQuery(queriesIterator.key(), executeQuery(queriesIterator.value()));
        }
    }

    QSqlQueryModel* Engine::executeQuery(const QString &query)
    {
        QSqlQueryModel *result = new QSqlQueryModel();
        result->setQuery(query, m_dbConnection);
        return result;
    }

	const QString		Engine::getLastError() const {
		return m_lastError;
	}

	const QWidgetPtr	Engine::getWidget() const {
		return m_widget;
	}

	const bool			Engine::isCompiled() const {
		return m_isCompiled;
	}
}
