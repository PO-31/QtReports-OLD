#include <QTest>
#include <QRegularExpression>
#include <engine.hpp>
#include "test_engine.hpp"

Test_Engine::Test_Engine( QObject * parent ) :
    QObject( parent ) {}

Test_Engine::~Test_Engine() {}

void    Test_Engine::compile() {
    qtreports::Engine engine;
    QString input = QFINDTESTDATA( "simple.qreport" );
    QVERIFY2( engine.open( input ), engine.getLastError().toStdString().c_str() );

    QString input_scheme = QFINDTESTDATA( "default.txt" );
    QFile scheme_file( input_scheme );

    QVERIFY2( scheme_file.open( QIODevice::ReadOnly | QIODevice::Text ), "Can't open default.txt file." );

    qtreports::detail::Parser parser;
    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );
    qtreports::detail::ReportPtr report = parser.getReport();

    QVector< QString > classes;
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

    if( curr_line.compare( "Styles" ) == 0 ) {
        int styles_num = report->getStyles().size();

        QVector<QString> styles;
        QVERIFY2( curr_line.compare( "Styles", Qt::CaseInsensitive ) == 0, "No 'Style' line in default.txt" );

        for( int i = 0; i < styles_num; ++i ) {
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

        for( int i = 0; i < styles.size(); ++i ) {
            error = "Style '" + styles.at( i ) + "' not parsed";
            QVERIFY2( !report->getStyle( styles.at( i ) ).isNull(), error.toLatin1().data() );
        }

        line = scheme_file.readLine();
        curr_line = line.data();
        curr_line.remove( curr_line.size() - 1, 1 );
    }

    /* Detail */
    if( curr_line.compare( "Detail" ) == 0 ) {
        QVERIFY2( !report->getDetail().isNull(), "Detail block not parsed" );
        int bands_num = 0;
        while( !scheme_file.atEnd() ) {
            line = scheme_file.readLine();
            curr_line = line.data();
            curr_line.remove( curr_line.size() - 1, 1 );
            if( curr_line.compare( "/Detail" ) == 0 ) {
                QVERIFY2( bands_num == report->getDetail()->getBandsSize(), "To many bands parsed" );
                break;
            }

            if( curr_line.compare( "Band" ) == 0 ) {
                QVERIFY2( bands_num < report->getDetail()->getBandsSize(), "To few bands parsed" );

                int static_text_num = 0, text_field_num = 0;
                while( !scheme_file.atEnd() ) {
                    line = scheme_file.readLine();
                    curr_line = line.data();
                    curr_line.remove( curr_line.size() - 1, 1 );
                    if( curr_line.compare( "/Band" ) == 0 ) {
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

                    if( curr_line.compare( "StaticText" ) == 0 ) {
                        error = "To few static text objects parsed in band number " + QString::number( bands_num ) +
                            " " + report->getDetail()->getBand( bands_num )->getName();
                        QVERIFY2( static_text_num < report->getDetail()->getBand( bands_num )->getStaticTextsSize(),
                            error.toLatin1().data() );

                        ++static_text_num;
                    }

                    if( curr_line.compare( "TextField" ) == 0 ) {
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
        
        /* <detail> */
        QWARN( "Test <detail>" );
        auto detail = report->getDetail();
        QTRY_VERIFY( !detail.isNull() );
        QTRY_COMPARE( detail->getName(), QString( "" ) );
        QTRY_COMPARE( detail->getTagName(), QString( "detail" ) );
        QTRY_COMPARE( detail->getLastError(), QString( "" ) );
        QTRY_VERIFY( detail->getBandsSize() == 1 );
        auto bands = detail->getBands();
        QTRY_VERIFY( bands.size() == 1 );
        QTRY_COMPARE( detail->getBand( 0 ), bands.at( 0 ) );
        
        /* <band height = "400"> */
        QWARN( "Test <band>" );
        auto band = bands.at( 0 );
        QTRY_VERIFY( !band.isNull() );
        QTRY_COMPARE( band->getName(), QString( "" ) );
        QTRY_COMPARE( band->getTagName(), QString( "band" ) );
        QTRY_COMPARE( band->getLastError(), QString( "" ) );
        QTRY_COMPARE( band->getX(), 0 );
        QTRY_COMPARE( band->getY(), 0 );
        QTRY_COMPARE( band->getWidth(), 0 );
        QTRY_COMPARE( band->getHeight(), 400 );
        QTRY_COMPARE( band->getPos(), QPoint() );
        QTRY_VERIFY( band->getPos().isNull() );
        QTRY_COMPARE( band->getSize(), QSize( 0, 400 ) );
        QTRY_VERIFY( band->getStyle().isNull() );
        QTRY_VERIFY( band->getStaticTextsSize() == 1 );
        auto staticTexts = band->getStaticTexts();
        QTRY_VERIFY( staticTexts.size() == 1 );
        QTRY_COMPARE( band->getStaticText( 0 ), staticTexts.at( 0 ) );
        QTRY_VERIFY( band->getTextFieldsSize() == 4 );
        auto textFields = band->getTextFields();
        QTRY_VERIFY( textFields.size() == 4 );
        QTRY_COMPARE( band->getTextField( 0 ), textFields.at( 0 ) );

        /*  
          <staticText>
          <reportElement x = "380" y = "0" width = "200" height = "20"/>
          <text><![CDATA[Тест !!]]></text>
          </staticText>
        */
        QWARN( "Test <staticText>" );
        auto staticText = staticTexts.at( 0 );
        QTRY_VERIFY( !staticText.isNull() );
        QTRY_COMPARE( staticText->getName(), QString( "" ) );
        QTRY_COMPARE( staticText->getTagName(), QString( "staticText" ) );
        QTRY_COMPARE( staticText->getLastError(), QString( "" ) );
        QTRY_COMPARE( staticText->getX(), 380 );
        QTRY_COMPARE( staticText->getY(), 0 );
        QTRY_COMPARE( staticText->getWidth(), 200 );
        QTRY_COMPARE( staticText->getHeight(), 20 );
        QTRY_COMPARE( staticText->getPos(), QPoint( 380, 0 ) );
        QTRY_COMPARE( staticText->getSize(), QSize( 200, 20 ) );
        QTRY_VERIFY( staticText->getStyle().isNull() );
        // QWARN( staticText->getText().toStdString().c_str() );
        // Use u8 literal for utf-8 texts
        QTRY_COMPARE( staticText->getText(), QString( u8"Тест !!" ) );
    }
}