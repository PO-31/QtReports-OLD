﻿#include <QTest>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QRegularExpression>
#include <QFileSystemModel>
#include <engine.hpp>
#include "test_engine.hpp"
#include <QDebug>

Test_Engine::Test_Engine( QObject * parent ) :
    QObject( parent ) {}

Test_Engine::~Test_Engine() {}

void    Test_Engine::engine()
{
    qtreports::Engine emptyEngine( "" );
    QCOMPARE( emptyEngine.isOpened(), false );

    QString reportPath = QFINDTESTDATA( "default.qreport" );
    //qDebug() << endl << "Used report: " << reportPath;
    qtreports::Engine engine( reportPath );
    QVERIFY2( engine.isOpened(), engine.getLastError().toStdString().c_str() );
}

void    Test_Engine::open() {
    qtreports::Engine engine;
    QCOMPARE( engine.open( "" ), false );

    QString reportPath = QFINDTESTDATA( "default.qreport" );
    //qDebug() << endl << "Used report: " << reportPath;
    QVERIFY2( engine.open( reportPath ), engine.getLastError().toStdString().c_str() );

    QVERIFY2( engine.open( reportPath ), engine.getLastError().toStdString().c_str() );

    QString erroredReportPath = QFINDTESTDATA( "errored.qrxml" );
    //qDebug() << endl << "Used report: " << erroredReportPath;
    QCOMPARE( engine.open( erroredReportPath ), false );
}

void    Test_Engine::close()
{
    QString reportPath = QFINDTESTDATA( "default.qreport" );
    //qDebug() << endl << "Used report: " << reportPath;
    qtreports::Engine engine;
    QVERIFY2( engine.open( reportPath ), engine.getLastError().toStdString().c_str() );

    QCOMPARE( engine.isOpened(), true );
    engine.close();
    QCOMPARE( engine.isOpened(), false );
}

void    Test_Engine::setParameters()
{
    QMap < QString, QVariant > map;
    map[ "title" ] = "Best Title in World";
    //qDebug() << endl << "Used map: " << map;

    qtreports::Engine engine;
    QCOMPARE( engine.setParameters( map ), false );

    QString reportPath = QFINDTESTDATA( "full.qrxml" );
    //qDebug() << endl << "Used report: " << reportPath;
    QVERIFY2( engine.open( reportPath ), engine.getLastError().toStdString().c_str() );

    QVERIFY2( engine.setParameters( map ), engine.getLastError().toStdString().c_str() );
}

void    Test_Engine::setConnection() {
    qtreports::Engine engine;

    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    QCOMPARE( engine.setConnection( db ), false );

    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );
    QCOMPARE( engine.setConnection( db ), false );

    db.setDatabaseName( "testDB" );
    QVERIFY2( db.open(), ( "Can't open database. Error: " + db.lastError().text() ).toStdString().c_str() );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );

    /*
    QSqlQuery q;
    q.exec("select * from groups_t;");
    while (q.next()) {
    qDebug() << q.value(1).toString();
    }
    */
}

void    Test_Engine::setDataSource()
{
    qtreports::Engine engine;
    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QMap< QString, QVector< QVariant > > data;

    QVector< QVariant > ids;
    ids << 1 << 2 << 3;
    data[ "id" ] = ids;

    QVector< QVariant > firstnames;
    firstnames << "first" << "second" << "three";
    data[ "firstname" ] = firstnames;

    QVector< QVariant > lastnames;
    lastnames << "" << "" << "";
    data[ "lastname" ] = lastnames;

    QVector< QVariant > citys;
    citys << "" << "" << "";
    data[ "city" ] = citys;

    QVector< QVariant > segments;
    segments << "" << "" << "";
    data[ "segment" ] = segments;
    QVERIFY2( engine.setDataSource( data ), engine.getLastError().toStdString().c_str() );
}

