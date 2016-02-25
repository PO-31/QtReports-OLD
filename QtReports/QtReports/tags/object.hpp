#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <QVector>
#include <QString>
#include <QVariant>
#include <QPoint>
#include <QSize>
#include <QSharedPointer>
#include "..\painter.hpp"
#include "..\processeddb.hpp"

namespace qtreports {
	namespace detail {
		class Object;
		typedef QSharedPointer< Object > ObjectPtr;

		/* Интерфейс объекта для дальнейшей отрисовки. 
		Координаты объекта являются локальными относительно родительского объекта.
		При начале рисования объекта необходимо задать рабочую область 
		(прямоугольник в относительных координатах родителя). */
		class Object {

		public:
			Object( ObjectPtr parent = ObjectPtr() );
			~Object();

			bool			draw( Painter & p, const ProcessedDB & db );

			void			setPosition( const QPoint & pos );
			void			setSize( const QSize & size );
			virtual bool	setParameter( const QString & name, const QVariant & value );

			void			addChild( const ObjectPtr & object );
			const ObjectPtr	getChild( int index ) const;

			void			setStyleId( int styleId );
			int				getStyleId() const;

			QString			getLastError() const;

		protected:
			// Функция отрисовывает сам объект
			virtual bool	drawSelf( Painter & painter, const ProcessedDB & db ) = 0;
			// Задает параметры потомков (например их положение)
			virtual bool	prepareChilds( Painter & painter, const ProcessedDB & db ) = 0;
			bool			drawChilds( Painter & painter, const ProcessedDB & db );

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
