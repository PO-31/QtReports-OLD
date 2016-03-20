#pragma once
#ifndef PROCESSEDDB_HPP
#define PROCESSEDDB_HPP
#include <QString>
#include <QVariant>
#include <QMap>
#include <QSharedPointer>
#include <QSqlQueryModel>
#include <QSqlField>

namespace qtreports {
    namespace detail {
        typedef QSharedPointer< QSqlQueryModel > QSqlQueryModelPtr;

        /*! @~russian
        @brief Класс, используемый для хранения выполненных запросов и параметров.
        @warning Все функции данного класса, возвращающие bool,
        возвращают true в случае успеха либо false, если во время
        выполнения произошли ошибки. При этом с помощью метода getLastError()
        можно получить описание последней произошедшей ошибки.

        Класс который отвечает за структуру хранения результатов выполненных запросов и
        параметров БД.
        */
        class ProcessedDB {

        public:
            ProcessedDB();
            ~ProcessedDB();

            /*! @~russian
            Получает параметр из результата работы скрипта.
            @param[in] name Имя параметра
            @param[out] result Значение параметра
            */
            bool        getParam( const QString & name, QVariant & result );

            /*! @~russian
            Получает значение поля из выполненного запроса.
            @param[in] queryName Имя запроса
            @param[in] columnName Название столбца
            @param[in] row Номер строки
            @param[out] result Значение поля
            */
            bool        getField( const QString & queryName, const QString & columnName, int row, QVariant &result );

            /*! @~russian
            Получает значение поля из выполненного запроса.
            @param[in] queryName Имя запроса
            @param[in] column Номер столбца
            @param[in] row Номер строки
            @param[out] result Значение поля
            */
            bool        getField( const QString & queryName, int column, int row, QVariant & result );

            /*! @~russian
            Добавляет параметр в список параметров.
            @param[in] name Имя параметра
            @param[in] value Значение параметра
            */
            void        addParam( const QString & name, const QVariant & value );

            /*! @~russian
            Добавляет данные выполненного запроса в массив данных выполненных запросов.
            @param[in] name Название запроса
            @param[in] model Указатель на модель выполненного запроса.
            */
            void        addExecutedQuery( const QString & name, const QSqlQueryModelPtr & model );

            /*! @~russian
            Получает строку ошибки.
            */
            const QString   getError() const;

        private:
            QString                                             m_errorString;
            QMap< QString, QVector< QSqlRecord > >              m_queriesResultData;
        };
    }
}

#endif // PROCESSEDDB_HPP
