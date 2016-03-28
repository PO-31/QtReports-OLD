#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <QObject>
#include <QString>
#include <QVariant>
#include <QMap>
#include <QVector>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlField>
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

@section install_sec Установка с помощью CMAKE

@subsection step1 Шаг 1: Распаковка проекта.

Скачать проект по ссылке https://github.com/PO-21/QtReports/archive/master.zip.

Распаковать архив в папку QtReports. 

(Полный путь к папке QtReports не должен содержать кириллицы)

@subsection step2 Шаг 2: Генерация CMakeLists.

В корневой папке QtReports, где расположен CMakeLists.txt в командной строке запустить команду: 

Для Windows:

cmake [CMAKE_PREFIX_PATH="путь к qt"]  -G "MinGW Makefiles" -B./bin -H./

Для Unix:

cmake [CMAKE_PREFIX_PATH="путь к qt"]  -G "Unix Makefiles" -B./bin -H./

Примечание:

При возникновении ошибки "By not providing "FindQt5Widgets.cmake" in CMAKE_MODULE_PATH this project

has asked CMake to find a package configuration file provided by

"Qt5Widgets", but CMake did not find one." необходимо добавить в команду блок [CMAKE_PREFIX_PATH="путь к qt"].

Пример для Windows:
cmake [CMAKE_PREFIX_PATH="C:/Qt/5.5/mingw492_32"]  -G "MinGW Makefiles" -B./bin -H./

Пример для Unix:

cmake CMAKE_PREFIX_PATH="/usr/lib/x86_64-linux-gnu/qt5"  -G "Unix Makefiles" -B./bin -H./


@subsection step3 Шаг 3: Компиляция проекта.

Windows:

Запустить команду: mingw32-make -C./bin

Linux: 

Запустить команду: make -C ./bin

Exe-файл будет расположен в папке qtreportsviewer

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
        bool    close();

        bool    setParameters( const QMap< QString, QString > & map );
        bool    setConnection( const QSqlDatabase & connection );
        bool    setDataSource( const QMap <QString, QVector <QVariant> > & columnsSet);
        bool    setQuery( const QString & query );
        bool    addScript( const QString & script );
        bool    setDataModel( const QAbstractItemModel & model );

        bool                createPDF( const QString & path );
        bool                createHTML( const QString & path );//etc.
        const QWidgetPtr	createWidget();
        const QWidgetPtr	createLayout();
        bool                print();
        
        bool        	    isOpened() const;
        const QString       getLastError() const;

    public:
        bool                                m_isOpened;
        QString                             m_lastError, m_compiledPath;
        detail::ReportPtr                   m_report;
        QStringList                         m_queriesList;
        QVector< QString >                  m_scripts;
        QSqlDatabase                        m_dbConnection;
        QWidgetPtr                          m_printedWidget;
        bool                                m_connectionIsSet;
        bool                                m_dataSourceIsSet;
        QMap <QString, QVector <QVariant> > m_dataSource;
        detail::ProcessedDB                 m_processedDB;

        void                                drawPreview( QPrinter * printer );
        bool                                prepareDB();
        void                                prepareDataSource();
        void                                fillColumnsFromReport();
        void                                executeQueries();
    };
}
#endif // ENGINE_HPP
