#include "Report.h"

Report::Report() : page_width(600), page_height(400), is_vertical(true)
{

}

bool Report::draw_report(Painter &p, const ProcessedDB &db)
{
    do
    {
        if (!draw(p, db))
            return false;

        p.page_drawing_complete();
    }
    while ((p.is_new_page_requested()));

    return true;
}
