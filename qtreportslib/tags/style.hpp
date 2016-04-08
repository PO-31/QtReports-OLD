#pragma once
#ifndef STYLE_HPP
#define STYLE_HPP

#include <QString>
#include <QColor>
#include <QSharedPointer>

#include "object.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, реализующий тэг <Style>
        Класс, реализующий тэг стиль
        */
        class Style : public Object {

        public:
            Style();
            ~Style();


            /*! @~russian
            Является ли данный стиль стилем по умолчанию
            */
            bool	        isDefault() const; // Является ли данный стиль стилем по умолчанию
            /*! @~russian
            Устанавливает стиль по умолчанию
            @param[in] flag - bool
            */            
            void	        setAsDefault( bool flag );


            /*! @~russian
            Получаем имя шрифта
            */
            const QString	getFontName() const; // Имя шрифта
            /*! @~russian
            Устанавливает имя шрифта
            @param[in] имя шрифта
            */            
            void	        setFontName( const QString & name );

            /*! @~russian
            Получаем размер шрифта
            */
            int		        getFontSize() const; // Размер шрифта
            /*! @~russian
            Устанавливает размер шрифта
            @param[in] размер шрифта
            */  
            void	        setFontSize( int size );

            /*! @~russian
            Получаем цвет шрифта
            */
            const QColor	getFontColor() const; // Цвет шрифта
            /*! @~russian
            Устанавливает цвет шрифта
            @param[in] цвет шрифта
            */
            void	        setFontColor( const QColor & color );

            /*! @~russian
            Шрифт жирный?
            */
            bool	        isBold() const; // Жирный шрифт
             /*! @~russian
            Устанавливает шрифт жирным
            @param[in] флаг отвечающий за включение или отключение жирности
            */
            void	        setBold( bool flag );

            /*! @~russian
            Шрифт курсив?
            */
            bool	        isItalic() const; // Курсив
             /*! @~russian
            Устанавливает шрифт курсивным
            @param[in] флаг отвечающий за включение или отключение курсива
            */
            void	        setItalic( bool flag );

            /*! @~russian
            Шрифт подчеркнут?
            */
            bool	        isUnderline() const; // Подчеркивание
             /*! @~russian
            Устанавливает шрифт подчеркнутым
            @param[in] флаг отвечающий за включение или отключение подчеркивание
            */
            void	        setUnderline( bool flag );

            bool	        isStrikeThrough() const; // Хз
            void	        setStrikeThrough( bool flag );

            /*! @~russian
            Получаем имя шрифта в PDF
            */
            const QString	getPDFFontName() const; // Имя шрифта
            /*! @~russian
            Устанавливает имя шрифта в PDF
            @param[in] имя шрифта
            */  
            void	        setPDFFontName( const QString & name );

            /*! @~russian
            Получаем имя шрифта в PDF
            */
            const QString	getPDFEncoding() const; // Имя шрифта
             /*! @~russian
            Устанавливает имя шрифта в PDF
            @param[in] имя шрифта
            */  
            void	        setPDFEncoding( const QString & encoding );

            bool	        isPDFEmbedded() const; // Имя шрифта
            /*! @~russian
            Устанавливает имя шрифта в PDF
            @param[in] имя шрифта
            */              
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
