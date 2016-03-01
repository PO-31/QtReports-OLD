#include "style.hpp"

namespace qtreports {
    namespace detail {

        Style::Style() : Style( -1 ) {}
        Style::Style( int id ) : m_id( id ), m_is_default( false ), m_is_bold( false ), m_is_italic( false ) {}

        int Style::id() const
        {
            return m_id;
        }

        void Style::setId( int id )
        {
            m_id = id;
        }

        QString Style::getName() const
        {
            return m_name;
        }

        void Style::setName( const QString &name )
        {
            m_name = name;
        }

        bool Style::isDefault() const
        {
            return m_is_default;
        }

        void Style::setDefault( bool flag )
        {
            m_is_default = flag;
        }

        int Style::fontSize() const
        {
            return m_font_size;
        }

        void Style::setFontSize( int size )
        {
            m_font_size = size;
        }

        QColor Style::fontColor() const
        {
            return m_font_color;
        }

        void Style::setFontColor( const QColor &color )
        {
            m_font_color = color;
        }

        QString Style::fontName() const
        {
            return m_font_name;
        }

        void Style::setFontName( const QString &name )
        {
            m_font_name = name;
        }

        bool Style::isBold() const
        {
            return m_is_bold;
        }

        void Style::setBold( bool flag )
        {
            m_is_bold = flag;
        }

        bool Style::isItalic() const
        {
            return m_is_italic;
        }

        void Style::setItalic( bool flag )
        {
            m_is_italic = flag;
        }

    }
}
