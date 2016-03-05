#include "style.hpp"

namespace qtreports {
    namespace detail {

        Style::Style() : 
            m_isDefault( false ),
            m_isBold( false ),
            m_isItalic( false ),
            m_fontSize( 12 ) {}

        Style::~Style() {}

        bool    Style::isDefault() const {
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
