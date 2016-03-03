#pragma once
#ifndef PROCESSEDDB_HPP
#define PROCESSEDDB_HPP
#include <QString>
#include <QVariant>
#include <QSqlQueryModel>
#include <QSharedPointer>

namespace qtreports {
    namespace detail {
        typedef QSharedPointer< QSqlQueryModel > QSqlQueryModelPtr;

        /* Обработанные запросы к БД и параметры. */
        class ProcessedDB {

        public:
            ProcessedDB();
            ~ProcessedDB();

            bool        getParam( const QString & name, QVariant & result );
            bool        getField( const QString & queryName, const QString & columnName, int row, QVariant &result );
            bool        getField( const QString & queryName, int column, int row, QVariant & result );

            void        addParam( const QString & name, const QVariant & value );
            void        addExecutedQuery( const QString & name, const QSqlQueryModelPtr & model );

            const QString   getError() const;

        private:
            QString                             m_errorString;
            QMap< QString, QSqlQueryModelPtr >  m_queriesResults;

        };

    }
}

#endif // PROCESSEDDB_HPP
