#include "style.hpp"

namespace qtreports {
    namespace detail {

        Style::Style() : Style( -1 ) {}

        Style::Style( int id ) :
            m_id( id ),
            m_isDefault( false ),
            m_isBold( false ),
            m_isItalic( false ),
            m_fontSize( 12 ) {}

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
            return m_isDefault;
        }

        void Style::setDefault( bool flag )
        {
            m_isDefault = flag;
        }

        int Style::fontSize() const
        {
            return m_fontSize;
        }

        void Style::setFontSize( int size )
        {
            m_fontSize = size;
        }

        QColor Style::fontColor() const
        {
            return m_fontColor;
        }

        void Style::setFontColor( const QColor &color )
        {
            m_fontColor = color;
        }

        QString Style::fontName() const
        {
            return m_fontName;
        }

        void Style::setFontName( const QString &name )
        {
            m_fontName = name;
        }

        bool Style::isBold() const
        {
            return m_isBold;
        }

        void Style::setBold( bool flag )
        {
            m_isBold = flag;
        }

        bool Style::isItalic() const
        {
            return m_isItalic;
        }

        void Style::setItalic( bool flag )
        {
            m_isItalic = flag;
        }

    }
}
