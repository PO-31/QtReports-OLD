#include <QFile>
#include <QTextStream>
#include "convertertohtml.hpp"

namespace qtreports {
    namespace detail {

        ConverterToHTML::ConverterToHTML( const ReportPtr & report ) :
            m_report( report ) {}

        ConverterToHTML::~ConverterToHTML() {}

        bool    ConverterToHTML::convert() {
            return createHTML();
        }

        bool    ConverterToHTML::convert( const QString & path ) {
            if( !convert() ) {
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
            stream << m_html;

            return true;
        }

        bool    ConverterToHTML::createHTML() {
            if( m_report.isNull() ) {
                m_lastError = "Report is empty";
                return false;
            }

            auto detail = m_report->getDetail();
            if( detail.isNull() ) {
                m_lastError = "Report->Detail is empty";
                return false;
            }

            for( auto && band : detail->getBands() ) {
                m_html += QString(
                    "<table border='1' width='100%' height='%1' "
                    "style='border-style: solid; border-color: black;'>"
                    "<tbody><tr><td>" )
                    .arg( band->getSize().height() );
                for( auto && staticText : band->getStaticTexts() ) {
                    m_html += QString(
                        "<div style='margin-left: %1; margin-top: %2;' "
                        "width='%3' height='%4' >%5</div>" )
                        .arg( staticText->getX() )
                        .arg( staticText->getY() )
                        .arg( staticText->getWidth() )
                        .arg( staticText->getHeight() )
                        .arg( staticText->getText() );
                }
                for( auto && textField : band->getTextFields() ) {
                    m_html += QString(
                        "<div style='margin-left: %1; margin-top: %2;' "
                        "width='%3' height='%4' >%5</div>" )
                        .arg( textField->getX() )
                        .arg( textField->getY() )
                        .arg( textField->getWidth() )
                        .arg( textField->getHeight() )
                        .arg( textField->getText() );
                }
                m_html += "</td></tr></tbody></table>";
            }
            return true;
        }

        const QString   ConverterToHTML::getLastError() const {
            return m_lastError;
        }

        const QString   ConverterToHTML::getHTML() const {
            return m_html;
        }

    }
}