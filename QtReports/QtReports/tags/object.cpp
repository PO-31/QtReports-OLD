#include "object.hpp"

namespace qtreports {
	namespace detail {

		Object::Object( ObjectPtr parent ) :
			m_parent( parent ),
			m_pos( 0, 0 ),
			m_size( 0, 0 ),
			m_styleId( 0 ) {}

		Object::~Object() {}

		bool	Object::draw( Painter & painter, const ProcessedDB & db ) {
			int id = painter.beginObjectDrawing();

            if( !this->drawSelf( painter, db ) ) {
				painter.endObjectDrawing( id );
				return false;
			}

            if( !this->prepareChilds( painter, db ) ) {
				painter.endObjectDrawing( id );
				return false;
			}

            if( !this->drawChilds( painter, db ) ) {
				painter.endObjectDrawing( id );
				return false;
			}

			painter.endObjectDrawing( id );
			return true;
		}

		void	Object::setPosition( const QPoint & pos ) {
			m_pos = pos;
		}

		void	Object::setSize( const QSize & size ) {
			m_size = size;
		}

		bool	Object::setParameter( const QString & name, const QVariant & value ) {
			QString _x( "x" ), _y( "y" ), _w( "w" ), _h( "h" ), _style_id( "style_id" );

			if( !value.isValid() ) {
				m_lastError = "Invalid parameter value";
				return false;
			}

			if( _x.compare( name, Qt::CaseInsensitive ) == 0 ) {
				if( value.type() != QVariant::Int ) {
					m_lastError = "Invalid type for this argument";
					return false;
				}

				m_pos.setX( value.toInt() );

				return true;
			}

			if( _y.compare( name, Qt::CaseInsensitive ) == 0 ) {
				if( value.type() != QVariant::Int ) {
					m_lastError = "Invalid type for this argument";
					return false;
				}

				m_pos.setY( value.toInt() );

				return true;
			}

			if( _w.compare( name, Qt::CaseInsensitive ) == 0 ) {
				if( value.type() != QVariant::Int ) {
					m_lastError = "Invalid type for this argument";
					return false;
				}

				m_size.setWidth( value.toInt() );
				return true;
			}

			if( _h.compare( name, Qt::CaseInsensitive ) == 0 ) {
				if( value.type() != QVariant::Int ) {
					m_lastError = "Invalid type for this argument";
					return false;
				}

				m_size.setHeight( value.toInt() );
				return true;
			}

			if( _style_id.compare( name, Qt::CaseInsensitive ) == 0 ) {
				if( value.type() != QVariant::Int ) {
					m_lastError = "Invalid type for this argument";
					return false;
				}

				m_styleId = value.toInt();

				return true;
			}


			m_lastError = "Unknown argument";
			return false;
		}

		void	Object::addChild( const ObjectPtr & object ) {
			if( !object.isNull() ) {
				return;
			}

			m_childs.append( object );
		}

		const ObjectPtr		Object::getChild( int index ) const {
			if( index < 0 || index >= m_childs.size() ) {
				return ObjectPtr();
			}

			return m_childs.at( index );
		}

		void	Object::setStyleId( int styleId ) {
			m_styleId = styleId;
		}

		int		Object::getStyleId() const {
			return m_styleId;
		}

		QString	Object::getLastError() const {
			return m_lastError;
		}

		bool	Object::drawChilds( Painter & painter, const ProcessedDB & db ) {
			for( auto && child : m_childs ) {
				if( !child->draw( painter, db ) ) {
					return false;
				}
			}

            return true;
        }

        DrawingExeption::DrawingExeption(QString error): m_error(error)
        {

        }

        QString DrawingExeption::getError()
        {
            return m_error;
        }

	}
}
