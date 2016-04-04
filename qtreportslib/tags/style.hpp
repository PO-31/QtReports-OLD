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
            
            bool	        isDefault() const; // Является ли данный стиль стилем по умолчанию
            void	        setAsDefault( bool flag );

            const QString	getFontName() const; // Имя шрифта
            void	        setFontName( const QString & name );

            int		        getFontSize() const; // Размер шрифта
            void	        setFontSize( int size );

            const QColor	getFontColor() const; // Цвет шрифта
            void	        setFontColor( const QColor & color );

            bool	        isBold() const; // Жирный шрифт
            void	        setBold( bool flag );

            bool	        isItalic() const; // Курсив
            void	        setItalic( bool flag );

            bool	        isUnderline() const; // Подчеркивание
            void	        setUnderline( bool flag );

            bool	        isStrikeThrough() const; // Хз
            void	        setStrikeThrough( bool flag );

            const QString	getPDFFontName() const; // Имя шрифта
            void	        setPDFFontName( const QString & name );
            
            const QString	getPDFEncoding() const; // Имя шрифта
            void	        setPDFEncoding( const QString & encoding );
            
            bool	        isPDFEmbedded() const; // Имя шрифта
            void	        setPDFEmbedded( bool isEmbedded );

        private:
            bool        m_isDefault;
            bool        m_isBold;
            bool        m_isItalic;
            bool        m_isUnderline;
            bool        m_isStrikeThrough;
            int         m_fontSize;
            bool        m_isPDFEmbedded;
            QColor      m_fontColor;
            QString     m_fontName;
            QString     m_pdfFontName;
            QString     m_pdfEncoding;

        };
        typedef QSharedPointer< Style > StylePtr;

    }
}

#endif // STYLE_HPP
