#include "painter.hpp"

namespace qtreports {
	namespace detail {

        Painter::Painter():page_counter(0), is_new_page(false) {

        }

		bool	Painter::beginPDFDrawing( const QString & path ) {

            qpdf_writer = new QPdfWriter(path + ".pdf");
            q_painter = new QPainter(qpdf_writer);
            page_counter = 1;

            return true;
		}

		int		Painter::beginObjectDrawing() {

            objects_ids.append(objects_ids.count());

            return objects_ids.count();
		}

		bool	Painter::setWorkspace( const QPoint & pos, const QSize & size ) {

            bool normal_size = true;

            if (workspaces_ids.count() == 0)
                workspaces_ids.append(QRect(pos, size));
            else
            {
                QPoint new_pos = QPoint(workspaces_ids.last().x() + pos.x(),
                                       workspaces_ids.last().y() + pos.y());

                QSize new_size = size;

                if (size.width() > workspaces_ids.last().width())
                {
                    new_size.setWidth(workspaces_ids.last().width());
                    normal_size = false;
                }

                if (size.height() > workspaces_ids.last().height())
                {
                    new_size.setHeight(workspaces_ids.last().height());
                    normal_size = false;
                }

                workspaces_ids.append(QRect(new_pos, new_size));
            }
            return normal_size;
		}

		bool	Painter::endObjectDrawing( int workspace_id ) {

            if (workspace_id >= workspaces_ids.count())
                return false;

            objects_ids.remove(workspace_id, objects_ids.count() - workspace_id);
            workspaces_ids.remove(workspace_id, workspaces_ids.count() - workspace_id);

            return true;
        }

        void	Painter::pageDrawingComplete() {

            if (is_new_page)
            {
                newPage();
                ++page_counter;
                is_new_page = false;
            }
            else
                page_counter = 0;

            objects_ids.clear();
            workspaces_ids.clear();

        }

		bool	Painter::drawLine( const QPoint & point1, const QPoint & point2 ) {

            q_painter->drawLine(point1, point2);

            return true;
		}

		bool	Painter::drawText( int x, int y, const QString & text ) {

            q_painter->drawText(x, y, text);

            return true;
		}

		void	Painter::newPageRequest() {

            is_new_page = true;
		}

		bool	Painter::isNewPageRequested() {

            return is_new_page;
		}

		bool	Painter::setCurrentPage( int ind ) {

            return true;
		}

		int		Painter::pagesCount() {

            return page_counter;
		}

		int		Painter::currPage() {
			return 0;
		}

		void	Painter::setStyle( int style_id ) {

            if (style_id < 0)
            {
                for (int i = 0; i < styles->count(); ++i)
                {
                    if (styles->at(i).isDefault())
                    {
                        setStyle(styles->at(i));
                        return;
                    }
                }
            }
            else
            {
                for (int i = 0; i < styles->count(); ++i)
                {
                    if (styles->at(i).id() == style_id)
                    {
                        setStyle(styles->at(i));
                        return;
                    }
                }
            }

		}

		QString	Painter::getLastError() const {

            return m_last_error;
		}

		void Painter::newPage() {

            qpdf_writer->newPage();
		}

		void Painter::setStyle( const Style & style ) {

            QFont font;

            font.setPointSize(style.fontSize());
            font.setFamily(style.fontName());

            if (style.isBold())
                font.setBold(true);
            else
                font.setBold(false);

            if (style.isItalic())
                font.setItalic(true);
            else
                font.setItalic(false);

            q_painter->setFont(font);
            q_painter->setPen(style.fontColor());
		}

	}
}

