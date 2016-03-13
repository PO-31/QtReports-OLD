#include "engine_tester.h"

#include <QTest>
#include <QSqlQuery>

#include <QDebug>

Engine_Tester::Engine_Tester(QObject *parent): QObject(parent)
{

}

void Engine_Tester::TestConnectionSetting()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("testDB");

    bool ok = db.open();

    QVERIFY2( ok, "Can't open test database 'testDB'" );

    ok = engine.setConnection(db);

    QVERIFY2( ok, engine.getLastError().toLatin1().data());

    /*QSqlQuery q;

    q.exec("select * from groups_t;");

    while (q.next())
    {
        qDebug() << q.value(1).toString();
    }*/

    db.close();
}
