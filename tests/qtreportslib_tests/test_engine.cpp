#include <QTest>
#include "../../qtreportslib/engine.hpp"
#include "test_engine.hpp"

Test_Engine::Test_Engine( QObject * parent ) : 
    QObject( parent ) {}

Test_Engine::~Test_Engine() {}

void    Test_Engine::compile() {
    qtreports::Engine engine;
    QVERIFY2( engine.compile( "" ), engine.getLastError().toStdString().c_str() );
}