#include "section.hpp"

namespace qtreports {
    namespace detail {

        Section::Section() {}

        Section::~Section() {}

        int     Section::getHeight() {
            int height = 0;
            for( auto && band : getBands() ) {
                height += band->getHeight();
            }

            return height;
        }

        void    Section::addBand( const BandPtr & band ) {
            m_bands.append( band );
        }

        const BandPtr  Section::getBand( int index ) const {
            return m_bands.at( index );
        }

        int     Section::getBandsSize() const {
            return m_bands.size();
        }

        const QVector< BandPtr >    Section::getBands() const {
            return m_bands;
        }

    }
}
