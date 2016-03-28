#pragma once
#ifndef CONVERTERTOQWIDGET_HPP
#define CONVERTERTOQWIDGET_HPP
#include <QString>
#include <QWidget>
#include <QFrame>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "tags/report.hpp"

namespace qtreports {
    typedef QSharedPointer< QWidget > QWidgetPtr;

    namespace detail {

        class ConverterToQWidget {

        public:
            ConverterToQWidget( const ReportPtr & report );
            ~ConverterToQWidget();

            /*! @~russian
            Тип создаваемого виджета.
            */
            enum WidgetType {
                Report = 0, ///< Отчет
                Layout ///< Макет
            };

            bool                convert( WidgetType type = WidgetType::Report );
            bool                convert( const ReportPtr & report, WidgetType type = WidgetType::Report );

            const QString       getLastError() const;
            bool                isReport() const;
            bool                isLayout() const;
            WidgetType          getType() const;
            const QWidgetPtr    getQWidget() const;

        private:
            ReportPtr   m_report;
            QString     m_lastError;
            QWidgetPtr  m_qwidget;
            WidgetType  m_type;

            void        addVerticalBorder( QBoxLayout * parent, int height, int left, int right );
            void        addEmptySection( QBoxLayout * parent, int left, int right );
            QFrame *    addSectionLayout( QBoxLayout * parent, int height, int left, int right );

            bool        createQWidget( const ReportPtr & report );
            bool        createSection( QWidget * parent, const SectionPtr & section );
            bool        createBands( QWidget * parent, const SectionPtr & section );

        };

    }
}
#endif // CONVERTERTOQWIDGET_HPP
