#pragma once
#ifndef TEST_ENGINE_HPP
#define TEST_ENGINE_HPP
#include <QObject>
#include <QRegularExpression>

#include "parser_tester.hpp"
#include "engine_tester.h"

class Test_Engine : public QObject {
	Q_OBJECT

public:
    explicit Test_Engine(QObject * parent = Q_NULLPTR);
	~Test_Engine();

private slots:
    void    compile();

    void tags_parse();

    void connection();
	
};

#endif // TEST_ENGINE_HPP
