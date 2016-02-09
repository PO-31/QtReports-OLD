#include <QtWidgets/QApplication>

int main( int argc, char *argv[] ) {
	QApplication a( argc, argv );

	qtreports::Engine engine;
	//QString( argv[ 1 ] ) or std::string( argv[ 1 ] )
	engine.compile( "blabla.report" );
	qtreports::WidgetPtr widget = engine.getWidget();
	widget->show();

	return a.exec();
}
