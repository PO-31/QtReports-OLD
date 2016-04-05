#include <QRegularExpression>
#include <QTest>
#include <QSize>
#include <parser.hpp>
#include "test_parser.hpp"

Test_Parser::Test_Parser( QObject *parent ) :
    QObject( parent ) {}

void    Test_Parser::ReportTreeParseTest() {
    qtreports::detail::Parser parser;
    QString input = QFINDTESTDATA( "default.qreport" );
    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );
      
    QString input_scheme = QFINDTESTDATA( "default.txt" );
    QFile scheme_file( input_scheme );

    QVERIFY2( scheme_file.open( QIODevice::ReadOnly | QIODevice::Text ), "Can't open default.txt file." );

    qtreports::detail::ReportPtr report = parser.getReport();

    QVector<QString> classes;
    QByteArray line = scheme_file.readLine();

    QString curr_line;

    curr_line = line.data();

    curr_line.remove( curr_line.size() - 1, 1 );

    QString error( curr_line.toLatin1().data() );

    error += " can't be found";

    QVERIFY2( curr_line.compare( report->getName(), Qt::CaseInsensitive ) == 0, error.toLatin1().data() );

    classes.append( curr_line );

    line = scheme_file.readLine();

    curr_line = line.data();

    curr_line.remove( curr_line.size() - 1, 1 );

    /* Styles block */

    if( curr_line.compare( "Styles" ) == 0 )
    {
        int styles_num = report->getStyles().size();

        QVector<QString> styles;

        QVERIFY2( curr_line.compare( "Styles", Qt::CaseInsensitive ) == 0, "No 'Style' line in default.txt" );

        for( int i = 0; i < styles_num; ++i )
        {
            QVERIFY2( !scheme_file.atEnd(), "Styles reading error in default.txt: to few styles in default.txt" );

            line = scheme_file.readLine();

            curr_line = line.data();

            curr_line.remove( curr_line.size() - 1, 1 );

            QVERIFY2( curr_line.compare( "/Styles", Qt::CaseInsensitive ) != 0, "Styles reading error in default.txt: to few styles in default.txt" );

            styles.append( curr_line );
        }

        line = scheme_file.readLine();

        curr_line = line.data();

        curr_line.remove( curr_line.size() - 1, 1 );

        QVERIFY2( curr_line.compare( "/Styles", Qt::CaseInsensitive ) == 0, "Styles reading error in default.txt: can't find '/Styles' in default.txt or to much styles in file" );

        for( int i = 0; i < styles.size(); ++i )
        {
            error = "Style '" + styles.at( i ) + "' not parsed";
            QVERIFY2( !report->getStyle( styles.at( i ) ).isNull(), error.toLatin1().data() );
        }

        line = scheme_file.readLine();

        curr_line = line.data();

        curr_line.remove( curr_line.size() - 1, 1 );
    }

    /* Detail */

    if( curr_line.compare( "Detail" ) == 0 )
    {
        QVERIFY2( !report->getDetail().isNull(), "Detail block not parsed" );

        int bands_num = 0;

        while( !scheme_file.atEnd() )
        {
            line = scheme_file.readLine();

            curr_line = line.data();

            curr_line.remove( curr_line.size() - 1, 1 );

            if( curr_line.compare( "/Detail" ) == 0 )
            {
                QVERIFY2( bands_num == report->getDetail()->getBandsSize(), "To many bands parsed" );
                break;
            }

            if( curr_line.compare( "Band" ) == 0 )
            {
                QVERIFY2( bands_num < report->getDetail()->getBandsSize(), "To few bands parsed" );

                int static_text_num = 0, text_field_num = 0;

                while( !scheme_file.atEnd() )
                {
                    line = scheme_file.readLine();

                    curr_line = line.data();

                    curr_line.remove( curr_line.size() - 1, 1 );

                    if( curr_line.compare( "/Band" ) == 0 )
                    {
                        error = "To many static text objects parsed in band number " + QString::number( bands_num ) +
                            " " + report->getDetail()->getBand( bands_num )->getName();
                        QVERIFY2( static_text_num == report->getDetail()->getBand( bands_num )->getStaticTextsSize(),
                            error.toLatin1().data() );

                        error = "To many text field objects parsed in band number " + QString::number( bands_num ) +
                            " " + report->getDetail()->getBand( bands_num )->getName();
                        QVERIFY2( text_field_num == report->getDetail()->getBand( bands_num )->getTextFieldsSize(),
                            error.toLatin1().data() );

                        break;
                    }

                    if( curr_line.compare( "StaticText" ) == 0 )
                    {
                        error = "To few static text objects parsed in band number " + QString::number( bands_num ) +
                            " " + report->getDetail()->getBand( bands_num )->getName();
                        QVERIFY2( static_text_num < report->getDetail()->getBand( bands_num )->getStaticTextsSize(),
                            error.toLatin1().data() );

                        ++static_text_num;
                    }

                    if( curr_line.compare( "TextField" ) == 0 )
                    {
                        error = "To few text field objects parsed in band number " + QString::number( bands_num ) +
                            " " + report->getDetail()->getBand( bands_num )->getName();
                        QVERIFY2( text_field_num < report->getDetail()->getBand( bands_num )->getTextFieldsSize(),
                            error.toLatin1().data() );

                        ++text_field_num;
                    }
                }

                ++bands_num;
            }
        }

        QVERIFY2( bands_num == report->getDetail()->getBandsSize(), "Detail block test error" );
    }
}

