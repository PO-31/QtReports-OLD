#include <QCoreApplication>
#include <QTest>
#include "test_engine.hpp"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QTest::qExec( new Test_Engine, argc, argv );

    return a.exec();
}
