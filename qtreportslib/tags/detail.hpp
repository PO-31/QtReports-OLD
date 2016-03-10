#pragma once
#ifndef DETAIL_HPP
#define DETAIL_HPP
#include <QVector>
#include <QSharedPointer>
#include "object.hpp"
#include "band.hpp"

namespace qtreports {
    namespace detail {

        class Detail : public Object {

        public:
            Detail();
            ~Detail();

            void                        addBand( const BandPtr & band );
            const BandPtr               getBand( int index ) const;
            int                         getBandsSize() const;
            const QVector< BandPtr >    getBands() const;

        private:
            QVector< BandPtr >  m_bands;

        };
        typedef QSharedPointer< Detail > DetailPtr;

    }
}

#endif // DETAIL_HPP
