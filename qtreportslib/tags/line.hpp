#pragma once
#ifndef LINE_HPP
#define LINE_HPP
#include <QSharedPointer>
#include "widget.hpp"

namespace qtreports
{
    namespace detail
    {

        class Line : public Widget {

        public:
            Line();
            ~Line();

        private:

        };
        typedef QSharedPointer< Line > LinePtr;

    }
}

#endif // LINE_HPP