#include <QtWidgets/QApplication>
#include <QMessageBox>
#include "../QtReports/engine.hpp"

int main( int argc, char *argv[] ) {
	QApplication a( argc, argv );
	//Need gui interface for select report file ???

	//If console
	QString path = argc > 1 ? argv[ 1 ] : "default.qreport";
	qtreports::Engine engine;
	bool result = engine.compile( path );
	if( !result ) {
		QMessageBox::critical( 0, "Error: ", engine.getLastError() );
		return -1;
	}

	auto widget = engine.getWidget();
	if( widget.isNull() ) {
		QMessageBox::critical( 0, "Error: ", "Widget is empty" );
		return -1;
	}

	widget->show();
	//engine.print();
	//engine.createPDF( "test.pdf" );
	//engine.createHTML( "test.html" );

	return a.exec();
}
