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

            void                            addStaticText( const StaticTextPtr & staticText );//Добавить StaticText
            const QVector< StaticTextPtr >  getStaticTexts() const;//Получить StaticText
            const StaticTextPtr             getStaticText( int index ) const;//Получить индекс StaticText
            int                             getStaticTextsSize() const;//Получить размер StaticText

            void                            addTextField( const TextFieldPtr & staticText );//Добавить Field
            const QVector< TextFieldPtr >   getTextFields() const;//Получить Field
            const TextFieldPtr              getTextField( int index ) const;//Получить индекс Field
            int                             getTextFieldsSize() const;//Получить размер Field

            int                             getTextWidgetsSize() const;//Получить размер TextWidgets
            QVector< TextWidgetPtr >        getTextWidgets() const;//Получить TextWidgets

            void                            addLine( const LinePtr & line );//Добавить Line
            const LinePtr                   getLine( int index ) const;//Получить индекс Line
            int                             getLinesSize() const;//Получить размер Line
            const QVector< LinePtr >        getLines() const;//Получить Lines

            void                            addRect( const RectPtr & rect );//Добавить Rect
            const RectPtr                   getRect( int index ) const;//Получить индекс Rect
            int                             getRectsSize() const;//Получить размер Rect
            const QVector< RectPtr >        getRects() const;//Получить Rects

            void                            addEllipse( const EllipsePtr & rect );//Добавить Ellipse
            const EllipsePtr                getEllipse( int index ) const;//Получить индекс Ellipse
            int                             getEllipsesSize() const;//Получить размер Ellipse
            const QVector< EllipsePtr >     getEllipses() const;//Получить Ellipses

            void                            addImage( const ImagePtr & rect );//Добавить Image
            const ImagePtr                  getImage( int index ) const;//Получить индекс Image
            int                             getImagesSize() const;//Получить размер Image
            const QVector< ImagePtr >       getImages() const;//Получить Images

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
