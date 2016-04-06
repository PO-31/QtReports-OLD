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

}

void    Test_Engine::setConnection() {
    qtreports::Engine engine;
    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "testDB" );

    QVERIFY2( db.open(), "Can't open test database 'testDB'" );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );

    /*
    QSqlQuery q;
    q.exec("select * from groups_t;");
    while (q.next()) {
    qDebug() << q.value(1).toString();
    }
    */

    db.close();
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

}

void Test_Engine::createHTML()
{
    qtreports::Engine engine;
    QString input = QFINDTESTDATA( "html.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( "testDB" );

    QVERIFY2( db.open(), "Can't open test database 'testDB'" );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );

    engine.createHTML("test.html");

    db.close();
}

void    Test_Engine::createWidget()
{

}

void    Test_Engine::createLayout()
{

}

void    Test_Engine::print()
{

}

void    Test_Engine::isOpened()
{

}

void    Test_Engine::getReport()
{

}

void    Test_Engine::getLastError()
{

}

