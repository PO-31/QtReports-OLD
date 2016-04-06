#pragma once
#ifndef FIELD_HPP
#define FIELD_HPP
#include <QSharedPointer>

#include <QVariant>
#include <QString>
#include <QVector>
#include <QImage>

#include "object.hpp"

namespace qtreports {
    namespace detail {
        class Field : public Object {

        public:
            Field();
            ~Field();

            void            setClassName( const QString & name );//Задать ClassName
            const QString   getClassName() const;//Получить

            void            setData( const QVector< QVariant > & data );//Задать Data

            QString         getData( int row );//Получить строку

            template< typename T1 >
            const T1        getData( int row )
            {
                return m_data.value( row ).value< T1 >();
            }

            int getRowCount();//Получить количество строк

        private:
            QString     m_className;

            QVector < QVariant > m_data;
        };

        typedef QSharedPointer< Field > FieldPtr;
    }
}

#endif // FIELD_HPP
