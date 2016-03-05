#include "field.hpp"

namespace qtreports {
    namespace detail {

        Field::Field() {}

        Field::~Field() {}

        bool    Field::setClassName( const QString & name ) {
            //int id = QMetaType::type( name.toStdString().c_str() );
            //QMetaType type( id );
            //m_className = name;
            Q_UNUSED( name );
            return true;// type.isValid();
        }

    }
}
