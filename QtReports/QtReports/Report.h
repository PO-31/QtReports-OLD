#ifndef REPORT_H
#define REPORT_H

#include "Object.h"

class Report : public Object
{
public:
    Report();

    bool drawReport(Painter &p, const ProcessedDB &db);

protected:

    virtual bool drawSelf(Painter &/*p*/, const ProcessedDB &/*db*/) {return true;}
    virtual bool prepareChilds(Painter &/*p*/, const ProcessedDB &/*db*/) {return true;}

    int m_page_width, m_page_height;

    bool m_is_vertical;
};

#endif // REPORT_H
