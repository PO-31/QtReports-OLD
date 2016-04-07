#include <QTest>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QRegularExpression>
#include <QFileSystemModel>
#include <engine.hpp>
#include "test_engine.hpp"
#include <QDebug>

Test_Engine::Test_Engine( QObject * parent ) :
    QObject( parent ) {}

Test_Engine::~Test_Engine() {}

void    Test_Engine::open() {
    qtreports::Engine engine;
    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );
}

void    Test_Engine::close()
{
    QString input = QFINDTESTDATA( "default.qreport" );

    qtreports::Engine engine;
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QCOMPARE( engine.isOpened(), true );
    engine.close();
    QCOMPARE( engine.isOpened(), false );
}

void    Test_Engine::setParameters()
{
    QString reportPath = QFINDTESTDATA( "full.qrxml" );
    qDebug() << endl << "Used report: " << reportPath;

    qtreports::Engine engine;
    QVERIFY2( engine.open( reportPath ), engine.getLastError().toStdString().c_str() );

    QMap < QString, QVariant > map;
    map[ "title" ] = "Best Title in World";
    qDebug() << endl << "Used map: " << map;
    QVERIFY2( engine.setParameters( map ), engine.getLastError().toStdString().c_str() );
}

void    Test_Engine::setConnection() {
    qtreports::Engine engine;
    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "testDB" );

    QVERIFY2( db.open(), "Can't open test database 'testDB'" );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );
    db.close();

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
    db.close();
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

    QVERIFY2( engine.createPDF( "test.pdf" ), engine.getLastError().toStdString().c_str() );
    //need delete. need test size.
    db.close();
}

void Test_Engine::createHTML()
{
    qtreports::Engine engine;
    QString input = QFINDTESTDATA( "html.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "testDB" );

    QVERIFY2( db.open(), "Can't open test database 'testDB'" );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );

    QVERIFY2( engine.createHTML("test.html"), engine.getLastError().toStdString().c_str() );

    db.close();
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

