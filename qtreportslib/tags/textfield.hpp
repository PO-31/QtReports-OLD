#pragma once
#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP
#include <QSharedPointer>
#include "widget.hpp"

namespace qtreports {
    namespace detail {

        class TextField : public Widget {
              
        public:
            TextField();
            ~TextField();

            void            setText( const QString & text );
            const QString   getText() const;

        private:
            QString     m_text;

        };
        typedef QSharedPointer< TextField > TextFieldPtr;

    }
}

#endif // TEXTFIELD_HPP
