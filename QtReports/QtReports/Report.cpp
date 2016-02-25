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

		bool	Report::drawSelf( Painter & painter, const ProcessedDB & db ) {
			return false;
		}

		bool	Report::prepareChilds( Painter & painter, const ProcessedDB & db ) {
			return false;
		}

	}
}
