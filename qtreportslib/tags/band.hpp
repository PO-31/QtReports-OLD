#pragma once
#ifndef BAND_HPP
#define BAND_HPP
#include <QVector>
#include <QSharedPointer>
#include "statictext.hpp"
#include "textfield.hpp"
#include "line.hpp"
#include "rect.hpp"
#include "widget.hpp"

namespace qtreports {
    namespace detail {

        class Band : public Widget {

        public:
            Band();
            ~Band();

            void                            addStaticText( const StaticTextPtr & staticText );
            const StaticTextPtr             getStaticText( int index ) const;
            int                             getStaticTextsSize() const;
            const QVector< StaticTextPtr >  getStaticTexts() const;

            void                            addTextField( const TextFieldPtr & staticText );
            const TextFieldPtr              getTextField( int index ) const;
            int                             getTextFieldsSize() const;
            const QVector< TextFieldPtr >   getTextFields() const;

            void                            addLine( const LinePtr & line );
            const LinePtr                   getLine( int index ) const;
            int                             getLinesSize() const;
            const QVector< LinePtr >        getLines() const;

            void                            addRect( const RectPtr & rect );
            const RectPtr                   getRect( int index ) const;
            int                             getRectsSize() const;
            const QVector< RectPtr >        getRects() const;

        private:
            QVector< StaticTextPtr >    m_staticTexts;
            QVector< TextFieldPtr >     m_textFields;
            QVector< LinePtr >          m_lines;
            QVector< RectPtr >          m_rects;

        };
        typedef QSharedPointer< Band > BandPtr;

    }
}

#endif // BAND_HPP
