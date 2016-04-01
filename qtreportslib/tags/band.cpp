#include "band.hpp"

namespace qtreports {
    namespace detail {

        Band::Band() {}

        Band::~Band() {}

        void    Band::addStaticText( const StaticTextPtr & staticText ) {
            m_staticTexts.append( staticText );
        }

        const QVector< StaticTextPtr >    Band::getStaticTexts() const
        {
            return m_staticTexts;
        }

        const StaticTextPtr  Band::getStaticText( int index ) const {
            return getStaticTexts().value( index );
        }

        int     Band::getStaticTextsSize() const {
            return getStaticTexts().size();
        }

        void    Band::addTextField( const TextFieldPtr & staticText ) {
            m_textFields.append( staticText );
        }

        const QVector< TextFieldPtr >    Band::getTextFields() const
        {
            return m_textFields;
        }

        const TextFieldPtr  Band::getTextField( int index ) const {
            return getTextFields().value( index );
        }

        int     Band::getTextFieldsSize() const {
            return getTextFields().size();
        }

        QVector< TextWidgetPtr >    Band::getTextWidgets() const
        {
            QVector< TextWidgetPtr > textWidgets;
            //Slooooow
            for( auto && widget : getStaticTexts() )
            {
                textWidgets.append( widget );
            }
            for( auto && widget : getTextFields() )
            {
                textWidgets.append( widget );
            }

            return textWidgets;
        }

        int     Band::getTextWidgetsSize() const
        {
            return getTextWidgets().size();
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
