#pragma once
#ifndef PROCESSEDDB_HPP
#define PROCESSEDDB_HPP
#include <QString>
#include <QVariant>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlField>

namespace qtreports {
	namespace detail {

		/* Обработанные запросы к БД и параметры. */
		class ProcessedDB {

		public:
			ProcessedDB();
			~ProcessedDB();

            QVariant	getParam( const QString & name ) ;
            bool    	getField(const QString & queryName, const QString & columnName, int row , QVariant &result);
            bool    	getField( const QString & queryName, int column, int row, QVariant &result);

            void        addParam( const QString & name, const QVariant & value);
            void        addExecutedQuery(const QString & name, QSqlQueryModel *model);

            QString     getError() const;

        private:
            QString                         m_errorString;

            QMap <QString, QSqlQueryModel*> m_queriesResults;
		};

	}
}

#endif // PROCESSEDDB_HPP
