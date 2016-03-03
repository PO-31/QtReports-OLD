#include "processeddb.hpp"

namespace qtreports {
	namespace detail {

		ProcessedDB::ProcessedDB() {}

		ProcessedDB::~ProcessedDB() {}

        QVariant ProcessedDB::getParam( const QString & name ) {

			return QVariant();
		}

        bool ProcessedDB::getField( const QString & queryName, const QString & columnName, int row , QVariant & result) {
            if(!m_queriesResults.contains(queryName))
            {
                m_errorString = "No such query with name " + queryName;
                return false;
            }
            if(m_queriesResults[queryName]->rowCount() == 0)
            {
                m_errorString = "No data";
                return false;
            }

            QSqlRecord record = m_queriesResults[queryName]->record(row);

            result = record.field(columnName).value();

            if(!result.isValid())
            {
                m_errorString = "Result is not valid";
                return false;
            }

            return true;
		}

        bool ProcessedDB::getField(const QString & queryName, int column, int row , QVariant &result) {
            if(!m_queriesResults.contains(queryName))
            {
                m_errorString = "No such query with name ";
                return false;
            }
            if(m_queriesResults[queryName]->rowCount() == 0)
            {
                m_errorString = "No data";
                return false;
            }

            QSqlRecord record = m_queriesResults[queryName]->record(row);

            result = record.field(column).value();

            if(!result.isValid())
            {
                m_errorString = "Result is not valid";
                return false;
            }

            return true;
        }

        void ProcessedDB::addExecutedQuery(const QString &name, QSqlQueryModel *model)
        {
            m_queriesResults[name] = model;
        }

        QString ProcessedDB::getError() const
        {
            return m_errorString;
        }
	}
}

