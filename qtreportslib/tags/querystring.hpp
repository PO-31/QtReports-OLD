#pragma once
#ifndef QUERYSTRING_HPP
#define QUERYSTRING_HPP
#include <QSharedPointer>
#include "object.hpp"

namespace qtreports {
    namespace detail {

        class QueryString : public Object {
              
        public:
            QueryString();
            ~QueryString();

            void            setText( const QString & text );
            const QString   getText() const;

        private:
            QString     m_text;

        };
        typedef QSharedPointer< QueryString > QueryStringPtr;

    }
}

#endif // QUERYSTRING_HPP
