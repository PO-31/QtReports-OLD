#include "textfield.hpp"

namespace qtreports {
    namespace detail {

        TextField::TextField() {}

        TextField::~TextField() {}

        void    TextField::setText( const QString & text ) {
            m_text = text;
        }

        const QString   TextField::getText() const {
            return m_text;
        }

    }
}
