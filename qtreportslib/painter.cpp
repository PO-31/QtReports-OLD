#include <QPdfWriter>
#include "tags/report.hpp"
#include "tags/style.hpp"
#include "painter.hpp"

namespace qtreports {
    namespace detail {

        Painter::Painter() :
            m_isNewPage( false ),
            m_pageCounter( 0 ) {}

        bool	Painter::beginPDFDrawing( const QString & path ) {
            QPdfWriter writer( path + ".pdf" );
            m_painter.begin( &writer );
            m_pageCounter = 1;

            return true;
        }

        int		Painter::beginObjectDrawing() {

            m_objects.append( m_objects.size() );

            return m_objects.size();
        }

        bool	Painter::setWorkspace( const QPoint & pos, const QSize & size ) {
            bool isNormalSize = true;

            if( m_workspaces.isEmpty() ) {
                m_workspaces.append( QRect( pos, size ) );
            }
            else {
                QPoint newPos(
                    m_workspaces.last().x() + pos.x(),
                    m_workspaces.last().y() + pos.y()
                    );

                QSize newSize = size;

                if( size.width() > m_workspaces.last().width() ) {
                    newSize.setWidth( m_workspaces.last().width() );
                    isNormalSize = false;
                }

                if( size.height() > m_workspaces.last().height() ) {
                    newSize.setHeight( m_workspaces.last().height() );
                    isNormalSize = false;
                }

                m_workspaces.append( QRect( newPos, newSize ) );
            }

            return isNormalSize;
        }

        bool	Painter::endObjectDrawing( int workspaceId ) {
            if( workspaceId >= m_workspaces.size() ) {
                return false;
            }

            m_objects.remove( workspaceId, m_objects.size() - workspaceId );
            m_workspaces.remove( workspaceId, m_workspaces.size() - workspaceId );

            return true;
        }

        void	Painter::pageDrawingComplete() {
            if( m_isNewPage ) {
                newPage();
                ++m_pageCounter;
                m_isNewPage = false;
            }
            else {
                m_pageCounter = 0;
            }

            m_objects.clear();
            m_workspaces.clear();
        }

        bool	Painter::drawLine( const QPoint & point1, const QPoint & point2 ) {
            m_painter.drawLine( point1, point2 );
            return true;
        }

        bool Painter::drawRect(const QRect &rect)
        {
            m_painter.drawRect(rect);
            return true;
        }

        bool Painter::drawImage( const QString & path, const QRect & rect ) {
            QImage image( path );
            bool isLoaded = !image.isNull();

            if( isLoaded ) {
                m_painter.drawImage( rect, image );
            }

            return isLoaded;
        }

        bool	Painter::drawText( int x, int y, const QString & text ) {
            m_painter.drawText( x, y, text );
            return true;
        }

        void	Painter::newPageRequest() {
            m_isNewPage = true;
        }

        bool	Painter::isNewPageRequested() const {
            return m_isNewPage;
        }

        bool	Painter::setCurrentPage( int index ) {
            Q_UNUSED( index );
            return true;
        }

        int		Painter::pagesCount() const {
            return m_pageCounter;
        }

        int		Painter::currentPage() const {
            return 0;
        }

        void	Painter::setDefaultStyle() {
            setStyle( m_report->getDefaultStyle() );
        }

        void	Painter::setStyle( const QString & name ) {
            setStyle( m_report->getStyle( name ) );
        }

        const QString	Painter::getLastError() const {
            return m_last_error;
        }

        void	Painter::newPage() {
            //m_pdfWriter->newPage();
        }

        void    Painter::setStyle( const StylePtr & style ) {
            QFont font;
            font.setPointSize( style->getFontSize() );
            font.setFamily( style->getFontName() );

            if( style->isBold() ) {
                font.setBold( true );
            }
            else {
                font.setBold( false );
            }

            if( style->isItalic() ) {
                font.setItalic( true );
            }
            else {
                font.setItalic( false );
            }

            m_painter.setFont( font );
            m_painter.setPen( style->getFontColor() );
        }

    }
}

