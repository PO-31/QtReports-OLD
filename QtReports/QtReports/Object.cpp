#include "Object.h"


Object::Object(Object *_parent)
{
    parent = _parent;

    x = y = w = h = style_id = 0;
}

bool Object::set_param(QString param, QVariant val)
{
    QString _x("x"), _y("y"), _w("w"), _h("h"), _style_id("style_id");

    if (!val.isValid())
    {
        errors.append("Invalid parameter value");
        return false;
    }

    if (_x.compare(param, Qt::CaseInsensitive) == 0)
    {
        if (val.type() != QVariant::Int)
        {
            errors.append("Invalid type for this argument");
            return false;
        }

        x = val.toInt();

        return true;
    }

    if (_y.compare(param, Qt::CaseInsensitive) == 0)
    {
        if (val.type() != QVariant::Int)
        {
            errors.append("Invalid type for this argument");
            return false;
        }

        y = val.toInt();

        return true;
    }

    if (_w.compare(param, Qt::CaseInsensitive) == 0)
    {
        if (val.type() != QVariant::Int)
        {
            errors.append("Invalid type for this argument");
            return false;
        }

        w = val.toInt();

        return true;
    }

    if (_h.compare(param, Qt::CaseInsensitive) == 0)
    {
        if (val.type() != QVariant::Int)
        {
            errors.append("Invalid type for this argument");
            return false;
        }

        h = val.toInt();

        return true;
    }

    if (_style_id.compare(param, Qt::CaseInsensitive) == 0)
    {
        if (val.type() != QVariant::Int)
        {
            errors.append("Invalid type for this argument");
            return false;
        }

        style_id = val.toInt();

        return true;
    }


    errors.append("Unknown argument");
    return false;
}
