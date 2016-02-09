#ifndef QTREPORTSVIEWER_H
#define QTREPORTSVIEWER_H

#include <QtWidgets/QMainWindow>
#include "ui_qtreportsviewer.h"

class QtReportsViewer : public QMainWindow
{
	Q_OBJECT

public:
	QtReportsViewer(QWidget *parent = 0);
	~QtReportsViewer();

private:
	Ui::QtReportsViewerClass ui;
};

#endif // QTREPORTSVIEWER_H
