#pragma once
#ifndef PROCESSEDDB_HPP
#define PROCESSEDDB_HPP
#include <QString>
#include <QVariant>
#include <QMap>

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, используемый для хранения выполненных запросов и параметров.
        @note Все функции данного класса, возвращающие bool,
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
            Добавляет параметр в список параметров.
            @param[in] name Имя параметра
            @param[in] value Значение параметра
            */
            void            setParameter( const QString & name, const QVariant & value );

            /*! @~russian
            Устанавливает карту параметров.
            @param[in] map Карта параметров.
            */
            void            setParameters( const QMap< QString, QVariant > & map );

            /*! @~russian
            Возвращает параметр из результата работы скрипта.
            @param[in] name Имя параметра
            */
            const QVariant  getParameter( const QString & name ) const;

            /*! @~russian
            Возвращает карту параметров.
            */
            const QMap< QString, QVariant >     getParameters() const;

            /*! @~russian
            Добавляет данные в соответствующий столбец.
            @param[in] columnName Имя поля
            @param[in] data Значение поля
            */
            void            appendColumnData( const QString & columnName, const QVariant & data );

            /*! @~russian
            Добавляет данные в соответствующий столбец.
            @param[in] column Номер поля.
            @param[in] data Значение поля.
            */
            void            appendColumnData( int column, const QVariant & data );

            /*! @~russian
            Добавляет данные в соответствующий столбец.
            @param[in] columnName Имя поля.
            @param[in] data Множество значений поля.
            */
            void            appendColumnData( const QString & columnName, const QVector< QVariant > & data );

            /*! @~russian
            Добавляет данные в соответствующий столбец.
            @param[in] column Номер поля.
            @param[in] data Множество значений поля.
            */
            void            appendColumnData( int column, const QVector< QVariant > & data );

            /*! @~russian
            Добавляет столбец.
            @param[in] name Имя столбца.
            */
            void            addEmptyColumn( const QString & name );

            /*! @~russian
            Добавляет столбец.
            @param[in] column Номер столбца
            */
            void            addEmptyColumn( int column );

            /*! @~russian
            Возвращает столбец данных.
            @param[in] name Имя столбца.
            */
            const QVector< QVariant >   getColumn( const QString & name ) const;

            /*! @~russian
            Получает столбец целиком.
            @param[in] col Номер столбца.
            */
            const QVector< QVariant >   getColumn( int col ) const;

            /*! @~russian
            Возвращает имя столбца.
            @param[in] column Номер столбца
            */
            QString     getColumnName( int column ) const;

            /*! @~russian
            Возвращает индекс столбца по имени. Если столбец не существует,
            возвращает -1.
            @param[in] name Имя столбца.
            */
            int         getColumnIndex( const QString & name ) const;

            /*! @~russian
            Проверяет, существует ли столбец с определенным именем.
            @param[in] name Имя столбца.
            */
            bool        columnIsExists( const QString & name ) const;

            /*! @~russian
            Проверяет, существует ли столбец с определенным именем.
            @param[in] column Номер столбца.
            */
            bool        columnIsExists( int column ) const;

            /*! @~russian
            Возвращает значение поля.
            @param[in] columnName Название столбца
            @param[in] row Номер строки
            */
            const QVariant  getFieldData( const QString & columnName, int row ) const;

            /*! @~russian
            Возвращает значение поля.
            @param[in] column Номер столбца
            @param[in] row Номер строки
            */
            const QVariant  getFieldData( int column, int row ) const;

            /*! @~russian
            Получает количество записей в столбце.
            @param[in] columnName Имя столбца.
            */
            int         getRowCount( const QString & columnName ) const;

            /*! @~russian
            Получает количество записей в столбце.
            @param[in] column Номер столбца.
            */
            int         getRowCount( int column ) const;

            /*! @~russian
            Получает максимальное количество записей среди набора столбцов.
            */
            int         getMaxRowCount() const;

            /*! @~russian
            Получает строку ошибки.
            */
            const QString   getError() const;

        private:
            QMap< QString, QVector< QVariant > >        m_columnsSet;
            QMap< QString, QVariant >                   m_parametersMap;
            QString                                     m_errorString;
        };
    }
}

#endif // PROCESSEDDB_HPP