void    Test_Parser::ReportTagParseTest() {
    qtreports::detail::Parser parser;
    QString input = QFINDTESTDATA( "report test.qreport" );
    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();

    QVERIFY2( !report.isNull(), "Null ptr report returned" );

    QVERIFY2( report->getName().compare( "test_report" ) == 0, "Uncorrect report name" );
    /*
    QSize report_size = report->getSize();

    QVERIFY2( report_size.width() == 600, "Uncorrect report width");

    QVERIFY2( report_size.height() == 900, "Uncorrect report height");*/

    QString error = "Wrong query string in report test: '";
    error += report->getQuery();
    error += "'";

    //QVERIFY2( report->getQuery() == " select * from customers ", error.toLatin1().data());

    QVERIFY2( !report->getStyle( "Arial_Normal" ).isNull(), "Null ptr style returned in report test" );

    QVERIFY2( report->getStyle( "Arial_Normal" )->getFontSize() == 12, "Wrong font size in report test" );

    error = "Wrong font name in report test: '";
    error += report->getStyle( "Arial_Normal" )->getFontName();
    error += "'";

    QVERIFY2( report->getStyle( "Arial_Normal" )->getFontName() == "Arial", error.toLatin1().data() );

    error = "Wrong PDF font name in report test: '";
    error += report->getStyle( "Arial_Normal" )->getPDFFontName();
    error += "'";

    QVERIFY2( report->getStyle( "Arial_Normal" )->getPDFFontName() == "c:\\tahoma.ttf", error.toLatin1().data() );

    error = "Wrong PDF encoding in report test: '";
    error += report->getStyle( "Arial_Normal" )->getPDFEncoding();
    error += "'";

    QVERIFY2( report->getStyle( "Arial_Normal" )->getPDFEncoding() == "Cp1251", error.toLatin1().data() );
}

