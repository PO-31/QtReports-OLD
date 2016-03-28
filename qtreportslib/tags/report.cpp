#include "report.hpp"

namespace qtreports {
    namespace detail {

        Report::Report() :
            m_isVertical( true ),
            m_size( 600, 400 ),
            m_leftMargin( 30 ),
            m_topMargin( 30 ),
            m_rightMargin( 30 ),
            m_bottomMargin( 30 ),
            m_rowCount( 0 ) {
            Q_UNUSED( m_isVertical );
            Q_UNUSED( m_size );
        }

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

        void    Report::setTitle( const TitlePtr & title ) {
            m_title = title;
        }

        const TitlePtr     Report::getTitle() const {
            return m_title;
        }

        void    Report::setDetail( const DetailPtr & detail ) {
            m_detail = detail;
        }

        const DetailPtr     Report::getDetail() const {
            return m_detail;
        }

        void Report::setFieldData(const QString field_name, const QVector<QVariant> data)
        {
            m_fields[ field_name ]->setData(data);
        }

        int     Report::getRowCount() {
            return m_rowCount;
        }

        void Report::setRowCount( int count )
        {
            m_rowCount = count;
        }

        int     Report::getLeftMargin() {
            return m_leftMargin;
        }

        int     Report::getTopMargin() {
            return m_topMargin;
        }

        int     Report::getRightMargin() {
            return m_rightMargin;
        }

        int     Report::getBottomMargin() {
            return m_bottomMargin;
        }

        void    Report::setLeftMargin( int left ) {
            m_leftMargin = left;
        }

        void    Report::setTopMargin( int top ) {
            m_topMargin = top;
        }

        void    Report::setRightMargin( int right ) {
            m_rightMargin = right;
        }

        void    Report::setBottomMargin( int bottom ) {
            m_bottomMargin = bottom;
        }

        void    Report::setMargins( int left, int top, int right, int bottom ) {
            setLeftMargin( left );
            setTopMargin( top );
            setRightMargin( right );
            setBottomMargin( bottom );
        }

    }
}
