#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <QVector>
#include <QString>
#include <QVariant>
#include <QPoint>
#include <QSize>
#include <QSharedPointer>

#include "../painter.hpp"
#include "../processeddb.hpp"
#include "drawingexception.hpp"

namespace qtreports {
	namespace detail {
		class Object;

        /* "Умный" указатель на объект. */
		typedef QSharedPointer< Object > ObjectPtr;

		/* Интерфейс объекта для дальнейшей отрисовки. 
		Координаты объекта являются локальными относительно родительского объекта.
		При начале рисования объекта необходимо задать рабочую область 
		(прямоугольник в относительных координатах родителя). */
		class Object {

		public:
            /* Конструктор объекта, в качестве параметра принимает указатель на родительский объект, по умолчанию равный
             * NULL. */
			Object( ObjectPtr parent = ObjectPtr() );
			virtual ~Object();

            /* Рисует объект и его дочерние объекты. Аргументы: рисовальщик (или художник?) p, обработанная БД db.
                Возвращает false, в случае ошибки. */
			bool			draw( Painter & p, const ProcessedDB & db );

            /* Установить положение объекта. Аргумент - неотрицательные координаты объекта, с центром координат в
             * верхнем левом углу. Координаты задаются относительно внешнего объекта. */
			void			setPosition( const QPoint & pos );
            /* Установить размер объекта. Аргумент - размер объекта. */
			void			setSize( const QSize & size );
            /* Установить значение параметра объекта с именем name значением value. Имя параметра name - не чувствительно
             * к регистру.
             * Список параметров:
             *  - int "x" - x - координата объекта;
             *  - int "y" - y - координата объекта;
             *  - int "w" - ширина объекта;
             *  - int "h" - высота объекта;
             *  - int "style_id" - индекс стиля объекта. */
			virtual bool	setParameter( const QString & name, const QVariant & value );

            /* Возвращает вектор указателей внутренних (дочерних) объектов. */
            QVector< ObjectPtr > getChildsVector() const;

            /* Возвращает количество внутренних объектов */
            int             getChildsNumber() const;
            /* Добавляет объект к списку внутренних объектов. Аргумент: object - "умный" указатель на Object. */
			void			addChild( const ObjectPtr & object );
            /* Возвращает "умный" указатель на потомка с индексом index (нумерация с нуля). */
			ObjectPtr		getChild( int index ) const;

            /* Устанавливает индекс стиля объекта значением styleId, отрицательные значения - стиль по умолчанию. */
			void			setStyleId( int styleId );
            /* Возвращает индекс стиля. */
			int				getStyleId() const;

            /* Возвращает текст последней ошибки. */
			QString			getLastError() const;

            /* Возвращает имя класса (тэга). */
            virtual QString getClassName() const;

		protected:
			// Функция отрисовывает сам объект
			virtual bool	drawSelf( Painter & painter, const ProcessedDB & db ) = 0;
			// Задает параметры потомков (например их положение)
			virtual bool	prepareChilds( Painter & painter, const ProcessedDB & db ) = 0;

            /* Рисует внутренние объекты. */
			bool			drawChilds( Painter & painter, const ProcessedDB & db );

            /* Используется для передачи текста ошибки самому верхнему объекту иерархии. */
            void sendError(QString error);

			ObjectPtr				m_parent;
			QVector< ObjectPtr >	m_childs;

			QPoint					m_pos;
			QSize					m_size;
			int						m_styleId;

			QString					m_lastError;

		};

	}
}

#endif // OBJECT_HPP
