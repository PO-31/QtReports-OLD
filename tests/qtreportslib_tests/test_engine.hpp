#pragma once
#ifndef TEST_ENGINE_HPP
#define TEST_ENGINE_HPP
#include <QObject>

class Test_Engine : public QObject {
	Q_OBJECT

public:
    explicit Test_Engine(QObject * parent = Q_NULLPTR);
	~Test_Engine();

private slots:
    void    compile();
	
};

#endif // TEST_ENGINE_HPP