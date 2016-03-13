#ifndef ENGINE_TESTER_H
#define ENGINE_TESTER_H

#include <QObject>
#include <QRegularExpression>

#include <QSqlDatabase>

#include "engine.hpp"

class Engine_Tester : public QObject
{
public:
    Engine_Tester(QObject * parent = Q_NULLPTR);

    void TestConnectionSetting();

protected:

    qtreports::Engine engine;
};

#endif // ENGINE_TESTER_H
