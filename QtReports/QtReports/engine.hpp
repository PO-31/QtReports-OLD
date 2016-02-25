#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <QObject>
#include <QString>
#include <QMap>
#include <QSqlDatabase>
#include <QPrinter>
#include "translator.hpp"
#include "processeddb.hpp"
#include "painter.hpp"
#include "tags/object.hpp"
#include "tags/report.hpp"

namespace qtreports {

    class Engine : public QObject {

    public:
        Engine( QObject * parent = 0 );
        ~Engine();

        bool	compile( const QString & path );
        bool	setParameters( const QMap< QString, QString > & map );
        bool	setConnection( const QSqlDatabase & connection );

        bool	createPDF( const QString & path );
        bool	createHTML( const QString & path );//etc.
        bool	print();

        const QString		getLastError() const;
        const QWidgetPtr	getWidget() const;
        const bool			isCompiled() const;


    private:
		QString		m_lastError, m_compiledPath;
		QWidgetPtr	m_widget;
		bool		m_isCompiled;

		void		drawPreview( QPrinter * printer );
    };

}
#endif // ENGINE_HPP
