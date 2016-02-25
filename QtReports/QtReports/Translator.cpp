#include <QFile>
#include <QXmlStreamReader>
#include <QLabel>
#include <QTextBrowser>
#include <QVBoxLayout>
#include "Translator.h"

namespace qtreports {
    namespace detail {

        Translator::Translator() {}

        Translator::~Translator() {}

        bool Translator::parse( const QString & path )
        {
            if( !QFile::exists( path ) ) {
                m_lastError.append("The file not exists");
                return false;
            }

            QFile file( path );
            file.open( QIODevice::ReadOnly | QIODevice::Text );
            if ( !file.isOpen() ) {
                m_lastError.append("The file can not be opened");
                return false;
            }

            QByteArray text = file.readAll();



            return true;
        }

        const QString	Translator::getLastError()
        {
            if (m_lastError.size())
                return QString();

            return m_lastError.takeLast();
        }

        const QWidgetPtr	Translator::getWidget() const
        {
            return m_widget;
        }

    }
}
