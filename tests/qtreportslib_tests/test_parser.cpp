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

    error = "Wrong text field in text test: '";
    error += report->getDetail()->getBand( 0 )->getTextField( 0 )->getText();
    error += "'";

    //QVERIFY2( report->getDetail()->getBand(0)->getTextField(0)->getText() == "$P{title}", error.toLatin1().data() );
}

void    Test_Parser::parse() {
    ReportTreeParseTest();
    ReportTagParseTest();
    TextTest();
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