#include "replacer.hpp"

namespace qtreports
{
    namespace detail
    {

        Replacer::Replacer() {}

        Replacer::~Replacer() {}

        QString     Replacer::replaceParameters( const ReportPtr & report, const QString & text )
        {
            Q_UNUSED( report );
            return text;
        }

        QString     Replacer::replaceField( const ReportPtr & report, const QString & text, int i )
        {
            Q_UNUSED( report );
            Q_UNUSED( i );
            return text;
        }

    }
}
