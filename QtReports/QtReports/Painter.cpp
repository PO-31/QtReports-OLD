#include "painter.hpp"

namespace qtreports {
	namespace detail {

		Painter::Painter() {}

		bool	Painter::beginPDFDrawing( const QString & path ) {
			return false;
		}

		int		Painter::beginObjectDrawing() {
			return 0;
		}

		bool	Painter::setWorkspace( const QPoint & pos, const QSize & size ) {
			return false;
		}

		bool	Painter::endObjectDrawing( int workspace_id ) {
			return false;
		}

		void	Painter::pageDrawingComplete() {}

		bool	Painter::drawLine( const QPoint & point1, const QPoint & point2 ) {
			return false;
		}

		bool	Painter::drawText( int x, int y, const QString & text ) {
			return false;
		}

		void	Painter::setFont() {
		}

		void	Painter::setPen() {
		}

		void	Painter::setBrush() {
		}

		void	Painter::newPageRequest() {
		}

		bool	Painter::isNewPageRequested() {
			return false;
		}

		bool	Painter::setCurrentPage( int ind ) {
			return false;
		}

		int		Painter::pagesCount() {
			return 0;
		}

		int		Painter::currPage() {
			return 0;
		}

		void	Painter::setStyle( int style_id ) {
		}

		QString	Painter::getLastError() const {
			return QString();
		}

		void Painter::newPage() {
		}

		void Painter::setStyle( const Style & style ) {
		}

	}
}

