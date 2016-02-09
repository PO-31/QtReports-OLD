#pragma once
#ifndef ENGINE_H
#define ENGINE_H
#include <QString>
#include <QMap>
#include <QSqlDatabase>
#include "translator.hpp"

namespace qtreports {

	class Engine {

	public:
		Engine();
		~Engine();

		bool	compile( const QString & path );
		bool	setParameters( const QMap< QString, QString > & map );
		bool	setConnection( const QSqlDatabase & connection );

		bool	createPDF( const QString & path );
		bool	createHTML( const QString & path );//etc.

		const QString		getLastError() const;
		const QWidgetPtr	getWidget() const;

	private:
		QString		m_lastError;
		QWidgetPtr	m_widget;

	};

}
#endif // ENGINE_H