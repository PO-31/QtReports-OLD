#pragma once
#ifndef REPORT_HPP
#define REPORT_HPP

#include <QString>
#include <QSize>
#include <QMap>
#include <QVector>
#include <QSharedPointer>
#include <QMargins>
#include <QPrinter>

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
            void                                setFieldData( const QString & name, const QVector< QVariant > & data );

            void                                setTitle( const TitlePtr & title );
            const TitlePtr                      getTitle() const;

            void                                setDetail( const DetailPtr & detail );
            const DetailPtr                     getDetail() const;

            void                                setParameter( const QString & name, const QVariant & value );
            void                                setParameters( const QMap< QString, QVariant > & parameters );
            const QVariant                      getParameter( const QString & name ) const;
            const QMap< QString, QVariant >     getParameters() const;

            void    setRowCount( int count );
            int     getRowCount() const;

            void                    setOrientation( QPrinter::Orientation orientation );
            QPrinter::Orientation   getOrientation() const;

            void            setSize( const QSize & size );
            const QSize     getSize() const;

            void            setWidth( int width );
            int             getWidth() const;

            void            setHeight( int height );
            int             getHeight() const;

            void    setLeftMargin( int left );
            int     getLeftMargin() const;

            void    setTopMargin( int top );
            int     getTopMargin() const;

            void    setRightMargin( int right );
            int     getRightMargin() const;

            void    setBottomMargin( int bottom );
            int     getBottomMargin() const;

            void            setMargins( int left, int top, int right, int bottom );
            void            setMargins( const QMargins & margins );
            const QMargins  getMargins() const;

        private:
            QPrinter::Orientation	    m_orientation;
            QSize	                    m_size;
            QMargins                    m_margins;
            int                         m_rowCount;
            StylePtr                    m_defaultStyle;
            QMap< QString, StylePtr >   m_styles;
            QString                     m_query;
            QMap< QString, FieldPtr >   m_fields;
            TitlePtr                    m_title;
            DetailPtr                   m_detail;
            QMap< QString, QVariant >   m_parameters;

        };
        typedef QSharedPointer< Report > ReportPtr;

    }
}

#endif // REPORT_HPP
