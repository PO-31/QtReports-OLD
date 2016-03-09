//#include <QTextBrowser>
//#include <QVBoxLayout>
//#include "convertertohtml.hpp"
#include <QFrame>
#include <QLabel>
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
            /*
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
            */

            m_qwidget = QWidgetPtr( new QWidget() );
            m_qwidget->setStyleSheet( "border: 1px solid black" );

            auto detail = m_report->getDetail();
            if( detail.isNull() ) {
                m_lastError = "Report->Detail is empty";
                return false;
            }

            for( auto && band : detail->getBands() ) {
                auto frame = new QFrame( m_qwidget.data() );
                frame->setGeometry( 0, 0, m_qwidget->width(), band->getSize().height() );
                for( auto && staticText : band->getStaticTexts() ) {
                    auto label = new QLabel( frame );
                    QRect rect( staticText->getPos(), staticText->getSize() );
                    label->setGeometry( rect );
                    label->setText( staticText->getText() );
                }
                for( auto && textField : band->getTextFields() ) {
                    auto label = new QLabel( frame );
                    QRect rect( textField->getPos(), textField->getSize() );
                    label->setGeometry( rect );
                    label->setText( textField->getText() );
                }
            }

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
