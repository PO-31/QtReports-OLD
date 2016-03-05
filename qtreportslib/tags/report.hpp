#pragma once
#ifndef REPORT_HPP
#define REPORT_HPP

#include <QString>
#include <QSize>
#include <QMap>
#include <QVector>
#include <QSharedPointer>

#include "widget.hpp"
#include "field.hpp"
#include "style.hpp"
#include "detail.hpp"

namespace qtreports {
    namespace detail {

        class Report {
                 
        public:
            Report();
            ~Report();

            /* Список параметров Report:
             *  - int "page_width" - ширина страницы;
             *  - int "page_height" - высота страницы;
             *  - bool "is_vertical" - принимает значение true, если объект вертикальный;
             *  - все параметры Object. */
            //bool	                            setParameter( const QString & name, const QVariant & value );

            void                                setField( const QString & name, const FieldPtr & field );
            const FieldPtr                      getField( const QString & name ) const;
            const QMap< QString, FieldPtr >     getFields() const;

            void                                setStyle( const QString & name, const StylePtr & style );
            const StylePtr                      getStyle( const QString & name ) const;
            const QMap< QString, StylePtr >     getStyles() const;

            void                                setDefaultStyleName( const QString & name );
            const QString                       getDefaultStyleName() const;

            void                                setDetail( const DetailPtr & detail );
            const DetailPtr                     getDetail() const;

        private:
            bool	m_isVertical;
            QSize	m_size;

            DetailPtr                   m_detail;
            QString                     m_defaultStyleName;
            QMap< QString, StylePtr >   m_styles;
            QMap< QString, FieldPtr >   m_fields;

        };
        typedef QSharedPointer< Report > ReportPtr;

    }
}

#endif // REPORT_HPP
