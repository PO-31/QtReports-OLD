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

        bool    ProcessedDB::getParam( const QString & name, QVariant & result )
        {
            if( m_parametersMap.contains( name ) )
            {
                m_errorString = "No parameter with name " + name;
                return false;
            }
            result = m_parametersMap[ name ];
            if( !result.isValid() )
            {
                m_errorString = "Invalid data";
                return false;
            }
            return true;
        }

        bool    ProcessedDB::getField( const QString & columnName, int row, QVariant & result )
        {
            if( !m_columnsSet.contains( columnName ) )
            {
                m_errorString = "No such column " + columnName;
                return false;
            }
            if( row < 0 || row >= m_columnsSet[ columnName ].size() )
            {
                m_errorString = "Invalid row index: " +
                    QString::number( row ) +
                    " . Row count: " + QString::number( m_columnsSet[ columnName ].size() );
                return false;
            }
            result = m_columnsSet[ columnName ][ row ];
            if( !result.isValid() )
            {
                m_errorString = "Invalid data";
                return false;
            }
            return true;
        }

        bool    ProcessedDB::getField( int column, int row, QVariant &result )
        {
            if( column >= m_columnsSet.size() )
            {
                m_errorString = "Invalid column index: " + QString::number( column ) + " . " +
                    "Column count: " + QString::number( m_columnsSet.size() );
                return false;
            }
            QMapIterator <QString, QVector <QVariant> > iterator( m_columnsSet );
            int index = 0;
            QString columnName;
            while( iterator.hasNext() )
            {
                iterator.next();
                if( index == column )
                {
                    columnName = iterator.key();
                    break;
                }
                index++;
            }
            if( row < 0 || row >= m_columnsSet[ columnName ].size() )
            {
                m_errorString = "Invalid row index: " +
                    QString::number( row ) +
                    " . Row count: " + QString::number( m_columnsSet[ columnName ].size() );
                return false;
            }
            result = m_columnsSet[ columnName ][ row ];
            if( !result.isValid() )
            {
                m_errorString = "Invalid data";
                return false;
            }
            return true;
        }

        void    ProcessedDB::addParam( const QString &name, const QVariant & value )
        {
            m_parametersMap[ name ] = value;
        }

        void    ProcessedDB::addFieldData( const QString &columnName, const QVariant &data )
        {
            if( m_columnsSet.contains( columnName ) )
            {
                m_columnsSet[ columnName ].append( data );
            }
        }

        void    ProcessedDB::addFieldData( const QString &columnName, const QVector<QVariant> &data )
        {
            if( m_columnsSet.contains( columnName ) )
            {
                m_columnsSet[ columnName ] += data;
            }
        }

        void ProcessedDB::addFieldData( int column, const QVariant &data )
        {
            if( column < m_columnsSet.size() )
            {
                QMapIterator <QString, QVector <QVariant> > iterator( m_columnsSet );
                int index = 0;
                while( iterator.hasNext() )
                {
                    iterator.next();
                    if( index == column )
                    {
                        m_columnsSet[ iterator.key() ].append( data );
                    }
                    index++;
                }
            }
        }

        void ProcessedDB::addColumn( const QString &name )
        {
            if( !m_columnsSet.contains( name ) )
            {
                m_columnsSet[ name ] = QVector <QVariant>( 0 );
            }
        }

        bool ProcessedDB::getColumn( const QString &name, QVector<QVariant> &result )
        {
            if( !m_columnsSet.contains( name ) )
            {
                m_errorString = "No such column: " + name;
                return false;
            }
            result = m_columnsSet[ name ];
            return true;
        }

        bool    ProcessedDB::getColumn( int col, QVector< QVariant > & result )
        {
            if( col < 0 || col >= m_columnsSet.size() )
            {
                m_errorString = QString( "Invalid column index: %1. Column count: %2" ).
                    arg( col ).arg( m_columnsSet.size() );
            }
            /*
            int index = 0;
            QMapIterator <QString, QVector <QVariant> > iterator( m_columnsSet );
            while( iterator.hasNext() )
            {
                iterator.next();
                if( index == col )
                {
                    result = m_columnsSet[ iterator.key() ];
                    return true;
                }
                index++;
            }
            
            m_errorString = "Column with index " + QString::number( col ) + " not found.";
            return false;
            */

            auto key = m_columnsSet.keys[ col ];
            return getColumn( key, result );
        }

        int ProcessedDB::getFieldIndex( const QString &name )
        {
            int index = 0;
            QMapIterator <QString, QVector <QVariant> > iterator( m_columnsSet );
            while( iterator.hasNext() )
            {
                iterator.next();
                if( iterator.key() == name )
                {
                    return index;
                }
                index++;
            }
            return -1;
        }

        int     ProcessedDB::getRowCount( const QString &columnName ) const
        {
            if( m_columnsSet.contains( columnName ) )
            {
                return -1;
            }
            return m_columnsSet[ columnName ].size();
        }

        int     ProcessedDB::getRowCount( int col ) const
        {
            /*
            int index = 0;
            QMapIterator <QString, QVector <QVariant> > iterator(m_columnsSet);
            while(iterator.hasNext()) {
                iterator.next();
                if(index == col) {
                    return iterator.value().size();
                }
                index++;
            }
            */
            if( col < 0 || col >= m_columnsSet.size() )
            {
                return -1;
            }

            return getRowCount( m_columnsSet.keys[ col ] );
        }

        int     ProcessedDB::getMaxRowCount() const
        {
            /*
            int max = 0;
            QMapIterator <QString, QVector <QVariant> > iterator(m_columnsSet);
            while(iterator.hasNext()) {
                iterator.next();
                if(iterator.value().size() > max) {
                    max = iterator.value().size();
                }
            }
            return max;
            */
            /*
            return std::max_element( m_columnsSet.begin(), m_columnsSet.end(),
            []( auto && first, auto && second ) {
                return first.size() < second.size();
            } )->size();
            */
            int max = -1;
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

