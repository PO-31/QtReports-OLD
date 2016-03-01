#include "band.hpp"

namespace qtreports {
	namespace detail {

    Band::Band( ObjectPtr parent ) :
        Object( parent ) {}

    QString Band::getClassName()
    {
        return QString("Band");
    }

	}
}
