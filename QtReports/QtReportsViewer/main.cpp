#include "qtreportsviewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtReportsViewer w;
	w.show();
	return a.exec();
}
