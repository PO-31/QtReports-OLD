#pragma once
#ifndef PAINTER_HPP
#define PAINTER_HPP
#include <QString>
#include <QPoint>
#include <QSize>
#include <QPainter>
#include <QSharedPointer>

namespace qtreports {
    namespace detail {
        class Style;
        class Report;
        typedef QSharedPointer< Report > ReportPtr;
        typedef QSharedPointer< Style > StylePtr;

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
            bool        drawRect( const QRect & rect );
            bool        drawImage( const QString & path, const QRect & rect);

            bool	drawText( int x, int y, const QString & text );

            // Вызывается, если объект требует новую страницу для отрисовки
            void	newPageRequest();
            bool	isNewPageRequested() const;

            bool	setCurrentPage( int index );
            int		pagesCount() const;

            int		currentPage() const;

            void    setDefaultStyle();
            void	setStyle( const QString & name );

            const QString	getLastError() const;

        protected:
            // Создать новую страницу
            void    newPage();

            // Задать стиль отрисовки
            void    setStyle( const StylePtr & style );

        private:
            bool				m_isNewPage;
            int					m_pageCounter;
            QString				m_last_error;
            QVector< int >		m_objects;
            QVector< QRect >	m_workspaces;
            ReportPtr       	m_report;
            QPainter			m_painter;

        };

    }
}

#endif // PAINTER_HPP
