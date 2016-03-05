#include "detail.hpp"

namespace qtreports {
    namespace detail {

        Detail::Detail() {}

        Detail::~Detail() {}

        void    Detail::addBand( const BandPtr & band ) {
            m_bands.append( band );
        }

        const BandPtr  Detail::getBand( int index ) const {
            return m_bands.at( index );
        }

        int     Detail::getBandsSize() const {
            return m_bands.size();
        }

        const QVector< BandPtr >    Detail::getBands() const {
            return m_bands;
        }

    }
}