void    Test_Parser::TextTest() {
    qtreports::detail::Parser parser;
    QString input = QFINDTESTDATA( "text test.qreport" );
    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();

    QString error;

    QVERIFY2( !report.isNull(), "Null ptr report returned in text test" );

    QVERIFY2( !report->getDetail().isNull(), "Null ptr detail in text test" );

    QVERIFY2( report->getDetail()->getBandsSize() == 1, "Wrong bands number in text test" );

    QVERIFY2( !report->getDetail()->getBand( 0 ).isNull(), "Null ptr band in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getHeight() == 400, "Wrong band height in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getStaticTextsSize() == 1, "Not one static text in text test" );

    QVERIFY2( !report->getDetail()->getBand( 0 )->getStaticText( 0 ).isNull(), "Null ptr static text in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getStaticText( 0 )->getPos().x() == 380 && report->getDetail()->getBand( 0 )->getStaticText( 0 )->getPos().y() == 0, "Wrong static text position in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getStaticText( 0 )->getWidth() == 200, "Wrong static text width in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getStaticText( 0 )->getHeight() == 20, "Wrong static text height in text test" );

    error = "Wrong static text in text test: '";
    error += report->getDetail()->getBand( 0 )->getStaticText( 0 )->getText();
    error += "'";

    QVERIFY2( report->getDetail()->getBand( 0 )->getStaticText( 0 )->getText() == "Тест !!", error.toLatin1().data() );

    QVERIFY2( report->getDetail()->getBand( 0 )->getTextFieldsSize() == 1, "Not one text field in text test" );

    QVERIFY2( !report->getDetail()->getBand( 0 )->getTextField( 0 ).isNull(), "Null ptr text field in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getTextField( 0 )->getPos().x() == 220 && report->getDetail()->getBand( 0 )->getTextField( 0 )->getPos().y() == 20, "Wrong text field position in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getTextField( 0 )->getWidth() == 100, "Wrong text field width in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getTextField( 0 )->getHeight() == 200, "Wrong text field height in text test" );
/*
    error = "Wrong text field in text test: '";
    error += report->getDetail()->getBand( 0 )->getTextFieldld( 0 )->getText();
    error += "'";
*/
    //QVERIFY2( report->getDetail()->getBand(0)->getTextField(0)->getText() == "$P{title}", error.toLatin1().data() );
}

void Test_Parser::ReportFieldParseTest()
{

    qtreports::detail::Parser parser;
    QString input = QFINDTESTDATA( "field test.qreport" );
    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();
    
    QVERIFY2( !report.isNull(), "Null ptr report returned in text test" );

    QVERIFY2( !report->getField( "Title" ).isNull(), "Null ptr field in field test" );

    QVERIFY2( report->getField("Title")->getClassName() == "QString", "Wrong className in field test");

    //QVERIFY2( report->getField("PersonName")->getData( 0 ) )
    
    
    //QVERIFY2( report->get().getBandsSize() == 1, "Wrong bands number in text test" );

    //QVERIFY2( !report-> getDetail()->getetBand( 0 ).isNull(), "Null ptr band in text test" );
    

    
}

void Test_Parser::ReportLineParseTest()
{
    qtreports::detail::Parser parser;
    QString input = QFINDTESTDATA( "line test.qreport" );
    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();

    QString error;

    QVERIFY2( !report.isNull(), "Null ptr report returned in line test" );

    QVERIFY2( !report->getDetail().isNull(), "Null ptr detail in line test" );

    QVERIFY2( report->getDetail()->getBandsSize() == 1, "Wrong bands number in text test" );

    QVERIFY2( !report->getDetail()->getBand( 0 ).isNull(), "Null ptr band in line test" );

    QVERIFY2( !report->getDetail()->getBand( 0 )->getLine( 0 ).isNull(), "Null ptr in line test" );

   // QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getAlignment() == Qt::Alignment(), "Wrong line alignment in line test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getHeight() == 25, "Wrong line height in line test");

    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getPos().x() == 200 && report->getDetail()->getBand( 0 )->getLine( 0 )->getPos().y() == 20, "Wrong position in line test");

    // QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getRect() )
    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getSize() == QSize(5,2), "Wrong line size in line test");

   //  QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getStyle() == )

   //  QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getTagName())

    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getWidth() == 10, "Wrong line width in line test");

    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getX() == 10, "Wrong line X in line test");

    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getY() == 20, "wrong line Y in line test");

    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->isBold(), "Wrong line bold in line test");
}

void Test_Parser::ReportStyleParseTest()
{
    qtreports::detail::Parser parser;
    QString input = QFINDTESTDATA( "style test.qreport" );

    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();

    QString error;

    QVERIFY2( !report.isNull(), "Null ptr report returned in style test" );

    QVERIFY2( !report->getStyle( "Arial_Normal" ).isNull(), "Null ptr band in style test" );

    QVERIFY2( report->getStyle( "Arial_Normal" )->getFontColor() == QColor("red"), "Wrong font color in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->getFontName() == "Arial", "Wrong font name in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->getFontSize() == 12, "Wrong font size in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->getPDFEncoding() == "Cp1251", "Wrong PDF encoding in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->getPDFFontName() == "c:\\tahoma.ttf", "Wrong PDF encoding in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->isBold(), "Wrong bold in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->isDefault(), "Wrong default in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->isItalic(), "Wrong italic in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->isPDFEmbedded(), "Wrong PDFEmbedded in style test");



}

