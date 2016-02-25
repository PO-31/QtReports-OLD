#ifndef PROCESSEDDB_H
#define PROCESSEDDB_H

#include <QVariant>

/* Обработанные запросы к БД и параметры. */

class ProcessedDB
{
public:
    ProcessedDB();

    QVariant getParam(QString p_name) const;

    QVariant getField(QString query_name, QString column_name, int row) const;

    QVariant getField(QString query_name, int column, int row) const;

};

#endif // PROCESSEDDB_H
