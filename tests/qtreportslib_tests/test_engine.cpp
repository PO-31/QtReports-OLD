#include <QTest>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QRegularExpression>
#include <QDebug>
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

}

void    Test_Engine::setQuery()
{

}

void    Test_Engine::addScript()
{

}

void    Test_Engine::setDataModel()
{

}

void    Test_Engine::createPDF()
{
    qtreports::Engine engine;

    QCOMPARE( engine.createPDF( "test.pdf" ), false );
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

    engine.createHTML("test.html");

    db.close();
}

void    Test_Engine::createWidget()
{
    qtreports::Engine engine;

    QCOMPARE( engine.createWidget(), qtreports::QWidgetPtr() );
}

void    Test_Engine::createLayout()
{
    qtreports::Engine engine;

    QCOMPARE( engine.createLayout(), qtreports::QWidgetPtr() );
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
}

void    Test_Engine::getReport()
{
    qtreports::Engine engine;

    QCOMPARE( engine.getReport(), qtreports::detail::ReportPtr() );
}

void    Test_Engine::getLastError()
{
    qtreports::Engine engine;

    QCOMPARE( engine.getLastError(), QString() );
}

