#pragma once
#ifndef TITLE_HPP
#define TITLE_HPP
#include "object.hpp"

namespace qtreports {
    namespace detail {

        class Title : public Object {

        public:
            Title();

            const QString getClassName() const;

        };

    }
}

#endif // TITLE_HPP
