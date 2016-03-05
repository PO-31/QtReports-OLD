#include <QLabel>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QFile>
#include <QPdfWriter>
#include <QTextStream>
#include "converter.hpp"

namespace qtreports {
    namespace detail {

        Converter::Converter( const ReportPtr & report ) :
            m_report( report ) {}

        Converter::~Converter() {}

        QString     Converter::toHTML() {
            QString html;
            if( m_report.isNull() ) {
                return html;
            }

            for( auto && band : m_report->getDetail()->getBands() ) {
                html += QString( 
                    "<table border='1' width='100%' height='%1' "
                    "style='border-style: solid; border-color: black;'>"
                    "<tbody><tr><td>" )
                    .arg( band->getSize().height() );
                for( auto && staticText : band->getStaticTexts() ) {
                    html += QString(
                        "<div style='margin-left: %1; margin-top: %2;' "
                        "width='%3' height='%4' >%5</div>" )
                        .arg( staticText->getX() )
                        .arg( staticText->getY() )
                        .arg( staticText->getWidth() )
                        .arg( staticText->getHeight() )
                        .arg( staticText->getText() );
                }
                for( auto && textField : band->getTextFields() ) {
                    html += QString(
                        "<div style='margin-left: %1; margin-top: %2;' "
                        "width='%3' height='%4' >%5</div>" )
                        .arg( textField->getX() )
                        .arg( textField->getY() )
                        .arg( textField->getWidth() )
                        .arg( textField->getHeight() )
                        .arg( textField->getText() );
                }
                html += "</td></tr></tbody></table>";
            }
            return html;
        }

        bool    Converter::toHTML( const QString & path ) {
            QString html = toHTML();
            if( html.isEmpty() ) {
                m_lastError = "Cannot convert to HTML. Please, check report for errors";
                return false;
            }

            QFile file( path );
            file.open(
                QIODevice::OpenModeFlag::WriteOnly |
                QIODevice::OpenModeFlag::Text |
                QIODevice::OpenModeFlag::Truncate
            );

            if( !file.isOpen() ) {
                m_lastError = "The file can not be opened";
                return false;
            }

            QTextStream stream( &file );
            stream << html;

            return true;
        }

        QWidgetPtr Converter::toQWidget() {
            QString html = toHTML();

            auto widget = new QWidget();
            widget->resize( 600, 400 );

            auto browser = new QTextBrowser();
            browser->setText( html );

            auto layout = new QVBoxLayout( widget );
            layout->setMargin( 0 );
            layout->addWidget( browser );
            return QWidgetPtr( widget );
        }

        bool    Converter::toPDF( const QString & path ) {
            QPdfWriter writer( path );
            auto widget = toQWidget();
            //Very small, need resize to page size.
            widget->render( &writer );

            return true;
        }

        const QString   Converter::getLastError() const {
            return m_lastError;
        }

    }
}
