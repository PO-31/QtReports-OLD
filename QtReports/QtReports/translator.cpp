#include "translator.hpp"

namespace qtreports {
	namespace detail {

		Translator::Translator() {}

		Translator::~Translator() {}

		bool	Translator::parse( const QString & path ) {
			//QXMLParser( path );
			//parsing...
			//return false if error
			m_widget = QWidgetPtr( new QWidget() );
			return true;
		}

		const QString	Translator::getLastError() const {
			return m_lastError;
		}

		const QWidgetPtr	Translator::getWidget() const {
			return m_widget;
		}

	}
}