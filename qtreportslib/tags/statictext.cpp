#include "statictext.hpp"

namespace qtreports {
    namespace detail {

        StaticText::StaticText() {}

        StaticText::~StaticText() {}

        void    StaticText::setText( const QString & text ) {
            m_text = text;
        }

        const QString   StaticText::getText() const {
            return m_text;
        }

    }
}
