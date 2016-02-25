#ifndef OBJECTSPLANT_H
#define OBJECTSPLANT_H

#include "Object.h"

#include <QMap>
#include <QString>

/* Фабрика объектов, возвращает объект и карту его параметров. */

class ObjectsPlant
{
public:
    ObjectsPlant();

    Object* getObject(QString object_name) const;

    QMap <QString, QString> getParamTypeMap(QString object_name) const;
};

#endif // OBJECTSPLANT_H
