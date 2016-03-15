#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <QObject>
#include <QString>
#include <QVariant>
#include <QMap>
#include <QVector>
#include <QSqlDatabase>
#include <QPrinter>
#include "parser.hpp"
#include "processeddb.hpp"
#include "tags/report.hpp"
#include "converters/convertertoqwidget.hpp"

/*! @~russian
@mainpage QtReports
Добро пожаловать в документацию проекта QtReports

@section intro_sec Введение
Хм.

@section install_sec Установка

@subsection step1 Шаг 1: Скачайте и установите.

@section use_sec Использование
Подключите библиотеку к проекту с помощью
-lqtreportslib -I/usr/include/qtreportslib
и вперед, навстречу приключениям!

*/

namespace qtreports {

    class Engine : public QObject {
        Q_OBJECT

    public:
        Engine( QObject * parent = Q_NULLPTR );
        Engine( const QString & path, QObject * parent = Q_NULLPTR );
        ~Engine();

        bool    open( const QString & path );
        bool    setParameters( const QMap< QString, QString > & map );
        bool    setConnection( const QSqlDatabase & connection );

        void    addQuery( const QString & queryName, const QString & query );
        void    addScript( const QString & script );

        bool                createPDF( const QString & path );
        bool                createHTML( const QString & path );//etc.
        const QWidgetPtr	createWidget();
        bool                print();
        
        bool        	    isOpened() const;
        const QString       getLastError() const;

    private:
        bool                        m_isOpened;
        QString                     m_lastError, m_compiledPath;
        detail::ReportPtr           m_report;
        QMap< QString, QString >    m_dbQueries;
        QVector< QString >          m_scripts;
        QSqlDatabase                m_dbConnection;
        detail::ProcessedDB         m_processedDB;

        void                drawPreview( QPrinter * printer );
        void                prepareDB();
        detail::QSqlQueryModelPtr   executeQuery( const QString & query );

    };

}
#endif // ENGINE_HPP
