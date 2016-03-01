#pragma once
#ifndef DETAIL_HPP
#define DETAIL_HPP
#include "object.hpp"

namespace qtreports {
    namespace detail {

        class Detail : public Object {

        public:
            Detail( ObjectPtr parent = ObjectPtr() );

            const QString   getClassName();

        };

    }
}

#endif // DETAIL_HPP
