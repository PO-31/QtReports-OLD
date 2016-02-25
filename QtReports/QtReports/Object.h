#ifndef OBJECT_H
#define OBJECT_H

#include <QVector>
#include <QString>
#include <QVariant>

#include "Painter.h"
#include "ProcessedDB.h"

/* Интерфейс объекта для дальнейшей отрисовки. Координаты объекта являются локальными относительно родительского объекта.
 * При начале рисования объекта необходимо задать рабочую область (прямоугольник в относительных координатах родителя). */


class Object
{
public:
    Object(Object *_parent = 0);

    bool draw(Painter &p, const ProcessedDB &db)
    {
        int id = p.beginObjectDrawing();

        if (!drawSelf(p, db))
        {
            p.endObjectDrawing(id);
            return false;
        }

        if (!prepareChilds(p, db))
        {
            p.endObjectDrawing(id);
            return false;
        }

        if (!drawChilds(p, db))
        {
            p.endObjectDrawing(id);
            return false;
        }

        p.endObjectDrawing(id);
        return true;
    }

    void setPosition(int _x, int _y)
    {
        if (_x < 0 || _y < 0)
            return;

        m_x = _x;
        m_y = _y;
    }

    void setSize(int _w, int _h)
    {
        if (_w < 0 || _h < 0)
            return;

        m_w = _w;
        m_h = _h;
    }

    void addChild(Object *ptr)
    {
        if (!ptr)
            return;

        m_childs.append(ptr);
    }

    Object* getChild(int ind)
    {
        if (ind < 0 || ind >= m_childs.size())
            return 0;

        return m_childs.at(ind);
    }

    QString lastError()
    {
        if (!m_errors.size())
            return QString();

        return m_errors.takeLast();
    }

    virtual bool setParam(QString param, QVariant val);

    void set_style_id(int _style_id)
    {
        m_style_id = _style_id;
    }

protected:

    virtual bool drawSelf(Painter &p, const ProcessedDB &db) = 0; // Функция отрисовывает сам объект
    virtual bool prepareChilds(Painter &p, const ProcessedDB &db) = 0; // Задает параметры потомков (например их положение)
    bool drawChilds(Painter &p, const ProcessedDB &db)
    {
        for (int i = 0; i < m_childs.size(); ++i)
            if (!m_childs.at(i)->draw(p, db))
                return false;

        return true;
    }

    void sendError(const QString &str) // Должна вызываться каждый раз при возникновении ошибки во время рисования
    {
        if (m_parent)
            m_parent->reciveError(str);
    }

    void reciveError(const QString &str)
    {
        if (m_parent)
        {
            sendError(str);
        }
        else
        {
            m_errors.append(str);
        }
    }

    int m_x, m_y;
    int m_w, m_h;

    int m_style_id;

    Object *m_parent;

    QVector<Object*> m_childs;
    QVector<QString> m_errors;
};

#endif // OBJECT_H
