#include <algorithm>
#include <QPair>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlField>
#include "processeddb.hpp"

namespace qtreports
{
    namespace detail
    {

        ProcessedDB::ProcessedDB() {}

        ProcessedDB::~ProcessedDB() {}

        void    ProcessedDB::setParameter( const QString &name, const QVariant & value )
        {
            m_parametersMap[ name ] = value;
        }

        void    ProcessedDB::setParameters( const QMap< QString, QVariant > & map )
        {
            m_parametersMap = map;
        }

        const QVariant  ProcessedDB::getParameter( const QString & name ) const
        {
            return m_parametersMap.value( name );
        }

        const QMap< QString, QVariant >     ProcessedDB::getParameters() const
        {
            return m_parametersMap;
        }

        const QVariant  ProcessedDB::getFieldData( const QString & columnName, int row ) const
        {
            return getColumn( columnName ).value( row );
        }

        const QVariant  ProcessedDB::getFieldData( int column, int row ) const
        {
            return getFieldData( getColumnName( column ), row );
        }

        void    ProcessedDB::appendColumnData( const QString & columnName, const QVariant & data )
        {
            if( m_columnsSet.contains( columnName ) )
            {
                m_columnsSet[ columnName ].append( data );
            }
        }

        void    ProcessedDB::appendColumnData( int column, const QVariant & data )
        {
            appendColumnData( getColumnName( column ), data );
        }

        void    ProcessedDB::appendColumnData( const QString & columnName, const QVector< QVariant > & data )
        {
            if( m_columnsSet.contains( columnName ) )
            {
                m_columnsSet[ columnName ] += data;
            }
        }

        void    ProcessedDB::appendColumnData( int column, const QVector< QVariant > & data )
        {
            appendColumnData( getColumnName( column ), data );
        }

        void    ProcessedDB::addEmptyColumn( const QString & name )
        {
            if( !m_columnsSet.contains( name ) )
            {
                m_columnsSet[ name ] = QVector< QVariant >();
            }
        }

        void    ProcessedDB::addEmptyColumn( int column )
        {
            addEmptyColumn( getColumnName( column ) );
        }

        const QVector<QVariant>     ProcessedDB::getColumn( const QString & name ) const
        {
            return m_columnsSet.value( name );
        }

        const QVector< QVariant >   ProcessedDB::getColumn( int column ) const
        {
            return getColumn( getColumnName( column ) );
        }

        QString     ProcessedDB::getColumnName( int column ) const
        {
            return m_columnsSet.keys().value( column );
        }

        int     ProcessedDB::getColumnIndex( const QString & name ) const
        {
            if( !columnIsExists( name ) )
            {
                return -1;
            }

            return std::distance( m_columnsSet.begin(), m_columnsSet.find( name ) );
        }

        bool    ProcessedDB::columnIsExists( const QString & name ) const
        {
            return m_columnsSet.contains( name );
        }

        bool    ProcessedDB::columnIsExists( int column ) const
        {
            return columnIsExists( getColumnName( column ) );
        }

        int     ProcessedDB::getRowCount( const QString & columnName ) const
        {
            return m_columnsSet.value( columnName ).size();
        }

        int     ProcessedDB::getRowCount( int column ) const
        {
            return getRowCount( getColumnName( column ) );
        }

        int     ProcessedDB::getMaxRowCount() const
        {
            int max = 0;
            for( auto && column : m_columnsSet )
            {
                max = std::max( max, column.size() );
            }

            return max;
        }

        const QString   ProcessedDB::getError() const
        {
            return m_errorString;
        }
    }
}

