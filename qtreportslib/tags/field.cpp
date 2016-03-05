#include "field.hpp"

namespace qtreports {
    namespace detail {

        Field::Field() {}

        Field::~Field() {}

        void    Field::setClassName( const QString & name ) {
            //int id = QMetaType::type( name.toStdString().c_str() );
            //QMetaType type( id );
            //return type.isValid();
            m_className = name;
        }

        const QString   Field::getClassName() const {
            return m_className;
        }

    }
}
