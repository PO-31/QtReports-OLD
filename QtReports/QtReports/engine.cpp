#include <QPdfWriter>
#include <QPrintDialog>
#include <QPainter>
#include <QPrintPreviewWidget>
#include <QPrintPreviewDialog>
#include "engine.hpp"

namespace qtreports {

	Engine::Engine( QObject * parent ) : 
		QObject( parent ) {}

	Engine::~Engine() {}

	bool	Engine::compile( const QString & path ) {
		detail::Translator translator;
		bool result = translator.parse( path );
		if( !result ) {
			m_lastError = translator.getLastError();
			return false;
		}

		m_widget = translator.getWidget();
		return true;
	}

	bool	Engine::setParameters( const QMap< QString, QString > & map ) {
		//setParameters
		return true;
	}

	bool	Engine::setConnection( const QSqlDatabase & connection ) {
		if( connection.isOpen() ) {
			m_lastError = "Connection not open";
			return false;
		}

		return true;
	}

	bool	Engine::createPDF( const QString & path ) {
		QWidgetPtr widget = getWidget();
		QPdfWriter writer( path );
		widget->render( &writer ); //very small
		return true;
	}

	bool	Engine::createHTML( const QString & path ) {
		QWidgetPtr widget = getWidget();
		//widget to html - ???
		//false if error
		return true;
	}

	bool	Engine::print() {
		QPrinter printer;

		QPrintPreviewDialog preview( &printer );
		connect( 
			&preview, &QPrintPreviewDialog::paintRequested,
			this, &Engine::drawPreview );
		preview.exec();

		return true;
	}

	void	Engine::drawPreview( QPrinter * printer ) {
		QWidgetPtr widget = getWidget();
		QRectF rect = printer->pageRect();
		QPainter painter( printer );
		double xscale = rect.width() / widget->width();
		double yscale = rect.height() / widget->height();
		double scale = std::min( xscale, yscale );
		painter.translate( 0,	rect.height() / 2
								- scale * widget->height() / 2 );
		painter.scale( scale, scale );
		widget->render( &painter );
	}

	const QString	Engine::getLastError() const {
		return m_lastError;
	}

	const QWidgetPtr	Engine::getWidget() const {
		return m_widget;
	}
}