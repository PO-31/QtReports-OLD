#ifndef QTREPORTS_H
#define QTREPORTS_H

#include <QtWidgets/QMainWindow>
#include "ui_qtreports.h"

class QtReports : public QMainWindow
{
	Q_OBJECT

public:
	QtReports(QWidget *parent = 0);
	~QtReports();

private:
	Ui::QtReportsClass ui;
};

#endif // QTREPORTS_H
