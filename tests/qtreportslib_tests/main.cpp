#include <QApplication>
#include <QTest>
#include "test_engine.hpp"

int main( int argc, char *argv[] ) {
    QApplication a( argc, argv );
    int result = 0;
    result |= QTest::qExec( new Test_Engine, argc, argv );

    return result;
    //return a.exec();
}
