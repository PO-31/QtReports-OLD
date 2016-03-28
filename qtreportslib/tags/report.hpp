#pragma once
#ifndef REPORT_HPP
#define REPORT_HPP

#include <QString>
#include <QSize>
#include <QMap>
#include <QVector>
#include <QSharedPointer>

#include "object.hpp"
#include "field.hpp"
#include "style.hpp"
#include "title.hpp"
#include "detail.hpp"

namespace qtreports {
    namespace detail {

        class Report : public Object {
                 
        public:
            Report();
            ~Report();

            enum Size {
                A4Gorizontal = 0,
                A4Vertical
            };

            /* Список параметров Report:
             *  - int "page_width" - ширина страницы;
             *  - int "page_height" - высота страницы;
             *  - bool "is_vertical" - принимает значение true, если объект вертикальный;
             *  - все параметры Object. */
            //bool	                            setParameter( const QString & name, const QVariant & value );

            void                                setDefaultStyle( const StylePtr & style );
            const StylePtr                      getDefaultStyle() const;

            void                                setStyle( const QString & name, const StylePtr & style );
            const StylePtr                      getStyle( const QString & name ) const;
            const QMap< QString, StylePtr >     getStyles() const;

            void                                setQuery( const QString & query );
            const QString                       getQuery() const;

            void                                setField( const QString & name, const FieldPtr & field );
            const FieldPtr                      getField( const QString & name ) const;
            const QMap< QString, FieldPtr >     getFields() const;

            void                                setTitle( const TitlePtr & title );
            const TitlePtr                      getTitle() const;

            void                                setDetail( const DetailPtr & detail );
            const DetailPtr                     getDetail() const;

            void setFieldData(const QString field_name, const QVector < QVariant > data);

            int     getRowCount();
            void    setRowCount( int count );

            int     getLeftMargin();
            int     getTopMargin();
            int     getRightMargin();
            int     getBottomMargin();

            void    setLeftMargin( int left );
            void    setTopMargin( int top );
            void    setRightMargin( int right );
            void    setBottomMargin( int bottom );
            void    setMargins( int left, int top, int right, int bottom );

        private:
            bool	                    m_isVertical; //?
            QSize	                    m_size; //?
            int                         m_leftMargin;
            int                         m_topMargin;
            int                         m_rightMargin;
            int                         m_bottomMargin;
            int                         m_rowCount;
            StylePtr                    m_defaultStyle;
            QMap< QString, StylePtr >   m_styles;
            QString                     m_query;
            QMap< QString, FieldPtr >   m_fields;
            TitlePtr                    m_title;
            DetailPtr                   m_detail;

        };
        typedef QSharedPointer< Report > ReportPtr;

    }
}

#endif // REPORT_HPP
