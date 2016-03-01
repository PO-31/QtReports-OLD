#pragma once
#ifndef PROCESSEDDB_HPP
#define PROCESSEDDB_HPP
#include <QString>
#include <QVariant>

namespace qtreports {
    namespace detail {

        /* Обработанные запросы к БД и параметры. */
        class ProcessedDB {

        public:
            ProcessedDB();
            ~ProcessedDB();

            const QVariant	getParam( const QString & name ) const;
            const QVariant	getField( const QString & queryName, const QString & columnName, int row ) const;
            const QVariant	getField( const QString & queryName, int column, int row ) const;

        };

    }
}

#endif // PROCESSEDDB_HPP
