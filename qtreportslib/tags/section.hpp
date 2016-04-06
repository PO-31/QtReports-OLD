#pragma once
#ifndef SECTION_HPP
#define SECTION_HPP
#include <QVector>
#include <QSharedPointer>
#include "object.hpp"
#include "band.hpp"

namespace qtreports {
    namespace detail {

        /*! @~russian
        @brief Класс, реализующий тэг <>
        Класс, реализующий тэг <>
        */
        class Section : public Object {

        public:
            Section();
            ~Section();

            void                        setWidth( int width );
            int                         getWidth() const;

            int                         getHeight() const;

            void                        addBand( const BandPtr & band );
            const BandPtr               getBand( int index ) const;
            int                         getBandsSize() const;
            const QVector< BandPtr >    getBands() const;

        protected:
            QVector< BandPtr >  m_bands;
            int                 m_width;
            int                 m_height;

        };
        typedef QSharedPointer< Section > SectionPtr;

    }
}

#endif // SECTION_HPP
