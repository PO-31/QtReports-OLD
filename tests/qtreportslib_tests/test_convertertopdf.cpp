#include <QTest>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <engine.hpp>
#include <converters/convertertopdf.hpp>
#include "test_convertertopdf.hpp"
#include <QDebug>

Test_ConverterToPdf::Test_ConverterToPdf( QObject * parent ) :
    QObject( parent ) {}

Test_ConverterToPdf::~Test_ConverterToPdf() {}

void    Test_ConverterToPdf::convert() {
    QString reportPath = QFINDTESTDATA( "full.qrxml" );
	qDebug() << endl << "Used report: " << reportPath;
	
    qtreports::Engine engine;
    QVERIFY2( engine.open( reportPath ), engine.getLastError().toStdString().c_str() );
	
    QMap < QString, QString > map;
    map[ "title" ] = "Best Title in World";
    qDebug() << endl << "Used map: " << map;
	QVERIFY2( engine.setParameters( map ), engine.getLastError().toStdString().c_str() );

    QString dbPath = QFINDTESTDATA( "images.db" );
    qDebug() << endl << "Used db: " << dbPath;
    auto db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( dbPath );
	QVERIFY2( db.open(), db.lastError().text().toStdString().c_str() );
	QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );

    auto report = engine.getReport();
	auto outPath = "test.pdf";

    qtreports::detail::ConverterToPDF converter( report );
    QVERIFY2( converter.convert( outPath ), converter.getLastError().toStdString().c_str() );
    QCOMPARE( converter.getDPI(), 600 );
    QCOMPARE( converter.getLastError(), QString() );
	
	QCOMPARE( QFile::exists( outPath ), true );
    QCOMPARE( QFile::remove( outPath ), true );
	//QVERIFY( QFile( test.pdf ).size() != 0 );
}

void    Test_ConverterToPdf::setDPI()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToPDF converter( report );

    converter.setDPI( 500 );
    QCOMPARE( converter.getDPI(), 500 );
}

void    Test_ConverterToPdf::getDPI()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToPDF converter( report );

    QCOMPARE( converter.getDPI(), 600 );
}

void    Test_ConverterToPdf::getLastError()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToPDF converter( report );

    QCOMPARE( converter.getLastError(), QString() );
}