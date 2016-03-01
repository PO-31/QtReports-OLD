#include "detail.hpp"

namespace qtreports {
    namespace detail {

        Detail::Detail( ObjectPtr parent ) :
            Object( parent ) {}

        const QString   Detail::getClassName() {
            return QString( "Detail" );
        }

    }
}
