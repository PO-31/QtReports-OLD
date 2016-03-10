#pragma once
#ifndef CONVERTERTOQWIDGET_HPP
#define CONVERTERTOQWIDGET_HPP
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include "tags/report.hpp"

namespace qtreports {
    namespace detail {
        typedef QSharedPointer< QWidget > QWidgetPtr;

        class ConverterToQWidget {

        public:
            ConverterToQWidget( const ReportPtr & report );
            ~ConverterToQWidget();

            bool                convert();

            const QString       getLastError() const;
            const QWidgetPtr    getQWidget() const;

        private:
            ReportPtr   m_report;
            QString     m_lastError;
            QWidgetPtr  m_qwidget;

            bool        createQWidget();
            bool        createSection( QVBoxLayout * parent, const SectionPtr & section );
            bool        createBands( QWidget * parent, const SectionPtr & section );

        };

    }
}
#endif // CONVERTERTOQWIDGET_HPP
