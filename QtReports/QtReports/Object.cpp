#include "Object.h"


Object::Object(Object *_parent)
{
    m_parent = _parent;

    m_x = m_y = m_w = m_h = m_style_id = 0;
}

bool Object::setParam(QString param, QVariant val)
{
    QString _x("x"), _y("y"), _w("w"), _h("h"), _style_id("style_id");

    if (!val.isValid())
    {
        m_errors.append("Invalid parameter value");
        return false;
    }

    if (_x.compare(param, Qt::CaseInsensitive) == 0)
    {
        if (val.type() != QVariant::Int)
        {
            m_errors.append("Invalid type for this argument");
            return false;
        }

        m_x = val.toInt();

        return true;
    }

    if (_y.compare(param, Qt::CaseInsensitive) == 0)
    {
        if (val.type() != QVariant::Int)
        {
            m_errors.append("Invalid type for this argument");
            return false;
        }

        m_y = val.toInt();

        return true;
    }

    if (_w.compare(param, Qt::CaseInsensitive) == 0)
    {
        if (val.type() != QVariant::Int)
        {
            m_errors.append("Invalid type for this argument");
            return false;
        }

        m_w = val.toInt();

        return true;
    }

    if (_h.compare(param, Qt::CaseInsensitive) == 0)
    {
        if (val.type() != QVariant::Int)
        {
            m_errors.append("Invalid type for this argument");
            return false;
        }

        m_h = val.toInt();

        return true;
    }

    if (_style_id.compare(param, Qt::CaseInsensitive) == 0)
    {
        if (val.type() != QVariant::Int)
        {
            m_errors.append("Invalid type for this argument");
            return false;
        }

        m_style_id = val.toInt();

        return true;
    }


    m_errors.append("Unknown argument");
    return false;
}
