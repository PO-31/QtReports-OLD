#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <QObject>
#include <QString>
#include <QMap>
#include <QSqlDatabase>
#include <QPrinter>
#include "parser.hpp"
#include "processeddb.hpp"
#include "painter.hpp"
//#include "dbquery.h"
#include "tags/object.hpp"
#include "tags/report.hpp"

namespace qtreports {
    using namespace detail;

    class Engine : public QObject {

    public:
        Engine( QObject * parent = 0 );
        ~Engine();

        bool	compile( const QString & path );
        bool	setParameters( const QMap< QString, QString > & map );
        bool	setConnection( const QSqlDatabase & connection );

        void    addQuery( const QString &queryName, const QString & query );
        void    addScript( const QString & script );

        bool	createPDF( const QString & path );
        bool	createHTML( const QString & path );//etc.
        bool	print();

        const QString		getLastError() const;
        const QWidgetPtr	getWidget() const;
        const bool			isCompiled() const;


    private:
        QString		m_lastError, m_compiledPath;
        QWidgetPtr	m_widget;
        bool		m_isCompiled;

        QMap <QString, QString>             m_dbQueries;
        QVector<QString>                    m_scripts;

        QSqlDatabase    m_dbConnection;
        ProcessedDB     m_processedDB;

        void            drawPreview( QPrinter * printer );
        void            prepareDB();
        QSqlQueryModel* executeQuery( const QString & query );
    };

}
#endif // ENGINE_HPP
