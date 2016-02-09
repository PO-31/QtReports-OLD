#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include "engine.hpp"

namespace qtreports {

	Engine::Engine() {}

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
		//QPdfWriter ?
		//widget to pdf - simple
		//false if error
		return true;
	}

	bool	Engine::createHTML( const QString & path ) {
		QWidgetPtr widget = getWidget();
		//widget to html - ???
		//false if error
		return true;
	}

	bool	Engine::print() {
		QWidgetPtr widget = getWidget();
		
		QPrinter printer;

		QPrintDialog dialog( &printer );
		dialog.setWindowTitle( QObject::tr( "Print Document" ) );
		if ( dialog.exec() != QDialog::Accepted ) {
			return false;
		}

		QPainter painter;
		painter.begin( &printer );
		double xscale = printer.pageRect().width() / double( widget->width() );
		double yscale = printer.pageRect().height() / double( widget->height() );
		double scale = qMin( xscale, yscale );
		painter.translate( printer.paperRect().x() + printer.pageRect().width() / 2,
			printer.paperRect().y() + printer.pageRect().height() / 2 );
		painter.scale( scale, scale );
		//spainter.translate( -width() / 2, -height() / 2 );
		painter.end(); //??
		widget->render( &painter );
		
		return true;
	}

	const QString	Engine::getLastError() const {
		return m_lastError;
	}

	const QWidgetPtr	Engine::getWidget() const {
		return m_widget;
	}
}