void Test_Parser::OptionalFieldsTest()
{
    qtreports::detail::Parser parser;
    QString input = QFINDTESTDATA( "optional.qreport" );

    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();

    QVERIFY( !report.isNull());

    QCOMPARE( report->getWidth(), 595 );
    QCOMPARE( report->getHeight(), 842 );

    QVERIFY( !report->getStyle("Optional_style").isNull() );

    QCOMPARE( report->getStyle("Optional_style")->getFontSize(), 12);
    QCOMPARE( report->getStyle("Optional_style")->isDefault(), false);
    QCOMPARE( report->getStyle("Optional_style")->isBold(), false);
    QCOMPARE( report->getStyle("Optional_style")->isItalic(), false);

    QVERIFY( !report->getDetail().isNull() );
    QVERIFY( !report->getDetail()->getBand(0).isNull() );
    QVERIFY( !report->getDetail()->getBand(0)->getStaticText(0).isNull() );

    QCOMPARE( report->getDetail()->getBand(0)->getStaticText(0)->getAlignment() & Qt::AlignLeft, Qt::AlignLeft);
    QCOMPARE( report->getDetail()->getBand(0)->getStaticText(0)->getAlignment() & Qt::AlignVCenter, Qt::AlignVCenter);
}

void Test_Parser::FullTest() {
    qtreports::detail::Parser parser;
    QString input = QFINDTESTDATA( "full.qreport" );

    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();

    QVERIFY( !report.isNull());

    QCOMPARE( report->getWidth(), 600 );
    QCOMPARE( report->getHeight(), 500 );
    QCOMPARE( report->getOrientation(), QPrinter::Orientation::Landscape );
    QCOMPARE( report->getName(), QString("full_report") );

    QVERIFY( !report->getStyle("Arial_Normal").isNull() );

    QCOMPARE( report->getStyle("Arial_Normal")->isDefault(), true );
    QCOMPARE( report->getStyle("Arial_Normal")->getFontName(), QString("Arial"));
    QCOMPARE( report->getStyle("Arial_Normal")->getFontSize(), 12 );
    QCOMPARE( report->getStyle("Arial_Normal")->getPDFFontName(), QString("c:\\tahoma.ttf") );
    QCOMPARE( report->getStyle("Arial_Normal")->isPDFEmbedded(), false );
    QCOMPARE( report->getStyle("Arial_Normal")->isBold(), true );
    QCOMPARE( report->getStyle("Arial_Normal")->isItalic(), true );
    QCOMPARE( report->getStyle("Arial_Normal")->getFontColor(), QColor("red") );

    QCOMPARE( report->getQuery(), QString("\n     select idImg, nameImg, image from images; \n  ") );

    QVERIFY( !report->getField("idImg").isNull() );
    QVERIFY( !report->getField("nameImg").isNull() );
    QVERIFY( !report->getField("image").isNull() );

    QCOMPARE( report->getField("idImg")->getClassName(), QString("integer") );
    QCOMPARE( report->getField("nameImg")->getClassName(), QString("QString") );
    QCOMPARE( report->getField("image")->getClassName(), QString("QString") );

    QVERIFY( !report->getTitle().isNull() );

    QVERIFY( !report->getTitle()->getBand(0).isNull() );

    QCOMPARE( report->getTitle()->getBand(0)->getHeight(), 200 );

    QVERIFY( !report->getTitle()->getBand(0)->getStaticText(0).isNull() );

    QCOMPARE( report->getTitle()->getBand(0)->getStaticText(0)->getAlignment() & Qt::AlignRight, Qt::AlignRight);
    QCOMPARE( report->getTitle()->getBand(0)->getStaticText(0)->getAlignment() & Qt::AlignTop, Qt::AlignTop);
    QCOMPARE( report->getTitle()->getBand(0)->getStaticText(0)->getPos(), QPoint(0, 40) );
    QCOMPARE( report->getTitle()->getBand(0)->getStaticText(0)->getSize(), QSize(200, 20) );
    QCOMPARE( report->getTitle()->getBand(0)->getStaticText(0)->getOriginalText(), QString("TopRight Text") );

    QVERIFY( !report->getDetail().isNull() );

    QVERIFY( !report->getDetail()->getBand(0).isNull() );
    QVERIFY( !report->getDetail()->getBand(1).isNull() );
    QVERIFY( !report->getDetail()->getBand(2).isNull() );

    QVERIFY( !report->getDetail()->getBand(0)->getTextField(0).isNull() );

    QCOMPARE( report->getDetail()->getBand(0)->getTextField(0)->getSize(), QSize(100, 30) );
    QCOMPARE( report->getDetail()->getBand(0)->getTextField(0)->getPos(), QPoint(20, 20) );
    QCOMPARE( report->getDetail()->getBand(0)->getTextField(0)->getClassName(), QString("QString") );
    QCOMPARE( report->getDetail()->getBand(0)->getTextField(0)->getOriginalText(), QString("$P{param1}") );

    QCOMPARE( report->getTitle()->getBandsSize(), 1 );
    QCOMPARE( report->getDetail()->getBandsSize(), 3 );

    QVERIFY( !report->getDetail()->getBand(1).isNull() );

    QCOMPARE( report->getDetail()->getBand(1)->getHeight(), 230);
    QCOMPARE( report->getDetail()->getBand(1)->getTextFieldsSize(), 2 );
    QCOMPARE( report->getDetail()->getBand(1)->getTextField(0)->getOriginalText(), QString("$F{idImg}") );
    QCOMPARE( report->getDetail()->getBand(1)->getTextField(1)->getAlignment() & Qt::AlignLeft, Qt::AlignLeft);
    QCOMPARE( report->getDetail()->getBand(1)->getTextField(1)->getAlignment() & Qt::AlignBottom, Qt::AlignBottom);

    QVERIFY( !report->getDetail()->getBand(1)->getImage(0).isNull() );

    QCOMPARE( report->getDetail()->getBand(1)->getImage(0)->getSize(), QSize(425, 200) );
    QCOMPARE( report->getDetail()->getBand(1)->getImage(0)->getPos(), QPoint(102, 0) );
    QCOMPARE( report->getDetail()->getBand(1)->getImage(0)->getOriginalText(), QString("$F{image}"));

    QVERIFY( !report->getDetail()->getBand(2).isNull() );

    QVERIFY( !report->getDetail()->getBand(2)->getRect(0).isNull() );
    QVERIFY( !report->getDetail()->getBand(2)->getLine(0).isNull() );
    QVERIFY( !report->getDetail()->getBand(2)->getEllipse(0).isNull() );

    QCOMPARE( report->getDetail()->getBand(2)->getRect(0)->getPos(), QPoint(50, 0));
    QCOMPARE( report->getDetail()->getBand(2)->getRect(0)->getSize(), QSize(100, 100));

    QCOMPARE( report->getDetail()->getBand(2)->getLine(0)->getPos(), QPoint(100, 0));
    QCOMPARE( report->getDetail()->getBand(2)->getLine(0)->getSize(), QSize(1, 100));

    QCOMPARE( report->getDetail()->getBand(2)->getEllipse(0)->getPos(), QPoint(50, 0));
    QCOMPARE( report->getDetail()->getBand(2)->getEllipse(0)->getSize(), QSize(100, 100));
}

void    Test_Parser::parse() {
    ReportTreeParseTest();
    ReportTagParseTest();
    ReportStyleParseTest();
    ReportFieldParseTest();
    TextTest();

    OptionalFieldsTest();
}

void    Test_Parser::getReport() {
    qtreports::detail::Parser parser;
    QVERIFY( parser.getReport().isNull() );
}

void    Test_Parser::getLastError() {
    qtreports::detail::Parser parser;
    QVERIFY( parser.getLastError() == QString( "" ) );
}

void    Test_Parser::getLog() {
    qtreports::detail::Parser parser;
    QVERIFY( parser.getLog() == QString( "" ) );
}
