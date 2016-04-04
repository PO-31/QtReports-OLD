#include "report.hpp"

namespace qtreports
{
    namespace detail
    {

        Report::Report() :
            m_orientation( QPrinter::Orientation::Landscape ),
            m_size( 595, 842 ),
            m_margins( 30, 30, 30, 30 ),
            m_rowCount( 0 )
        {}

        Report::~Report() {}

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
            return m_styles.value( name );
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
            return m_fields.value( name );
        }

        const QMap< QString, FieldPtr >   Report::getFields() const
        {
            return m_fields;
        }

        void    Report::setFieldData( const QString & name, const QVector< QVariant > & data )
        {
            auto field = getField( name );
            if( !field.isNull() )
            {
                field->setData( data );
            }
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

        void    Report::setParameter( const QString & name, const QString & value )
        {
            m_parameters[ name ] = value;
        }

        void    Report::setParameters( const QMap< QString, QString > & parameters )
        {
            m_parameters = parameters;
        }

        const QString  Report::getParameter( const QString & name ) const
        {
            return m_parameters.value( name );
        }

        const QMap< QString, QString >   Report::getParameters() const
        {
            return m_parameters;
        }

        int     Report::getRowCount() const
        {
            return m_rowCount;
        }

        void    Report::setRowCount( int count )
        {
            m_rowCount = count;
        }

        QPrinter::Orientation     Report::getOrientation() const
        {
            return m_orientation;
        }

        void    Report::setOrientation( QPrinter::Orientation orientation )
        {
            m_orientation = orientation;
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
