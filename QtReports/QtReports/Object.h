#ifndef OBJECT_H
#define OBJECT_H

#include <QVector>
#include <QString>
#include <QVariant>

#include <Painter.h>
#include <ProcessedDB.h>

/* Интерфейс объекта для дальнейшей отрисовки. Координаты объекта являются локальными относительно родительского объекта.
 * При начале рисования объекта необходимо задать рабочую область (прямоугольник в относительных координатах родителя). */


class Object
{
public:
    Object(Object *_parent = 0);

    bool draw(Painter &p, const ProcessedDB &db)
    {
        int id = p.begin_object_drawing();

        if (!draw_self(p, db))
        {
            p.end_object_drawing(id);
            return false;
        }

        if (!prepare_childs(p, db))
        {
            p.end_object_drawing(id);
            return false;
        }

        if (!draw_childs(p, db))
        {
            p.end_object_drawing(id);
            return false;
        }

        p.end_object_drawing(id);
        return true;
    }

    void set_position(int _x, int _y)
    {
        if (_x < 0 || _y < 0)
            return;

        x = _x;
        y = _y;
    }

    void set_size(int _w, int _h)
    {
        if (_w < 0 || _h < 0)
            return;

        w = _w;
        h = _h;
    }

    void add_child(Object *ptr)
    {
        if (!ptr)
            return;

        childs.append(ptr);
    }

    Object* get_child(int ind)
    {
        if (ind < 0 || ind >= childs.size())
            return 0;

        return childs.at(ind);
    }

    QString last_error()
    {
        if (!errors.size())
            return QString();

        return errors.takeLast();
    }

    virtual bool set_param(QString param, QVariant val);

protected:

    virtual bool draw_self(Painter &p, const ProcessedDB &db) = 0; // Функция отрисовывает сам объект
    virtual bool prepare_childs(Painter &p, const ProcessedDB &db) = 0; // Задает параметры потомков (например их положение)
    bool draw_childs(Painter &p, const ProcessedDB &db)
    {
        for (int i = 0; i < childs.size(); ++i)
            if (!childs.at(i)->draw(p, db))
                return false;

        return true;
    }

    void send_error(const QString &str) // Должна вызываться каждый раз при возникновении ошибки во время рисования
    {
        if (parent)
            parent->recive_error(str);
    }

    void recive_error(const QString &str)
    {
        if (parent)
        {
            send_error(str);
        }
        else
        {
            errors.append(str);
        }
    }

    int x, y;
    int w, h;

    int style_id;

    Object *parent;

    QVector<Object*> childs;
    QVector<QString> errors;
};

#endif // OBJECT_H
