#pragma once
#ifndef TITLE_HPP
#define TITLE_HPP
#include <QVector>
#include <QSharedPointer>
#include "object.hpp"
#include "band.hpp"

namespace qtreports {
    namespace detail {

        class Title : public Object {

        public:
            Title();
            ~Title();

            void                        addBand( const BandPtr & band );
            const BandPtr               getBand( int index ) const;
            int                         getBandsSize() const;
            const QVector< BandPtr >    getBands() const;

        private:
            QVector< BandPtr >  m_bands;

        };
        typedef QSharedPointer< Title > TitlePtr;

    }
}

#endif // TITLE_HPP
