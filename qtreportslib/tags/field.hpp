#pragma once
#ifndef FIELD_HPP
#define FIELD_HPP
#include "object.hpp"

namespace qtreports {
    namespace detail {

        class Field : private Object {

        public:
            Field( const QString & name, ObjectPtr parent = ObjectPtr() );

            bool    setClassName( const QString & name );

        private:
            QString     m_name;
            QString     m_className;

        };

    }
}

#endif // FIELD_HPP
