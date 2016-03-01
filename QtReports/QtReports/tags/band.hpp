#pragma once
#ifndef BAND_HPP
#define BAND_HPP
#include "object.hpp"

namespace qtreports {
    namespace detail {

        class Band : public Object {

        public:
            Band( ObjectPtr parent = ObjectPtr() );

            const QString   getClassName();

        };

    }
}

#endif // BAND_HPP
