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
		//widget to pdf
		//false if error
		return true;
	}

	bool	Engine::createHTML( const QString & path ) {
		QWidgetPtr widget = getWidget();
		//widget to html
		//false if error
		return false;
	}

	const QString	Engine::getLastError() const {
		return m_lastError;
	}

	const QWidgetPtr	Engine::getWidget() const {
		return m_widget;
	}
}