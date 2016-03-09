#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QDir>
#include <engine.hpp>

int main( int argc, char *argv[] ) {
    QApplication a( argc, argv );
    //Need initialize first of engine widget( for not memory problem );
    QMainWindow window;
    QMenuBar bar( &window );
    QMenu file( "File", &bar );
    QMenu convert( "Convert", &bar );

    QString path = argc > 1 ? argv[ 1 ] : "../tests/qtreportslib_tests/default.qreport";
    qtreports::Engine engine( path );
    if( !engine.isOpened() ) {
        QMessageBox::critical( 0, "Error: ", engine.getLastError() );
        return -1;
    }

    QMap < QString, QString > map;
    map[ "title" ] = "Best Title in World";
    bool result = engine.setParameters( map );//{ { "title", "Best Title in World" } }
    if( !result ) {
        QMessageBox::critical( 0, "Error: ", engine.getLastError() );
        return -1;
    }

    auto widget = engine.createWidget();
    if( widget.isNull() ) {
        QMessageBox::critical( 0, "Error: ", "Widget is empty" );
        return -1;
    }

    window.setCentralWidget( widget.data() );
    window.resize( widget->size() );
    window.show();

    QAction print( QObject::tr( "&Print..." ), &window );
    print.setShortcuts( QKeySequence::Print );
    print.setStatusTip( QObject::tr( "Print current report" ) );
    QObject::connect( &print, &QAction::triggered, [ & ]() {
        bool result = engine.print();
        if( !result ) {
            QMessageBox::critical( 0, "Error: ", engine.getLastError() );
            return;
        }
    } );

    QAction createPDF( QObject::tr( "&Create PDF..." ), &window );
    createPDF.setStatusTip( QObject::tr( "Create PDF from current report" ) );
    QObject::connect( &createPDF, &QAction::triggered, [ & ]() {
        auto file = QFileDialog::getSaveFileName( &window,
            QObject::tr( "Save as PDF" ),
            QString(),
            QObject::tr( "PDF Files (*.pdf)" ) );
        if( file.isEmpty() ) {
            return;
        }

        bool result = engine.createPDF( file );
        if( !result ) {
            QMessageBox::critical( 0, "Error: ", engine.getLastError() );
            return;
        }
    } );

    QAction createHTML( QObject::tr( "&Create HTML..." ), &window );
    createHTML.setStatusTip( QObject::tr( "Create HTML from current report" ) );
    QObject::connect( &createHTML, &QAction::triggered, [ & ]() {
        auto file = QFileDialog::getSaveFileName( &window,
            QObject::tr( "Save as HTML" ),
            QString(),
            QObject::tr( "HTML Files (*.html *.htm)" ) );
        if( file.isEmpty() ) {
            return;
        }

        bool result = engine.createHTML( file );
        if( !result ) {
            QMessageBox::critical( 0, "Error: ", engine.getLastError() );
            return;
        }
    } );

    QAction close( QObject::tr( "&Close..." ), &window );
    close.setShortcuts( QKeySequence::Close );
    close.setStatusTip( QObject::tr( "Close current report" ) );
    QObject::connect( &close, &QAction::triggered, [ & ]() {
        if( window.centralWidget() != nullptr ) {
#if ( QT_VERSION >= QT_VERSION_CHECK( 5, 2, 0 ) )
            window.takeCentralWidget();
#endif
        }

        print.setEnabled( false );
        convert.setEnabled( false );
        close.setEnabled( false );
    } );

    QAction open( QObject::tr( "&Open..." ), &window );
    open.setShortcuts( QKeySequence::Open );
    open.setStatusTip( QObject::tr( "Open an existing file" ) );
    QObject::connect( &open, &QAction::triggered, [ & ]() {
        auto file = QFileDialog::getOpenFileName( &window,
            QObject::tr( "Open QReport" ),
            QString(),
            QObject::tr( "QReport Files (*.qreport);;All Files (*.*)" ) );
        if( file.isEmpty() ) {
            return;
        }
        
        if( window.centralWidget() != nullptr ) {
        #if ( QT_VERSION >= QT_VERSION_CHECK( 5, 2, 0 ) )
            window.takeCentralWidget();
        #endif
        }

        bool result = engine.open( file );
        print.setEnabled( engine.isOpened() );
        convert.setEnabled( engine.isOpened() );
        close.setEnabled( engine.isOpened() );
        if( !result ) {
            QMessageBox::critical( 0, "Error: ", engine.getLastError() );
            return;
        }

        widget = engine.createWidget();
        if( widget.isNull() ) {
            QMessageBox::critical( 0, "Error: ", "Widget is empty" );
            return;
        }

        window.setCentralWidget( widget.data() );
        window.resize( widget->size() );
    } );

    QAction exit( QObject::tr( "&Exit..." ), &window );
    exit.setShortcuts( QKeySequence::Close );
    QObject::connect( &exit, &QAction::triggered, &window, &QMainWindow::close );

    print.setEnabled( engine.isOpened() );
    convert.setEnabled( engine.isOpened() );

    file.addAction( &open );
    file.addAction( &print );
    file.addAction( &close );
    file.addAction( &exit );
    convert.addAction( &createPDF );
    convert.addAction( &createHTML );
    bar.addMenu( &file );
    bar.addMenu( &convert );
    window.setMenuBar( &bar );
    //engine.createPDF( "test.pdf" );
    //engine.createHTML( "C:/Users/haven/Desktop/test.html" );

    return a.exec();
}
