#pragma once
#ifndef SECTION_HPP
#define SECTION_HPP
#include <QVector>
#include <QSharedPointer>
#include "object.hpp"
#include "band.hpp"

namespace qtreports {
    namespace detail {

        class Section : public Object {

        public:
            Section();
            ~Section();

            int                         getHeight();

            void                        addBand( const BandPtr & band );
            const BandPtr               getBand( int index ) const;
            int                         getBandsSize() const;
            const QVector< BandPtr >    getBands() const;

        protected:
            QVector< BandPtr >  m_bands;

        };
        typedef QSharedPointer< Section > SectionPtr;

    }
}

#endif // SECTION_HPP
