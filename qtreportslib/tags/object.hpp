#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <QString>
#include <QVariant>
#include <QSharedPointer>

namespace qtreports {
    namespace detail {
        bool    isEquals( const QString & string1, const QString & string2 );

        /* Базовый интерфейс объекта для любого тэга. */
        class Object {

        public:
            Object();
            Object( const QString & name );
            virtual ~Object();

            void            setName( const QString & name );
            void            setTagName( const QString & name );
            //virtual bool    setParameter( const QString & name, const QVariant & value );

            const QString   getName() const;
            const QString   getTagName() const;
            const QString	getLastError() const;

        protected:
            QString     m_name;
            QString     m_tagName;
            QString     m_lastError;

        };
        typedef QSharedPointer< Object > ObjectPtr;

    }
}

#endif // OBJECT_HPP
