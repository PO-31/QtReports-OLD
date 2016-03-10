#include "objectsplant.hpp"

namespace qtreports {
    namespace detail {

        ObjectsPlant::ObjectsPlant() {}

        const ObjectPtr ObjectsPlant::getObject( const QString & name ) const {
            Q_UNUSED( name );
            return ObjectPtr();
        }

        const QMap<QString, QString>    ObjectsPlant::getParamTypeMap( const QString & name ) const {
            Q_UNUSED( name );
            return QMap<QString, QString>();
        }

    }
}
