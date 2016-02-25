#pragma once
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP
#include <QString>
#include <QWidget>
#include <QSharedPointer>
#include <QXmlStreamReader>
#include "tags/report.hpp"

namespace qtreports {
	typedef QSharedPointer< QWidget > QWidgetPtr;

	//All support classes in detail
	namespace detail {

		class Parser {

		public:
			Parser();
			~Parser();

			bool	parse( const QString & path );

			const ReportPtr		getReport() const;
			const QString		getLastError() const;
			const QWidgetPtr	getWidget() const;

		private:
			bool	parseReport( const QString & text );
			bool	parseDetail( const QString & text );
			void	createWidget();

			ReportPtr	m_report;
			QString		m_lastError;
			QWidgetPtr	m_widget;

		};

	}
}
#endif // TRANSLATOR_HPP