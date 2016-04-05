#pragma once
#ifndef BAND_HPP
#define BAND_HPP
#include <QVector>
#include <QSharedPointer>
#include "statictext.hpp"
#include "textfield.hpp"
#include "line.hpp"
#include "rect.hpp"
#include "ellipse.hpp"
#include "image.hpp"
#include "widget.hpp"

namespace qtreports {
    namespace detail {

        class Band : public Widget {

        public:
            Band();
            ~Band();

            void                            addStaticText( const StaticTextPtr & staticText );
            const QVector< StaticTextPtr >  getStaticTexts() const;
            const StaticTextPtr             getStaticText( int index ) const;
            int                             getStaticTextsSize() const;

            void                            addTextField( const TextFieldPtr & staticText );
            const QVector< TextFieldPtr >   getTextFields() const;
            const TextFieldPtr              getTextField( int index ) const;
            int                             getTextFieldsSize() const;

            int                             getTextWidgetsSize() const;
            QVector< TextWidgetPtr >        getTextWidgets() const;

            void                            addLine( const LinePtr & line );
            const LinePtr                   getLine( int index ) const;
            int                             getLinesSize() const;
            const QVector< LinePtr >        getLines() const;

            void                            addRect( const RectPtr & rect );
            const RectPtr                   getRect( int index ) const;
            int                             getRectsSize() const;
            const QVector< RectPtr >        getRects() const;

            void                            addEllipse( const EllipsePtr & rect );
            const EllipsePtr                getEllipse( int index ) const;
            int                             getEllipsesSize() const;
            const QVector< EllipsePtr >     getEllipses() const;

            void                            addImage( const ImagePtr & rect );
            const ImagePtr                  getImage( int index ) const;
            int                             getImagesSize() const;
            const QVector< ImagePtr >       getImages() const;

        private:
            QVector< StaticTextPtr >    m_staticTexts;
            QVector< TextFieldPtr >     m_textFields;
            QVector< TextWidgetPtr >    m_textWidgets;
            QVector< LinePtr >          m_lines;
            QVector< RectPtr >          m_rects;
            QVector< EllipsePtr >       m_ellipses;
            QVector< ImagePtr >         m_images;

        };
        typedef QSharedPointer< Band > BandPtr;

    }
}

#endif // BAND_HPP
