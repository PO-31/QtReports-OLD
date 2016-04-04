#pragma once
#ifndef WIDGET_HPP
#define WIDGET_HPP

//#include <QVector>
#include <QString>
//#include <QVariant>
#include <QPoint>
#include <QSize>
#include <QRect>
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
            void			setX( int x );
            void			setY( int y );

            /* Установить размер объекта. Аргумент - размер объекта. */
            void			setSize( const QSize & size );
            void			setWidth( int width );
            void			setHeight( int height );

            void			setRect( const QRect & rect );
            /* Устанавливает индекс стиля объекта значением styleId, отрицательные значения - стиль по умолчанию. */
            //void            setStyle( const StylePtr & style );
            void            setStyle( const QString & style );

            void            setAlignment( Qt::Alignment alignment );
            Qt::Alignment   getAlignment();
            
            const QPoint    getPos() const;
            int             getX() const;
            int             getY() const;

            const QSize     getSize() const;
            int             getWidth() const;
            int             getHeight() const;

            const QRect     getRect() const;

            /* Возвращает индекс стиля. */
            //const StylePtr  getStyle() const;
            const QString   getStyle() const;

            bool            isBold() const;
            void            setBold( bool isBold );

        protected:
            bool                    m_isBold;
            QRect					m_rect;
            Qt::Alignment           m_alignment;
            //StylePtr				m_style;
            QString				    m_style;

        };
        typedef QSharedPointer< Widget > WidgetPtr;

    }
}

#endif // WIDGET_HPP
