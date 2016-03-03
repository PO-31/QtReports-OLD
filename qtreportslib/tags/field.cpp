#include "field.hpp"

namespace qtreports {
    namespace detail {

        Field::Field( const QString & name, ObjectPtr parent ) :
            Object( parent ),
            m_name( name ) {}

        bool    Field::setClassName( const QString & name ) {
            int id = QMetaType::type( name.toStdString().c_str() );
            QMetaType type( id );
            m_className = name;

            return type.isValid();
        }

    }
}
