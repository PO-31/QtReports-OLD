#include "statictext.hpp"

namespace qtreports {
    namespace detail {

        StaticText::StaticText( ObjectPtr parent ) :
            Object( parent ) {}

        const QString   StaticText::getClassName() const {
            return "StaticText";
        }

    }
}
