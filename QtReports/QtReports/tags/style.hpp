#pragma once
#ifndef STYLE_HPP
#define STYLE_HPP

#include <QString>
#include <QColor>

namespace qtreports {
	namespace detail {

		class Style {
		public:
            Style(int id);

			int		id() const;
			void	setId( int id );

			QString	getName() const;
			void	setName( const QString & name );

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

            int m_id;

            QString m_name;

            bool m_is_default;

            int m_font_size;

            QColor m_font_color;

            QString m_font_name;

            bool m_is_bold;

            bool m_is_italic;

		};

	}
}

#endif // STYLE_HPP
