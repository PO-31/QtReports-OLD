#pragma once
#ifndef REPORT_HPP
#define REPORT_HPP
#include <QString>
#include <QSize>
#include <QSharedPointer>
#include "tags/object.hpp"
#include "painter.hpp"
#include "processeddb.hpp"

namespace qtreports {
	namespace detail {
		class Report : public Object {

		public:
			Report();
			~Report();

			bool	draw( Painter & p, const ProcessedDB & db );

			QString	asHTML() const;

			bool	setParameter( const QString & name, const QVariant & value );

		protected:

			bool	drawSelf( Painter & painter, const ProcessedDB & db );
			bool	prepareChilds( Painter & painter, const ProcessedDB & db );

			bool	m_isVertical;
			QSize	m_size;

		};

		typedef QSharedPointer< Report > ReportPtr;
	}
}

#endif // REPORT_HPP
