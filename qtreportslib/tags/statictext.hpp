#pragma once
#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP

#include "object.hpp"

namespace qtreports {
    namespace detail {

        class StaticText : public Object {

        public:
            StaticText( ObjectPtr parent = ObjectPtr() );

            const QString     getClassName() const;

        };

    }
}

#endif // STATICTEXT_HPP
