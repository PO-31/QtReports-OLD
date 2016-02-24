#ifndef REPORT_H
#define REPORT_H

#include "Object.h"

class Report : public Object
{
public:
    Report();

    bool draw_report(Painter &p, const ProcessedDB &db);

protected:

    virtual bool draw_self(Painter &/*p*/, const ProcessedDB &/*db*/) {return true;}
    virtual bool prepare_childs(Painter &/*p*/, const ProcessedDB &/*db*/) {return true;}

    int page_width, page_height;

    bool is_vertical;
};

#endif // REPORT_H
