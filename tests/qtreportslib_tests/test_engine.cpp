#include <QTest>
#include <engine.hpp>
#include "test_engine.hpp"

Test_Engine::Test_Engine( QObject * parent ) : 
    QObject( parent ) {}

Test_Engine::~Test_Engine() {}

void    Test_Engine::compile() {
    Parser_Tester pt;

    pt.ReportTreeParseTest();
}

void Test_Engine::tags_parse()
{
    Parser_Tester pt;

    pt.ReportTagParseTest();

    pt.TextTest();
}

void Test_Engine::connection()
{
    Engine_Tester eng_t;

    eng_t.TestConnectionSetting();
}
