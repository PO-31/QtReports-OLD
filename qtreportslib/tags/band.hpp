#pragma once
#ifndef BAND_HPP
#define BAND_HPP
#include <QVector>
#include <QSharedPointer>
#include "statictext.hpp"
#include "textfield.hpp"
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

        private:
            QVector< StaticTextPtr >  m_staticTexts;
            QVector< TextFieldPtr >   m_textFields;

        };
        typedef QSharedPointer< Band > BandPtr;

    }
}

#endif // BAND_HPP
