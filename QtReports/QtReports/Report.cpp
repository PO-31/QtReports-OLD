#include "Report.h"

Report::Report() : m_page_width(600), m_page_height(400), m_is_vertical(true)
{

}

bool Report::drawReport(Painter &p, const ProcessedDB &db)
{
    do
    {
        if (!draw(p, db))
            return false;

        p.pageDrawingComplete();
    }
    while ((p.isNewPageRequested()));

    return true;
}
