#pragma once
#ifndef RECT_HPP
#define RECT_HPP
#include <QSharedPointer>
#include "widget.hpp"

namespace qtreports
{
    namespace detail
    {

        class Rect : public Widget {

        public:
            Rect();
            ~Rect();

        private:

        };
        typedef QSharedPointer< Rect > RectPtr;

    }
}

#endif // RECT_HPP