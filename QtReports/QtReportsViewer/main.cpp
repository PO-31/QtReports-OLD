#include <QtWidgets/QApplication>
#include "../QtReports/engine.hpp"

int main( int argc, char *argv[] ) {
	QApplication a( argc, argv );
	//Need gui interface for select report file ???

	//If console
	QString path = argc > 1 ? argv[ 1 ] : "default.report";
	qtreports::Engine engine;
	engine.compile( path );
	
	qtreports::QWidgetPtr widget = engine.getWidget();
	widget->show();
	//engine.print();
	//engine.createPDF( "test.pdf" );

	return a.exec();
}
