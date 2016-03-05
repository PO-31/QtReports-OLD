#pragma once
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP
#include <QString>
#include <QXmlStreamReader>
#include "tags/report.hpp"
#include "tags/style.hpp"
#include "tags/field.hpp"
#include "tags/detail.hpp"
#include "tags/band.hpp"
#include "tags/statictext.hpp"
#include "tags/textfield.hpp"

namespace qtreports {

    //All support classes in detail
    namespace detail {

        class Parser {

        public:
            Parser();
            ~Parser();

            bool	            parse( const QString & path );

            const ReportPtr	    getReport() const;
            const QString       getLastError() const;

        private:
            ReportPtr	m_report;
            QString		m_lastError;

            bool    getValue( QXmlStreamReader & reader, QString & data );
            bool    getAttribute( QXmlStreamReader & reader, const QString & name, QString & data );

            bool	parseReport( const QString & text );
            bool    parseStyle( QXmlStreamReader & reader, const ReportPtr & report );
            bool	parseField( QXmlStreamReader & reader, const ReportPtr & report );
            bool	parseDetail( QXmlStreamReader & reader, const ReportPtr & report );
            bool    parseBand( QXmlStreamReader & reader, const DetailPtr & detail );
            bool    parseStaticText( QXmlStreamReader & reader, const BandPtr & band );
            bool    parseTextField( QXmlStreamReader & reader, const BandPtr & band );
            bool    parseReportElement( QXmlStreamReader & reader, const WidgetPtr & text );
            bool    parseText( QXmlStreamReader & reader, const StaticTextPtr & text );
            bool    parseTextFieldExpression( QXmlStreamReader & reader, const TextFieldPtr & text );

        };

    }
}
#endif // TRANSLATOR_HPP
