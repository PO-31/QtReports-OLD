#pragma once
#ifndef CONVERTERTOPDF_HPP
#define CONVERTERTOPDF_HPP
#include <QString>
#include "tags/report.hpp"

namespace qtreports {
    namespace detail {

        class ConverterToPDF {

        public:
            ConverterToPDF( const ReportPtr & report );
            ~ConverterToPDF();

            bool            convert( const QString & path );

            const QString   getLastError() const;

        private:
            ReportPtr   m_report;
            QString     m_lastError;

            bool        createPDF( const QString & path );

        };

    }
}
#endif // CONVERTERTOPDF_HPP
