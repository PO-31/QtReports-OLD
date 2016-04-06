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
        
        
        /*! @~russian
        @brief Класс, реализующий тэг <Field>
        Класс, реализующий тэг <Field>
        */
        class Field : public Object {

        public:
            Field();
            ~Field();


            /*! @~russian
            Задаем ClassName
            @param[in] name 
            */
            void            setClassName( const QString & name );

            /*! @~russian
            Получаем ClassName.
            */            
            const QString   getClassName() const;


            /*! @~russian
            Задаем Data
            @param[in] data 
            */
            void            setData( const QVector< QVariant > & data );


            /*! @~russian
            Получить номер строки.
            @param[in] row номер
            */
            QString         getData( int row );

            template< typename T1 >
            const T1        getData( int row )
            {
                return m_data.value( row ).value< T1 >();
            }


            /*! @~russian
            Получить количесвто строк
            */
            int getRowCount();

        private:
            QString     m_className;

            QVector < QVariant > m_data;
        };

        typedef QSharedPointer< Field > FieldPtr;
    }
}

#endif // FIELD_HPP
