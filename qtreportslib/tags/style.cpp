#include "style.hpp"

namespace qtreports {
    namespace detail {

        Style::Style() : 
            m_isDefault( false ),
            m_isBold( false ),
            m_isItalic( false ),
            m_fontSize( 12 ),
            m_isPDFEmbedded( false ) {}

        Style::~Style() {}

        bool    Style::isDefault() const {
            return m_isDefault;
        }

        void    Style::setAsDefault( bool flag ) {
            m_isDefault = flag;
        }

        int     Style::getFontSize() const {
            return m_fontSize;
        }

        void    Style::setFontSize( int size ) {
            m_fontSize = size;
        }

        const QColor    Style::getFontColor() const {
            return m_fontColor;
        }

        void    Style::setFontColor( const QColor & color ) {
            m_fontColor = color;
        }

        const QString   Style::getFontName() const {
            return m_fontName;
        }

        void    Style::setFontName( const QString &name ) {
            m_fontName = name;
        }

        const QString   Style::getPDFFontName() const {
            return m_pdfFontName;
        }

        void    Style::setPDFFontName( const QString & name ) {
            m_pdfFontName = name;
        }

        const QString   Style::getPDFEncoding() const {
            return m_pdfEncoding;
        }

        void    Style::setPDFEncoding( const QString & encoding ) {
            m_pdfEncoding = encoding;
        }

        bool    Style::isPDFEmbedded() const {
            return m_isPDFEmbedded;
        }

        void    Style::setPDFEmbedded( bool isEmbedded ) {
            m_isPDFEmbedded = isEmbedded;
        }

        bool    Style::isBold() const {
            return m_isBold;
        }

        void    Style::setBold( bool flag ) {
            m_isBold = flag;
        }

        bool    Style::isItalic() const {
            return m_isItalic;
        }

        void    Style::setItalic( bool flag ) {
            m_isItalic = flag;
        }

    }
}
