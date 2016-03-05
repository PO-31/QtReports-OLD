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

    }
}
