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
            if(m_report.isNull())
            {
                m_lastError = "Report is empty";
                return false;
            }

            int m_pageHeight = 800;
            int m_pageWidth = 600;
            int m_freePageSpace = m_pageHeight;

            m_html += QString("<!DOCTYPE html>\n"
                      "<html>\n"
                      " <head>\n"
                      "  <meta http-equiv='Content-Type' content='text/html; charset=utf-8'>\n"
                      "  <title>Report</title>\n"
                      "  <style>\n"

                      "   div, .detail, .title, .band {\n"
                      "   border: 1px solid black;\n"
                      "   position: relative;\n"
                      "   width: 100%;\n"
                      "   overflow: hidden;\n"
                      "   }\n"

                      "   .page {\n"
                      "   width: %1px;\n"
                      "   height: %2px;\n"
                      "   background-color: #C1CDC1;\n"
                      "   }\n"

                      "   .statictext, .textfield {\n"
                      "   position: absolute;\n"
                      "   background-color: transparent;\n"
                      "   }\n"

                      "   .statictext {\n"
                      "   font-family: %3;\n"
                      "   font-size: %4pt;\n"
                      "   color: %5;\n"
                      "   font-style: %6;\n"
                      "   font-weight: %7;\n"
                      "   background-color: Snow;\n"
                      "   }\n"

                      "   .textfield {\n"
                      "   font-family: %8;\n"
                      "   font-size: %9pt;\n"
                      "   color: %10;\n"
                      "   font-style: %11;\n"
                      "   font-weight: %12;\n"
                      "   background-color: GhostWhite;\n"
                      "   }\n"

                      "  </style>\n"
                      " </head>\n"
                      " <body>\n")
                    .arg(m_pageWidth).arg(m_pageHeight)
                    .arg("Verdana").arg("12").arg("black").arg("normal").arg("bold")
                    .arg("Verdana").arg("12").arg("black").arg("italic").arg("normal");

            m_html += "  <div class='page'>\n";
            m_html += "   <div class='title' style='background-color: #FFE4C4'>\n";

            auto title = m_report->getTitle();

            if(title.isNull())
            {
                m_lastError = "Report->Title is empty";
                return false;
            }

            int m_titleHeight = 0;

            for(auto && band : title->getBands())
            {
                QString m_elementStr = "";

                for(auto && textField : band->getTextFields())
                {
                   QString m_oldStr = textField->getText();
                   QString m_fieldStr = "";
                   QString m_newStr = "";

                   while (m_oldStr.contains("$F{"))
                   {
                       m_newStr += m_oldStr.section("$F{", 0, 0);
                       m_oldStr = m_oldStr.section("$F{", 1, -1);
                       m_fieldStr = m_oldStr.section("}", 0, 0);
                       m_oldStr = m_oldStr.section("}", 1, -1);

                       if (m_report->getField(m_fieldStr).data()->getRowCount() > 0)
                       {
                           m_newStr += m_report->getField(m_fieldStr).data()->getData(0);
                       }
                   }

                   m_oldStr = m_newStr + m_oldStr;

                   if (m_oldStr != "")
                   {
                       m_elementStr += QString("     <div class='textfield' "
                               "style='left: %1px; top: %2px; "
                               "width: %3px; height: %4px'>%5</div>\n")
                               .arg(textField->getX())
                               .arg(textField->getY())
                               .arg(textField->getWidth())
                               .arg(textField->getHeight())
                               .arg(m_oldStr);
                   }
                }

                for(auto && staticText : band->getStaticTexts())
                {
                    m_elementStr += QString("     <div class='statictext' "
                            "style='left: %1px; top: %2px; "
                            "width: %3px; height: %4px'>%5</div>\n")
                            .arg(staticText->getX())
                            .arg(staticText->getY())
                            .arg(staticText->getWidth())
                            .arg(staticText->getHeight())
                            .arg(staticText->getText());
                }

                m_titleHeight += band->getSize().height();

                m_html += QString("    <div class='band' "
                             "style='height: %1px'>\n%2    </div>\n")
                             .arg(band->getSize().height())
                             .arg(m_elementStr);
            }

            m_html += "   </div>\n";

            m_freePageSpace -= m_titleHeight;


            auto detail = m_report->getDetail();
            if(detail.isNull())
            {
                m_lastError = "Report->Detail is empty";
                return false;
            }

            int m_pageCount = 0;
            int m_detailCount = 0;

            while (true)
            {
                bool m_isDetailEmpty = true;
                int m_detailHeight = 0;
                QString m_bandStr = "";

                for(auto && band : detail->getBands())
                {
                    bool m_isBandEmpty = true;
                    QString m_elementStr = "";

                    for(auto && textField : band->getTextFields())
                    {
                       QString m_oldStr = textField->getText();
                       QString m_fieldStr = "";
                       QString m_newStr = "";

                       while (m_oldStr.contains("$F{"))
                       {
                           m_newStr += m_oldStr.section("$F{", 0, 0);
                           m_oldStr = m_oldStr.section("$F{", 1, -1);
                           m_fieldStr = m_oldStr.section("}", 0, 0);
                           m_oldStr = m_oldStr.section("}", 1, -1);

                           if (m_detailCount < m_report->getField(m_fieldStr).data()->getRowCount())
                           {
                               m_newStr += m_report->getField(m_fieldStr).data()->getData(m_detailCount);
                               m_isBandEmpty = false;
                           }
                       }

                       m_oldStr = m_newStr + m_oldStr;

                       /*while (m_oldStr.contains("$P{"))
                       {

                       }
                       while (m_oldStr.contains("$V{"))
                       {

                       }*/

                       if (m_oldStr != "")
                       {
                           m_elementStr += QString("     <div class='textfield' "
                                   "style='left: %1px; top: %2px; "
                                   "width: %3px; height: %4px'>%5</div>\n")
                                   .arg(textField->getX())
                                   .arg(textField->getY())
                                   .arg(textField->getWidth())
                                   .arg(textField->getHeight())
                                   .arg(m_oldStr);
                       }
                    }

                    if (!m_isBandEmpty)
                    {
                        for(auto && staticText : band->getStaticTexts())
                        {
                            m_elementStr += QString("     <div class='statictext' "
                                    "style='left: %1px; top: %2px; "
                                    "width: %3px; height: %4px'>%5</div>\n")
                                    .arg(staticText->getX())
                                    .arg(staticText->getY())
                                    .arg(staticText->getWidth())
                                    .arg(staticText->getHeight())
                                    .arg(staticText->getText());
                        }

                        m_isDetailEmpty = false;
                        m_detailHeight += band->getSize().height();

                        m_bandStr += QString("    <div class='band' "
                                     "style='height: %1px'>\n%2    </div>\n")
                                     .arg(band->getSize().height())
                                     .arg(m_elementStr);
                    }
                }

                if (m_isDetailEmpty)
                {
                    ++m_pageCount;
                    //Колонтитул
                    m_html += "  </div>\n";
                    break;
                }
                else
                {
                    if (m_detailHeight > m_freePageSpace)
                    {
                        ++m_pageCount;
                        //Колонтитул
                        m_html += QString("  </div>\n"
                                  "  <div class='page'>\n"
                                  "   <div class='detail' style='background-color: #FFF8DC'>\n%1   </div>\n")
                                  .arg(m_bandStr);

                        m_freePageSpace = m_pageHeight - m_detailHeight;
                    }
                    else
                    {
                        m_html += QString("   <div class='detail' style='background-color: #EEEEE0'>\n%1   </div>\n")
                                  .arg(m_bandStr);
                        m_freePageSpace -= m_detailHeight;
                    }
                }

                ++m_detailCount;
            }

            m_html += " </body>\n</html>\n";

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
