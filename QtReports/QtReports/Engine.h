#ifndef ENGINE_H
#define ENGINE_H
#include <QObject>
#include <QString>
#include <QMap>
#include <QSqlDatabase>
#include <QPrinter>

#include "Translator.h"
#include "ProcessedDB.h"


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

        const QString		getLastError();
        const QWidgetPtr	getWidget() const;
        bool			isCompiled() const;


    private:
        QVector<QString>		m_lastError;
        QString m_compiledPath;
        QWidgetPtr	m_widget;
        bool		m_isCompiled;

        void		drawPreview( QPrinter * printer );

    };

}
#endif // ENGINE_H