void    Test_Engine::setQuery()
{
    qtreports::Engine engine;
    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "testDB" );

    QVERIFY2( db.open(), "Can't open test database 'testDB'" );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );
    QVERIFY2( engine.setQuery( "select * from customers" ), engine.getLastError().toStdString().c_str() );
}

void    Test_Engine::addScript()
{
    qtreports::Engine engine;
    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );
    QVERIFY2( engine.addScript( "test" ), engine.getLastError().toStdString().c_str() );
}

void    Test_Engine::setDataModel()
{
    qtreports::Engine engine;
    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );
    QVERIFY2( engine.setDataModel( QFileSystemModel() ), engine.getLastError().toStdString().c_str() );
}

void    Test_Engine::createPDF()
{
    qtreports::Engine engine;

    QCOMPARE( engine.createPDF( "test.pdf" ), false );

    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "testDB" );

    QVERIFY2( db.open(), "Can't open test database 'testDB'" );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );

    QString outPath = "test.pdf";
    QVERIFY2( engine.createPDF( outPath ), engine.getLastError().toStdString().c_str() );

    QCOMPARE( QFile::exists( outPath ), true );
    QFile file( outPath );
    QVERIFY2( file.open( QIODevice::OpenModeFlag::ReadOnly ), file.errorString().toStdString().c_str() );
    QVERIFY( file.size() != 0 );
    file.close();
    QCOMPARE( QFile::remove( outPath ), true );
}

void Test_Engine::createHTML()
{
    qtreports::Engine engine;
    QString outPath = "test.html";

    QCOMPARE( engine.createHTML( outPath ), false );

    QString input = QFINDTESTDATA( "html.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "testDB" );

    QVERIFY2( db.open(), "Can't open test database 'testDB'" );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );

    QVERIFY2( engine.createHTML( outPath ), engine.getLastError().toStdString().c_str() );

    QCOMPARE( QFile::exists( outPath ), true );
    QFile file( outPath );
    QVERIFY2( file.open( QIODevice::OpenModeFlag::ReadOnly ), file.errorString().toStdString().c_str() );
    QVERIFY( file.size() != 0 );
    file.close();
    QCOMPARE( QFile::remove( outPath ), true );
}

void    Test_Engine::createWidget()
{
    qtreports::Engine engine;

    QCOMPARE( engine.createWidget(), qtreports::QWidgetPtr() );

    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "testDB" );

    QVERIFY2( db.open(), "Can't open test database 'testDB'" );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );

    QVERIFY2( engine.createWidget() != qtreports::QWidgetPtr(), engine.getLastError().toStdString().c_str() );
}

void    Test_Engine::createLayout()
{
    qtreports::Engine engine;

    QCOMPARE( engine.createLayout(), qtreports::QWidgetPtr() );

    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "testDB" );

    QVERIFY2( db.open(), "Can't open test database 'testDB'" );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );

    QVERIFY2( engine.createLayout() != qtreports::QWidgetPtr(), engine.getLastError().toStdString().c_str() );
}

void    Test_Engine::print()
{
    qtreports::Engine engine;

    QCOMPARE( engine.print(), false );

    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "testDB" );

    QVERIFY2( db.open(), "Can't open test database 'testDB'" );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );
    //QTRY_VERIFY2_WITH_TIMEOUT( engine.print(), engine.getLastError().toStdString().c_str(), 5 );
}

void    Test_Engine::isOpened()
{
    qtreports::Engine engine;

    QCOMPARE( engine.isOpened(), false );

    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QCOMPARE( engine.isOpened(), true );
}

void    Test_Engine::getReport()
{
    qtreports::Engine engine;

    QCOMPARE( engine.getReport(), qtreports::detail::ReportPtr() );

    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "testDB" );

    QVERIFY2( db.open(), "Can't open test database 'testDB'" );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );

    QVERIFY2( engine.getReport() != qtreports::detail::ReportPtr(), engine.getLastError().toStdString().c_str() );

}

void    Test_Engine::getLastError()
{
    qtreports::Engine engine;

    QCOMPARE( engine.getLastError(), QString() );
}

