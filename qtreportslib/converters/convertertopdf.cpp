#include <QPdfWriter>
#include "convertertoqwidget.hpp"
#include "convertertopdf.hpp"

namespace qtreports {
    namespace detail {

        ConverterToPDF::ConverterToPDF( const ReportPtr & report ) :
            m_report( report ) {}

        ConverterToPDF::~ConverterToPDF() {}

        bool    ConverterToPDF::convert( const QString & path ) {
            return createPDF( path );
        }

        bool    ConverterToPDF::createPDF( const QString & path ) {
            if( m_report.isNull() ) {
                m_lastError = "Report is empty";
                return false;
            }

            ConverterToQWidget converter( m_report );
            bool result = converter.convert();
            if( !result ) {
                m_lastError = "Cannot convert to QWidget: " + converter.getLastError();
                return false;
            }

            auto widget = converter.getQWidget();

            QPdfWriter writer( path );
            //Very small, need resize to page size.
            widget->render( &writer );

            return true;
        }

        const QString   ConverterToPDF::getLastError() const {
            return m_lastError;
        }

    }
}
