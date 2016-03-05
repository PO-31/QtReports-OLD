#pragma once
#ifndef FIELD_HPP
#define FIELD_HPP
#include <QSharedPointer>
#include "object.hpp"

namespace qtreports {
    namespace detail {
        class Field : public Object {

        public:
            Field();
            ~Field();

            bool    setClassName( const QString & name );

        private:
            QString     m_className;

        };

        typedef QSharedPointer< Field > FieldPtr;
    }
}

#endif // FIELD_HPP
