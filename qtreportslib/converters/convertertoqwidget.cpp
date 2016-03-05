#include <QTextBrowser>
#include <QVBoxLayout>
#include "convertertohtml.hpp"
#include "convertertoqwidget.hpp"

namespace qtreports {
    namespace detail {

        ConverterToQWidget::ConverterToQWidget( const ReportPtr & report ) :
            m_report( report ) {}

        ConverterToQWidget::~ConverterToQWidget() {}

        bool    ConverterToQWidget::convert() {
            return createQWidget();
        }

        bool    ConverterToQWidget::createQWidget() {
            if( m_report.isNull() ) {
                m_lastError = "Report is empty";
                return false;
            }

            ConverterToHTML converter( m_report );
            bool result = converter.convert();
            if( !result ) {
                m_lastError = "Cannot convert to HTML: " + converter.getLastError();
                return false;
            }

            QString html = converter.getHTML();

            auto widget = new QWidget();
            widget->resize( 600, 400 );

            auto browser = new QTextBrowser();
            browser->setText( html );

            auto layout = new QVBoxLayout( widget );
            layout->setMargin( 0 );
            layout->addWidget( browser );

            m_qwidget = QWidgetPtr( widget );

            return true;
        }

        const QString       ConverterToQWidget::getLastError() const {
            return m_lastError;
        }

        const QWidgetPtr    ConverterToQWidget::getQWidget() const {
            return m_qwidget;
        }

    }
}
