//#include <QTextBrowser>
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

            auto layout = new QVBoxLayout( m_qwidget.data() );
            layout->setMargin( 0 );

            auto title = m_report->getTitle();
            if( !title.isNull() && !createSection( layout, title ) ) {
                return false;
            }

            if( !createSection( layout, detail ) ) {
                return false;;
            }

            auto emptyWidget = new QFrame();
            emptyWidget->setMinimumHeight( 0 );
            layout->addWidget( emptyWidget );

            return true;
        }

        bool    ConverterToQWidget::createSection( QVBoxLayout * parent, const SectionPtr & section ) {
            auto frame = new QFrame();
            frame->setMaximumHeight( section->getHeight() );
            frame->setMinimumHeight( section->getHeight() );
            parent->addWidget( frame );

            auto label = new QLabel( frame );
            label->setText( section->getTagName() );
            label->setAttribute( Qt::WA_TranslucentBackground );
            label->setStyleSheet( "font-size: 26px; color: rgba( 0, 0, 0, 50% )" );
            label->setAlignment( Qt::AlignCenter );
            label->resize( frame->size() );

            if( !createBands( frame, section ) ) {
                return false;;
            }

            return true;
        }

        bool    ConverterToQWidget::createBands( QWidget * parent, const SectionPtr & section ) {
            for( auto && band : section->getBands() ) {
                auto frame = new QFrame( parent );
                for( auto && staticText : band->getStaticTexts() ) {
                    auto label = new QLabel( frame );
                    label->setGeometry( staticText->getRect() );
                    label->setText( staticText->getText() );
                }
                for( auto && textField : band->getTextFields() ) {
                    auto label = new QLabel( frame );
                    label->setGeometry( textField->getRect() );
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
