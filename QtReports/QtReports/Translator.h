#pragma once
#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <QString>
#include <QWidget>
#include <QSharedPointer>

#include <QFile>

#include <QIODevice>

#include <QVector>

#include <QVector>

#include "Report.h"

#include "Style.h"

namespace qtreports {
    typedef QSharedPointer< QWidget > QWidgetPtr;

    //All support classes in detail
    namespace detail {

        class Translator {

        public:
            Translator();
            ~Translator();

            bool	parse( const QString & path );

            Report* getReport();
            QVector<Style> getStyles();

            const QString		getLastError();
            const QWidgetPtr	getWidget() const;

        private:

            QVector<QString>		m_lastError;
            QWidgetPtr	m_widget;

        };

    }
}
#endif // TRANSLATOR_H
