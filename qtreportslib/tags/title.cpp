#include "title.hpp"

namespace qtreports {
    namespace detail {

        Title::Title() {}

        Title::~Title() {}

        void    Title::addBand( const BandPtr & band ) {
            m_bands.append( band );
        }

        const BandPtr  Title::getBand( int index ) const {
            return m_bands.at( index );
        }

        int     Title::getBandsSize() const {
            return m_bands.size();
        }

        const QVector< BandPtr >    Title::getBands() const {
            return m_bands;
        }

    }
}
