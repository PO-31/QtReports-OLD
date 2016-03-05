#pragma once
#ifndef CONVERTER_HPP
#define CONVERTER_HPP
#include <QString>
#include <QWidget>
#include <QSharedPointer>
#include "tags/report.hpp"

namespace qtreports {
    namespace detail {
        typedef QSharedPointer< QWidget > QWidgetPtr;

        class Converter {

        public:
            Converter( const ReportPtr & report );
            ~Converter();

            QString     toHTML();
            QWidgetPtr  toQWidget();

            bool        toHTML( const QString & path );
            bool        toPDF( const QString & path );

            const QString   getLastError() const;

        private:
            ReportPtr   m_report;
            QString     m_lastError;

        };

    }
}
#endif // CONVERTER_HPP
