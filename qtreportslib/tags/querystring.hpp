#pragma once
#ifndef QUERYSTRING_HPP
#define QUERYSTRING_HPP
#include <QSharedPointer>
#include "object.hpp"

namespace qtreports {
    namespace detail {


        /*! @~russian
        @brief Класс, реализующий тэг <QueryString>
        Класс, реализующий тэг <QueryString>
        */
        class QueryString : public Object {
              
        public:
            QueryString();
            ~QueryString();

            /*! @~russian
            Задать Text
            @param[in] text значение
            */
            void            setText( const QString & text );
            /*! @~russian
            Получить Text
            */            
            const QString   getText() const;

        private:
            QString     m_text;

        };
        typedef QSharedPointer< QueryString > QueryStringPtr;

    }
}

#endif // QUERYSTRING_HPP
