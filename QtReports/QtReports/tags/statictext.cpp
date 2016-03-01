#include "statictext.hpp"

namespace qtreports {
	namespace detail {

    StaticText::StaticText( ObjectPtr parent ) :
        Object( parent ) {}

    QString StaticText::getClassName()
    {
        return QString("Static_text");
    }

	}
}
