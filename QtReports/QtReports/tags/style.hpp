#pragma once
#ifndef STYLE_HPP
#define STYLE_HPP

#include <QString>
#include <QColor>

namespace qtreports {
	namespace detail {

		class Style {
		public:
			Style();

			const int		id() const;
			void			setId( int id );

			const QString	getName() const;
			void			setName( const QString & name );

			const bool		isDefault() const; // Является ли данный стиль стилем по умолчанию
			void			setDefault( bool flag );

			const int		fontSize() const; // Размер шрифта
			void			setFontSize( int size );

			const QColor	fontColor() const; // Цвет шрифта
			void			setFontColor( const QColor & color );

			const QString	fontName() const; // Имя шрифта
			void			setFontName( const QString & name );

			const bool		isBold() const; // Жирный шрифт
			void			setBold( bool flag );

			const bool		isItalic() const; // Курсив
			void			setItalic( bool flag );

		};

	}
}

#endif // STYLE_HPP
