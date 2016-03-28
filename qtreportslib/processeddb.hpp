#pragma once
#ifndef PROCESSEDDB_HPP
#define PROCESSEDDB_HPP
#include <QString>
#include <QVariant>
#include <QMap>

namespace qtreports {
    namespace detail {

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
            @param[in] columnName Название столбца
            @param[in] row Номер строки
            @param[out] result Значение поля
            */
            bool        getField( const QString & columnName, int row, QVariant &result );

            /*! @~russian
            Получает значение поля из выполненного запроса.
            @param[in] column Номер столбца
            @param[in] row Номер строки
            @param[out] result Значение поля
            */
            bool        getField( int column, int row, QVariant & result );

            /*! @~russian
            Добавляет параметр в список параметров.
            @param[in] name Имя параметра
            @param[in] value Значение параметра
            */
            void        addParam(const QString & name, const QVariant & value );

            /*! @~russian
            Добавляет данные в соответствующий столбец.
            @param[in] columnName Имя поля
            @param[in] data Значение поля
            */
            void        addFieldData( const QString & columnName, const QVariant & data);

            /*! @~russian
            Добавляет данные в соответствующий столбец.
            @param[in] columnName Имя поля.
            @param[in] data Множество значений поля.
            */
            void        addFieldData(const QString &columnName, const QVector <QVariant> & data);

            /*! @~russian
            Добавляет данные в соответствующий столбец.
            @param[in] columnName Номер поля.
            @param[in] data Значение поля.
            */
            void        addFieldData( int column, const QVariant & data );

            /*! @~russian
            Добавляет столбец.
            @param[in] name Имя столбца.
            */
            void        addColumn( const QString & name);

            /*! @~russian
             Получает столбец целиком.
             @param[in] name Имя столбца.
             @param[out] result Вектор-столбец.
             */
            bool        getColumn(const QString & name, QVector <QVariant> & result);

            /*! @~russian
             Получает столбец целиком.
             @param[in] col Номер столбца.
             @param[out] result Вектор-столбец.
             */
            bool        getColumn(int col, QVector <QVariant> & result);

            /*! @~russian
             Получает индекс столбца по имени. (Возврат -1, если столбца нет).
             @param[in] name Имя столбца.
             */
            int         getFieldIndex(const QString & name);

            /*! @~russian
            Получает строку ошибки.
            */
            const QString   getError() const;

        private:
            QMap <QString, QVector <QVariant> >             m_columnsSet;
            QMap <QString, QVariant>                        m_parametersMap;
            QString                                         m_errorString;
        };
    }
}

#endif // PROCESSEDDB_HPP
