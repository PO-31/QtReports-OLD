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
            if( !m_queriesResults.contains( queryName ) ) {
                m_errorString = "No such query with name " + queryName;
                return false;
            }
            if( m_queriesResults[ queryName ]->rowCount() == 0 ) {
                m_errorString = "No data";
                return false;
            }

            QSqlRecord record = m_queriesResults[ queryName ]->record( row );

            result = record.field( columnName ).value();

            if( !result.isValid() ) {
                m_errorString = "Result is not valid";
                return false;
            }

            return true;
        }

        bool    ProcessedDB::getField( const QString & queryName, int column, int row, QVariant &result ) {
            if( !m_queriesResults.contains( queryName ) ) {
                m_errorString = "No such query with name ";
                return false;
            }
            if( m_queriesResults[ queryName ]->rowCount() == 0 ) {
                m_errorString = "No data";
                return false;
            }

            QSqlRecord record = m_queriesResults[ queryName ]->record( row );

            result = record.field( column ).value();

            if( !result.isValid() ) {
                m_errorString = "Result is not valid";
                return false;
            }

            return true;
        }

        void    ProcessedDB::addParam( const QString & name, const QVariant & value ) {
            Q_UNUSED( name );
            Q_UNUSED( value );
        }

        void    ProcessedDB::addExecutedQuery( const QString & name, const QSqlQueryModelPtr & model ) {
            m_queriesResults[ name ] = model;
        }

        const QString   ProcessedDB::getError() const {
            return m_errorString;
        }
    }
}

