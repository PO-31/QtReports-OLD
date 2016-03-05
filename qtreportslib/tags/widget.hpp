#pragma once
#ifndef WIDGET_HPP
#define WIDGET_HPP

//#include <QVector>
#include <QString>
//#include <QVariant>
#include <QPoint>
#include <QSize>
#include <QSharedPointer>

#include "style.hpp"
#include "object.hpp"

namespace qtreports {
    namespace detail {
        /* Интерфейс любого тэга, который будет отображаться на экране.
        Координаты объекта являются локальными относительно родительского объекта.*/
        class Widget : public Object {
                 
        public:
            Widget();
            virtual ~Widget();

            /* Установить положение объекта. Аргумент - неотрицательные координаты объекта, с центром координат в
             * верхнем левом углу. Координаты задаются относительно внешнего объекта. */
            void			setPosition( const QPoint & pos );
            /* Установить размер объекта. Аргумент - размер объекта. */
            void			setSize( const QSize & size );
            /* Устанавливает индекс стиля объекта значением styleId, отрицательные значения - стиль по умолчанию. */
            void            setStyle( const StylePtr & style );
            
            const QPoint    getPos() const;
            int             getX() const;
            int             getY() const;

            const QSize     getSize() const;
            int             getWidth() const;
            int             getHeight() const;

            /* Возвращает индекс стиля. */
            const StylePtr  getStyle() const;

            /* Установить значение параметра объекта с именем name значением value. Имя параметра name - не чувствительно
             * к регистру.
             * Список параметров:
             *  - int "x" - x - координата объекта;
             *  - int "y" - y - координата объекта;
             *  - int "w" - ширина объекта;
             *  - int "h" - высота объекта;
             *  - int "style_name" - индекс стиля объекта. */
            //virtual bool    setParameter( const QString & name, const QVariant & value );

        protected:
            QPoint					m_pos;
            QSize					m_size;
            StylePtr				m_style;

        };
        typedef QSharedPointer< Widget > WidgetPtr;

    }
}

#endif // WIDGET_HPP
