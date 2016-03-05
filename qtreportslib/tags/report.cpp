#include "../painter.hpp"
#include "report.hpp"

namespace qtreports {
    namespace detail {

        Report::Report() :
            m_isVertical( true ),
            m_size( 600, 400 ) {}

        Report::~Report() {}
        /*
        bool    Report::setParameter( const QString & name, const QVariant & value ) {
            QString page_width( "page_width" ), page_height( "page_height" ),
                isVertical( "is_vertical" );

            if( !value.isValid() ) {
                m_lastError = "Invalid parameter value";
                return false;
            }

            if( page_width.compare( name, Qt::CaseInsensitive ) == 0 ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_size.setWidth( value.toInt() );
                return true;
            }

            if( page_height.compare( name, Qt::CaseInsensitive ) == 0 ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_size.setWidth( value.toInt() );

                return true;
            }

            if( isVertical.compare( name, Qt::CaseInsensitive ) == 0 ) {
                if( value.type() != QVariant::Bool ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_isVertical = value.toBool();
                return true;
            }

            return true;// Object::setParameter( name, value );
        }
        */

        void    Report::setDefaultStyle( const StylePtr & style ) {
            m_defaultStyle = style;
        }

        const StylePtr  Report::getDefaultStyle() const {
            return m_defaultStyle;
        }

        void    Report::setStyle( const QString & name, const StylePtr & style ) {
            m_styles[ name ] = style;
        }

        const StylePtr  Report::getStyle( const QString & name ) const {
            if( !m_styles.contains( name ) ) {
                return StylePtr();
            }

            return m_styles[ name ];
        }

        const QMap< QString, StylePtr >     Report::getStyles() const {
            return m_styles;
        }

        void    Report::setQuery( const QString & query ) {
            m_query = query;
        }

        const QString   Report::getQuery() const {
            return m_query;
        }

        void    Report::setField( const QString & name, const FieldPtr & field ) {
            m_fields[ name ] = field;
        }

        const FieldPtr  Report::getField( const QString & name ) const {
            if( !m_fields.contains( name ) ) {
                return  FieldPtr();
            }

            return m_fields[ name ];
        }

        const QMap< QString, FieldPtr >   Report::getFields() const {
            return m_fields;
        }

        void    Report::setDetail( const DetailPtr & detail ) {
            m_detail = detail;
        }

        const DetailPtr     Report::getDetail() const {
            return m_detail;
        }

    }
}