#pragma once
#ifndef PAINTER_HPP
#define PAINTER_HPP
#include <QString>
#include <QPoint>
#include <QSize>
#include <QPainter>
#include <QPdfWriter>
#include "tags/style.hpp"

namespace qtreports {
	namespace detail {

		/* Осуществляет отображение отчета в некоторые форматы. */
		class Painter {
		public:
			Painter();

			/* Эта функция задает формат и файл, в которые будет транслирован готовый отчет.
			Вызывается перед началом рисования один раз. */
			bool	beginPDFDrawing( const QString & path );

			/* Вызывается перед отрисовкой конкретного объекта, возвращает его код. Теперь все последующие
			действия (задание рабочей зоны, рисование объектов, задание стиля и пр.) будут ассойиированы
			с этим объектом. */
			int		beginObjectDrawing(); 

			/* Устанавливает зону отрисовки для последнего объекта,
			вызвавшего begin_object_drawing().
			Причем координаты x и y задаются относительно координат области объекта,
			вызвавшего setWorkspace выше. Т.е. рабочие области вкладываются.
			Кроме того, рабочая область потомка не может выходить за пределы рабочей
			области родителя. */
			bool	setWorkspace( const QPoint & pos, const QSize & size ); 

			/* Заканчивает рисовать объект. */
            bool	endObjectDrawing( int workspaceId );

			/* Завершает отрисовку данной страницы, используется объектом Report. */
			void	pageDrawingComplete(); 

			bool	drawLine( const QPoint & point1, const QPoint & point2 );

			bool	drawText( int x, int y, const QString & text );

			// Вызывается, если объект требует новую страницу для отрисовки
			void	newPageRequest();
			bool	isNewPageRequested() const;

			bool	setCurrentPage( int index );
			int		pagesCount() const;

			int		currentPage() const;

			void	setStyle( int styleId );

			QString	getLastError() const;

		protected:

			// Создать новую страницу
			void newPage();

			// Задать стиль отрисовки
			void setStyle( const Style & style );

        private:
			bool				m_isNewPage;
			int					m_pageCounter;
			QString				m_last_error;
            QVector< int >		m_objects;
            QVector< QRect >	m_workspaces;
            QVector< Style >	m_styles;
			QPainter			m_painter;

		};

	}
}

#endif // PAINTER_HPP
