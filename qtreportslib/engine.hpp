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

@section install_sec Установка

@subsection step1 Шаг 1: Подготовка исходных файлов проекта к утсановке.

1) Скачать исходные файлы проекта;
2) Создать папку QtReports;
3) В папке QtReports создать три папки: qtreportslib, qtreportsviewer и tests;
4) В папке tests создать папку qtreportslib_tests;
5) В папке qtreportslib создать папки converters и tags;
6) Скопировать файлы в соответствующие папки:

convertertohtml.cpp, convertertohtml.hpp,
convertertopdf.cpp, convertertopdf.hpp,
convertertoqwidget.cpp, convertertoqwidget.hpp в папку converters;

band.cpp, band.hpp,
detail.cpp, detail.hpp, 
drawingexception.cpp, drawingexception.hpp,
field.cpp, field.hpp,
querystring.cpp, querystring.hpp,
object.cpp, object.hpp,
report.cpp, report.hpp,
section.cpp, section.hpp,
statictext.cpp, statictext.hpp,
textfield.cpp, textfield.hpp,
style.cpp, style.hpp,
title.cpp, title.hpp,
widget.cpp, widget.hpp в папку tags;

engine.cpp, engine.hpp,
objectsplant.cpp, objectsplant.hpp,
painter.cpp, painter.hpp,
parser.cpp, parser.hpp,
processeddb.cpp, processeddb.hpp в папку qtreportslib;

main.cpp в папку qtreportsviewer;

detail.qreport, testDB в qtreportslib_tests

@subsection step2 Шаг 2: Генерация CMakeLists.

В корневой папке QtReports, где расположен CMakeLists.txt в командной строке запустить команду: 
cmake CMAKE_PREFIX_PATH="путь к qt5"  -G "MinGW Makefiles" -B./bin -H./

Пример пути к qt5: C:/Qt/5/5.5/mingw492_32

@subsection step3 Шаг 3: Компиляция проекта.

Windows:
Запустить команду: mingw32-make -C./bin

Linux: В директории ../QtReports/bin запустить команду make;

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

        /*! @~russian
            Загружает макет отчета из файла path
            @param[in] path полное имя макета отчета
        */
        bool    open( const QString & path );
        /*! @~russian
            Выгружает из оперативной памяти данные об отчете
        */
        bool    close();

        /*! @~russian
            Передает карту параметров в отчет, для успешной передачи параметров не обязатеьно загружать их описание с макетом отчета
            @param[in] map карта параметров в формате (<имя параметра>, <значение параметра>)
        */
        bool    setParameters( const QMap< QString, QString > & map );
        /*! @~russian
            Устанавливает источник данных для отчета из БД
            @param[in] connection соединение с БД
        */
        bool    setConnection( const QSqlDatabase & connection );
        /*! @~russian
            Устанавливает источник данных для отчета из таблицы полей
            @param[in] columnSet набор данных в формате (<имя столбца>, <вектор значений столбца>)
        */
        void    setDataSource( const QMap <QString, QVector <QVariant> > & columnsSet);

        /*! @~russian
            Устанавливает запрос, по которому будут заполнятся поля отчета
            @param[in] query запрос
        */
        void    setQuery( const QString & query );
        /*! @~russian
            Добавить скрипт для отчета
            @param[in] script скрипт
        */
        void    addScript( const QString & script );

        /*! @~russian
            Создает PDF документ отчета по указанному пути
            @param[in] path полное имя выходного документа
        */
        bool                createPDF( const QString & path );
        /*! @~russian
            Создает HTML документ отчета по указанному пути
            @param[in] path полное имя выходного документа
        */
        bool                createHTML( const QString & path );//etc.
        
        /*! @~russian
            Выводит отчет на виджет
        */
        const QWidgetPtr	createWidget();
        const QWidgetPtr	createLayout();
        bool                print();
        
        /*! @~russian
            Возвращает true в случае учпешной загрузки отчета, иначе - false
        */
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
        void                                prepareDB();
        void                                prepareDataSource();
        void                                fillColumnsFromReport();
        void                                executeQueries();
    };
}
#endif // ENGINE_HPP