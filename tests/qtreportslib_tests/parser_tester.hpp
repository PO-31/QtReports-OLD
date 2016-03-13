#ifndef PARSER_TESTER_HPP
#define PARSER_TESTER_HPP
#include <QObject>
#include <QRegularExpression>

class Parser_Tester : public QObject
{
public:
    Parser_Tester(QObject * parent = Q_NULLPTR);

    void ReportTreeParseTest();

    void ReportTagParseTest();
    void TextTest();
};

#endif // PARSER_TESTER_H
