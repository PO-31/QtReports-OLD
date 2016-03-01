#include "band.hpp"

namespace qtreports {
	namespace detail {

        Band::Band( ObjectPtr parent ) :
            Object( parent ) {}

        const QString   Band::getClassName() {
            return QString("Band");
        }

	}
}
