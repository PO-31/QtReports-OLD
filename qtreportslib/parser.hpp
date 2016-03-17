#pragma once
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP
#include <functional>
#include <QString>
#include <QXmlStreamReader>
#include <QMap>
#include <QTextStream>
#include "tags/report.hpp"
#include "tags/style.hpp"
#include "tags/field.hpp"
#include "tags/detail.hpp"
#include "tags/band.hpp"
#include "tags/statictext.hpp"
#include "tags/textfield.hpp"

namespace qtreports {
    namespace detail {

        /*! @~russian
        @brief Класс, используемый для парсинга исходного отчета.
        @warning Все функции данного класса, возвращающие bool,
        возвращают true в случае успеха либо false, если во время 
        выполнения произошли ошибки. При этом с помощью метода getLastError()
        можно получить описание последней произошедшей ошибки.

        Класс, который отвечает за парсинг отчета и 
        создание из него внутренней структуры данных Report.
        */
        class Parser {

        public:
            Parser();
            ~Parser();

            /*! @~russian
            Парсит отчет и создает из него внутреннюю структуру данных Report.
            @param[in] path Путь к отчету формата .qreport
            */
            bool                parse( const QString & path );

            /*! @~russian
            Возвращает указатель на внутреннюю структуру отчета.
            Указатель может быть пустым, перед использованием необходимо
            проверить с помощью
            @code
            if ( !report.isNull() ) {
            @endcode
            */
            const ReportPtr     getReport() const;

            /*! @~russian
            Возвращает описание последней произошедшей ошибки.
            */
            const QString      getLastError() const;

            /*! @~russian
            Возвращает лог процесса парсинга. Используется для отладки при добавлении новый тэгов.
            */
            const QString      getLog() const;

            using ParseFuncPtr = bool( QXmlStreamReader &, const ObjectPtr & );
            using ParseMethodPtr = bool( Parser::* )( QXmlStreamReader &, const ObjectPtr & );
            using ParseFunc = std::function< ParseFuncPtr >;

        private:
            ReportPtr	                m_report;
            QString		                m_lastError;
            QTextStream                 m_log;
            QMap< QString, ParseFunc >  m_functions;

            /*! @~russian
            Опции при получении аттрибута с помощью вызова getAttribute().
            */
            enum AttributeOption {
                Required, ///< При отсутствии аттрибута будет выдана ошибка.
                Optional ///< При отсутствии аттрибута будет использовано пустое значение.
            };

            bool    getValue( QXmlStreamReader & reader, QString & data );
            bool    getAttribute( QXmlStreamReader & reader, const QString & name, QString & data, AttributeOption option );
            bool    getRequiredAttribute( QXmlStreamReader & reader, const QString & name, QString & data );
            bool    getOptionalAttribute( QXmlStreamReader & reader, const QString & name, QString & data );
            bool    goToElementEnd( QXmlStreamReader & reader );
            bool    parseChilds( QXmlStreamReader & reader, const ObjectPtr & object );

            bool    parseDocument( const QString & text );
            bool    parseReport( QXmlStreamReader & reader, const ReportPtr & report );
            bool    parseStyle( QXmlStreamReader & reader, const ReportPtr & report );
            bool    parseQueryString( QXmlStreamReader & reader, const ReportPtr & report );
            bool    parseField( QXmlStreamReader & reader, const ReportPtr & report );
            bool    parseTitle( QXmlStreamReader & reader, const ReportPtr & report );
            bool    parseDetail( QXmlStreamReader & reader, const ReportPtr & report );
            bool    parseBand( QXmlStreamReader & reader, const SectionPtr & section );
            bool    parseStaticText( QXmlStreamReader & reader, const BandPtr & band );
            bool    parseTextField( QXmlStreamReader & reader, const BandPtr & band );
            bool    parseReportElement( QXmlStreamReader & reader, const WidgetPtr & widget );
            bool	parseTextElement( QXmlStreamReader & reader, const WidgetPtr & widget );
            bool	parseFont( QXmlStreamReader & reader, const WidgetPtr & widget );
            bool    parseText( QXmlStreamReader & reader, const StaticTextPtr & text );
            bool    parseTextFieldExpression( QXmlStreamReader & reader, const TextFieldPtr & text );

        };

    }
}
#endif // TRANSLATOR_HPP
