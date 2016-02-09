#pragma once
#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <QString>
#include <QWidget>
#include <QSharedPointer>

namespace qtreports {
	typedef QSharedPointer< QWidget > QWidgetPtr;

	//All support classes in detail
	namespace detail {
		
		class Translator {

		public:
			Translator();
			~Translator();

			bool	parse( const QString & path );

			const QString		getLastError() const;
			const QWidgetPtr	getWidget() const;

		private:
			QString		m_lastError;
			QWidgetPtr	m_widget;

		};

	}
}
#endif // TRANSLATOR_H