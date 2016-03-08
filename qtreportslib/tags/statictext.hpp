#pragma once
#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP
#include <QString>
#include <QSharedPointer>
#include "widget.hpp"

namespace qtreports {
    namespace detail {

        class StaticText : public Widget {
              
        public:
            StaticText();
            ~StaticText();

            void            setText( const QString & text );
            const QString   getText() const;

        private:
            QString     m_text;

        };
        typedef QSharedPointer< StaticText > StaticTextPtr;

    }
}

#endif // STATICTEXT_HPP
