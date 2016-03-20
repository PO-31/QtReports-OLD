#include <QPair>
#include <QSqlRecord>
#include <QSqlField>
#include "processeddb.hpp"

namespace qtreports {
    namespace detail {

        ProcessedDB::ProcessedDB() {}

        ProcessedDB::~ProcessedDB() {}

        bool    ProcessedDB::getParam( const QString & name, QVariant & result ) {
            Q_UNUSED( name );
            Q_UNUSED( result );
            return false;
        }

        bool    ProcessedDB::getField( const QString & queryName, const QString & columnName, int row, QVariant & result ) {
            if( !m_queriesResultData.contains( queryName ) ) {
                m_errorString = "No such query with name ";
                return false;
            }
            if( m_queriesResultData[ queryName ].size() == 0 ) {
                m_errorString = "No data";
                return false;
            }

            if( row > m_queriesResultData[ queryName ].size() || row < 0) {
                m_errorString = "Invalid row index";
                return false;
            }

            QSqlRecord rec = m_queriesResultData[ queryName ][row];

            if(!rec.contains(columnName)) {
                m_errorString = "Invalid column name";
                return false;
            }

            result = rec.field(columnName).value();
            return true;
        }

        bool    ProcessedDB::getField( const QString & queryName, int column, int row, QVariant &result ) {
            if( !m_queriesResultData.contains( queryName ) ) {
                m_errorString = "No such query with name ";
                return false;
            }
            if( m_queriesResultData[ queryName ].size() == 0 ) {
                m_errorString = "No data";
                return false;
            }

            if( row > m_queriesResultData[ queryName ].size() || row < 0) {
                m_errorString = "Invalid row index";
                return false;
            }

            QSqlRecord rec = m_queriesResultData[ queryName ][row];

            if(column > rec.count() || column < 0) {
                m_errorString = "Invalid column index";
                return false;
            }

            result = rec.field(column).value();
            return true;
        }

        void    ProcessedDB::addParam( const QString & name, const QVariant & value ) {
            Q_UNUSED( name );
            Q_UNUSED( value );
        }

        void    ProcessedDB::addExecutedQuery( const QString & name, const QSqlQueryModelPtr & model ) {
            QVector <QSqlRecord> recordsList;
            for(int row = 0; row < model.data()->rowCount(); row++) {
                QSqlRecord rec = model.data()->record(row);
                recordsList.append(rec);
            }
            m_queriesResultData[ name ] = recordsList;
        }

        const QString   ProcessedDB::getError() const {
            return m_errorString;
        }
    }
}

