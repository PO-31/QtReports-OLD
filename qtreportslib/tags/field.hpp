#pragma once
#ifndef FIELD_HPP
#define FIELD_HPP
#include <QSharedPointer>

#include <QVariant>
#include <QString>
#include <QVector>

#include "object.hpp"

namespace qtreports {
    namespace detail {
        class Field : public Object {

        public:
            Field();
            ~Field();

            void            setClassName( const QString & name );
            const QString   getClassName() const;

            void setData(const QVector < QVariant > & data);

            QString getData(int row);

            int getRowCount();

        private:
            QString     m_className;

            QVector < QVariant > m_data;
        };

        typedef QSharedPointer< Field > FieldPtr;
    }
}

#endif // FIELD_HPP
