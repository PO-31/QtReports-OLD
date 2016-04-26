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
            enum class WidgetType {
                Report, ///< Отчет
                Layout ///< Макет
            };

            bool                convert( WidgetType type = WidgetType::Report );

            bool                            isReport() const;
            bool                            isLayout() const;
            WidgetType                      getType() const;
            const QWidgetPtr                getQWidget() const;
            const QWidgetPtr                getPage( int i ) const;
            const QVector< QWidgetPtr >     getPages() const;
            const QString                   getLastError() const;

        private:
            ReportPtr               m_report;
            QString                 m_lastError;
            QWidgetPtr              m_qwidget;
            WidgetType              m_type;
            QVector< QWidgetPtr >   m_pages;
            int                     m_currentHeight;

            void        addVerticalBorder( QBoxLayout * parent, const QMargins & margins, int height );
            void        addEmptySection( QBoxLayout * parent, const QMargins & margins );
            QFrame *    addSectionLayout( QBoxLayout * parent, const QMargins & margins, int height );
            
            void        addPage();

            bool        createQWidget( const ReportPtr & report );
            bool        createSection( QWidget * parent, const SectionPtr & section, int i );
            bool        createBands( QWidget * parent, const SectionPtr & section );

        };

    }
}
#endif // CONVERTERTOQWIDGET_HPP
