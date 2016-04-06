#pragma once
#ifndef TITLE_HPP
#define TITLE_HPP
#include <QSharedPointer>
#include "section.hpp"

namespace qtreports {
    namespace detail {

        /*! @~russian
        @brief Класс, реализующий тэг <Title>
        Класс, реализующий тэг <Title>
        */
        class Title : public Section {

        public:
            Title();
            ~Title();

        private:

        };
        typedef QSharedPointer< Title > TitlePtr;

    }
}

#endif // TITLE_HPP
