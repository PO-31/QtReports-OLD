#pragma once
#ifndef STYLE_HPP
#define STYLE_HPP

#include <QString>
#include <QColor>
#include <QSharedPointer>

#include "object.hpp"

namespace qtreports {
    namespace detail {

        class Style : public Object {
                 
        public:
            Style();
            ~Style();

            bool	isDefault() const; // Является ли данный стиль стилем по умолчанию
            void	setDefault( bool flag );

            int		fontSize() const; // Размер шрифта
            void	setFontSize( int size );

            QColor	fontColor() const; // Цвет шрифта
            void	setFontColor( const QColor & color );

            QString	fontName() const; // Имя шрифта
            void	setFontName( const QString & name );

            bool	isBold() const; // Жирный шрифт
            void	setBold( bool flag );

            bool	isItalic() const; // Курсив
            void	setItalic( bool flag );

        protected:
            int         m_id;
            bool        m_isDefault;
            bool        m_isBold;
            bool        m_isItalic;
            int         m_fontSize;
            QColor      m_fontColor;
            QString     m_fontName;

        };
        typedef QSharedPointer< Style > StylePtr;

    }
}

#endif // STYLE_HPP
