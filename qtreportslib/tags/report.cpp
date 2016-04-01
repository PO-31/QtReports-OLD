#include "report.hpp"

namespace qtreports
{
    namespace detail
    {

        Report::Report() :
            m_isVertical( true ),
            m_size( 595, 842 ),
            m_margins( 30, 30, 30, 30 ),
            m_rowCount( 0 )
        {
            Q_UNUSED( m_isVertical );
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

        void    Report::setDefaultStyle( const StylePtr & style )
        {
            m_defaultStyle = style;
        }

        const StylePtr  Report::getDefaultStyle() const
        {
            return m_defaultStyle;
        }

        void    Report::setStyle( const QString & name, const StylePtr & style )
        {
            m_styles[ name ] = style;
        }

        const StylePtr  Report::getStyle( const QString & name ) const
        {
            if( !m_styles.contains( name ) )
            {
                return StylePtr();
            }

            return m_styles[ name ];
        }

        const QMap< QString, StylePtr >     Report::getStyles() const
        {
            return m_styles;
        }

        void    Report::setQuery( const QString & query )
        {
            m_query = query;
        }

        const QString   Report::getQuery() const
        {
            return m_query;
        }

        void    Report::setField( const QString & name, const FieldPtr & field )
        {
            m_fields[ name ] = field;
        }

        const FieldPtr  Report::getField( const QString & name ) const
        {
            if( !m_fields.contains( name ) )
            {
                return  FieldPtr();
            }

            return m_fields[ name ];
        }

        const QMap< QString, FieldPtr >   Report::getFields() const
        {
            return m_fields;
        }

        void    Report::setTitle( const TitlePtr & title )
        {
            m_title = title;
        }

        const TitlePtr     Report::getTitle() const
        {
            return m_title;
        }

        void    Report::setDetail( const DetailPtr & detail )
        {
            m_detail = detail;
        }

        const DetailPtr     Report::getDetail() const
        {
            return m_detail;
        }

        void Report::setFieldData( const QString field_name, const QVector<QVariant> data )
        {
            m_fields[ field_name ]->setData( data );
        }

        int     Report::getRowCount() const
        {
            return m_rowCount;
        }

        void Report::setRowCount( int count )
        {
            m_rowCount = count;
        }

        const QSize     Report::getSize() const
        {
            return m_size;
        }

        void    Report::setSize( const QSize & size )
        {
            m_size = size;
        }

        int     Report::getHeight() const
        {
            return m_size.height();
        }

        int     Report::getWidth() const
        {
            return m_size.width();
        }

        int     Report::getLeftMargin() const
        {
            return m_margins.left();
        }

        int     Report::getTopMargin() const
        {
            return m_margins.top();
        }

        int     Report::getRightMargin() const
        {
            return m_margins.right();
        }

        int     Report::getBottomMargin() const
        {
            return m_margins.bottom();
        }

        const QMargins  Report::getMargins() const
        {
            return m_margins;
        }

        void    Report::setLeftMargin( int left )
        {
            m_margins.setLeft( left );
        }

        void    Report::setTopMargin( int top )
        {
            m_margins.setTop( top );
        }

        void    Report::setRightMargin( int right )
        {
            m_margins.setRight( right );
        }

        void    Report::setBottomMargin( int bottom )
        {
            m_margins.setBottom( bottom );
        }

        void    Report::setMargins( int left, int top, int right, int bottom )
        {
            setLeftMargin( left );
            setTopMargin( top );
            setRightMargin( right );
            setBottomMargin( bottom );
        }

        void    Report::setMargins( const QMargins & margins )
        {
            m_margins = margins;
        }

    }
}
