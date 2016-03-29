#include "band.hpp"

namespace qtreports {
    namespace detail {

        Band::Band() {}

        Band::~Band() {}

        void    Band::addStaticText( const StaticTextPtr & staticText ) {
            m_staticTexts.append( staticText );
        }

        const StaticTextPtr  Band::getStaticText( int index ) const {
            return m_staticTexts.at( index );
        }

        int     Band::getStaticTextsSize() const {
            return m_staticTexts.size();
        }

        const QVector< StaticTextPtr >    Band::getStaticTexts() const {
            return m_staticTexts;
        }

        void    Band::addTextField( const TextFieldPtr & staticText ) {
            m_textFields.append( staticText );
        }

        const TextFieldPtr  Band::getTextField( int index ) const {
            return m_textFields.at( index );
        }

        int     Band::getTextFieldsSize() const {
            return m_textFields.size();
        }

        const QVector< TextFieldPtr >    Band::getTextFields() const {
            return m_textFields;
        }

        void    Band::addLine( const LinePtr & line )
        {
            m_lines.append( line );
        }

        const LinePtr  Band::getLine( int index ) const
        {
            return m_lines.at( index );
        }

        int     Band::getLinesSize() const
        {
            return m_lines.size();
        }

        const QVector< LinePtr >    Band::getLines() const
        {
            return m_lines;
        }

        void    Band::addRect( const RectPtr & rect )
        {
            m_rects.append( rect );
        }

        const RectPtr  Band::getRect( int index ) const
        {
            return m_rects.at( index );
        }

        int     Band::getRectsSize() const
        {
            return m_rects.size();
        }

        const QVector< RectPtr >    Band::getRects() const
        {
            return m_rects;
        }
    }
}
