#include "../painter.hpp"
#include "widget.hpp"

namespace qtreports {
    namespace detail {

        Widget::Widget() :
            m_pos( 0, 0 ),
            m_size( 0, 0 ) {}

        Widget::~Widget() {}

        void	Widget::setPosition( const QPoint & pos ) {
            if( pos.x() >= 0 && pos.y() >= 0 )
                m_pos = pos;
        }

        void	Widget::setSize( const QSize & size ) {
            m_size = size;
        }

        void	Widget::setStyleName( const QString & name ) {
            m_styleName = name;
        }

        const QPoint    Widget::getPos() const {
            return m_pos;
        }

        int             Widget::getX() const {
            return m_pos.x();
        }

        int             Widget::getY() const {
            return m_pos.y();
        }

        const QSize     Widget::getSize() const {
            return m_size;
        }

        int             Widget::getWidth() const {
            return m_size.width();
        }

        int             Widget::getHeight() const {
            return m_size.height();
        }

        const QString   Widget::getStyleName() const {
            return m_styleName;
        }

        bool	Widget::setParameter( const QString & name, const QVariant & value ) {
            QString _x( "x" ), _y( "y" ), _w( "w" ), _h( "h" ), _style_name( "style_name" );

            if( !value.isValid() ) {
                m_lastError = "Invalid parameter value";
                return false;
            }

            if( isEquals( name, _x ) ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_pos.setX( value.toInt() );

                return true;
            }

            if( isEquals( name, _y ) ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_pos.setY( value.toInt() );

                return true;
            }

            if( isEquals( name, _w ) ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_size.setWidth( value.toInt() );
                return true;
            }

            if( isEquals( name, _h ) ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_size.setHeight( value.toInt() );
                return true;
            }

            if( isEquals( name, _style_name ) ) {
                if( value.type() != QVariant::String ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_styleName = value.toString();

                return true;
            }

            return Object::setParameter( name, value );
        }

    }
}
