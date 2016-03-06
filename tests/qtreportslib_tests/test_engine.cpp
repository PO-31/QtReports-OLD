#include <QTest>
#include <engine.hpp>
#include "test_engine.hpp"

Test_Engine::Test_Engine( QObject * parent ) : 
    QObject( parent ) {}

Test_Engine::~Test_Engine() {}

void    Test_Engine::compile() {
    qtreports::Engine engine;
    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );
}