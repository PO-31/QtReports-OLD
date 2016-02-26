#include "report.hpp"

namespace qtreports {
	namespace detail {

		Report::Report() :
			m_isVertical( true ),
			m_size( 600, 400 ) {}

		Report::~Report() {}

		bool	Report::draw( Painter & p, const ProcessedDB & db ) {
			do {
				if( !Object::draw( p, db ) ) {
					return false;
				}

				p.pageDrawingComplete();
			} 
			while( p.isNewPageRequested() );

			return true;
		}

		QString		Report::asHTML() const {
            return "Hello, world";
        }

        bool Report::setParameter(const QString &name, const QVariant &value)
        {
            QString page_width("page_width"), page_height("page_height"),
                    isVertical("is_vertical");

            if( !value.isValid() ) {
                m_lastError = "Invalid parameter value";
                return false;
            }

            if( page_width.compare( name, Qt::CaseInsensitive ) == 0 ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_size.setWidth(value.toInt() );

                return true;
            }

            if( page_height.compare( name, Qt::CaseInsensitive ) == 0 ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_size.setWidth(value.toInt() );

                return true;
            }

            if( isVertical.compare( name, Qt::CaseInsensitive ) == 0 ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_isVertical = value.toBool();
                return true;
            }

            if (!Object::setParameter(name, value))
                return false;
            else
                return true;
        }

        bool	Report::drawSelf( Painter & /*painter*/, const ProcessedDB & /*db*/ ) {
            return true;
		}

        bool	Report::prepareChilds( Painter & /*painter*/, const ProcessedDB & /*db*/ ) {
            return true;
		}

	}
}
