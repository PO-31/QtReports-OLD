#pragma once
#ifndef REPORT_HPP
#define REPORT_HPP
#include <QString>
#include <QSize>
#include <QSharedPointer>
#include "tags/object.hpp"
#include "painter.hpp"
#include "processeddb.hpp"

namespace qtreports {
    namespace detail {
        class Report : public Object {

        public:
            Report();
            ~Report();

            /* Отрисовывает отчет. Аргументы те же, что и у Object::draw(...). */
            bool	draw( Painter & p, const ProcessedDB & db );

            const QString	asHTML() const;

            /* Список параметров Report:
             *  - int "page_width" - ширина страницы;
             *  - int "page_height" - высота страницы;
             *  - bool "is_vertical" - принимает значение true, если объект вертикальный;
             *  - все параметры Object. */
            bool	        setParameter( const QString & name, const QVariant & value );

            const QString   getClassName() const;

        protected:

            bool	drawSelf( Painter & painter, const ProcessedDB & db );
            bool	prepareChilds( Painter & painter, const ProcessedDB & db );

            bool	m_isVertical;
            QSize	m_size;

        };

        typedef QSharedPointer< Report > ReportPtr;
    }
}

#endif // REPORT_HPP
