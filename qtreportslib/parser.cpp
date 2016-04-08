#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include "parser.hpp"

namespace qtreports
{
    namespace detail
    {

        Parser::ParseFunc    bindParseFunc( Parser * obj, Parser::ParseMethodPtr method )
        {
            using namespace std::placeholders;
            auto func = std::bind( method, obj, _1, _2 );
            return func;
        }

        template < typename T1 >
        Parser::ParseFunc    toParseFunc( Parser * obj, bool( Parser::*method )( QXmlStreamReader &, const T1 & ) )
        {
            //Cast second parameter to ObjectPtr type;
            auto parseMethodPtr = reinterpret_cast< Parser::ParseMethodPtr >( method );
            return bindParseFunc( obj, parseMethodPtr );
        }

        bool    toBool( const QString & string )
        {
            return isEquals( string, "true" ) || isEquals( string, "1" );
        }

        Parser::Parser() : m_log( new QString() )
        {
            m_functions[ "report" ] = toParseFunc( this, &Parser::parseReport );
            m_functions[ "style" ] = toParseFunc( this, &Parser::parseStyle );
            m_functions[ "queryString" ] = toParseFunc( this, &Parser::parseQueryString );
            m_functions[ "field" ] = toParseFunc( this, &Parser::parseField );
            m_functions[ "title" ] = toParseFunc( this, &Parser::parseTitle );
            m_functions[ "detail" ] = toParseFunc( this, &Parser::parseDetail );
            m_functions[ "band" ] = toParseFunc( this, &Parser::parseBand );
            m_functions[ "staticText" ] = toParseFunc( this, &Parser::parseStaticText );
            m_functions[ "textField" ] = toParseFunc( this, &Parser::parseTextField );
            m_functions[ "line" ] = toParseFunc( this, &Parser::parseLine );
            m_functions[ "rect" ] = toParseFunc( this, &Parser::parseRect );
            m_functions[ "ellipse" ] = toParseFunc( this, &Parser::parseEllipse );
            m_functions[ "image" ] = toParseFunc( this, &Parser::parseImage );
            m_functions[ "imageExpression" ] = toParseFunc( this, &Parser::parseImageExpression );
            m_functions[ "reportElement" ] = toParseFunc( this, &Parser::parseReportElement );
            m_functions[ "textElement" ] = toParseFunc( this, &Parser::parseTextElement );
            m_functions[ "font" ] = toParseFunc( this, &Parser::parseFont );
            m_functions[ "text" ] = toParseFunc( this, &Parser::parseText );
            m_functions[ "textFieldExpression" ] = toParseFunc( this, &Parser::parseTextFieldExpression );
        }

        Parser::~Parser() {}

        bool	Parser::parse( const QString & path )
        {
            if( !QFile::exists( path ) )
            {
                m_lastError = "The file not exists";
                return false;
            }

            QFile file( path );
            file.open( QIODevice::OpenModeFlag::ReadOnly | QIODevice::Text );
            if( !file.isOpen() )
            {
                m_lastError = "The file can not be opened";
                return false;
            }

            return parseDocument( file.readAll() );//.replace( " ", "" )
        }

        bool    Parser::getValue( QXmlStreamReader & reader, QString & data )
        {
            m_log << "getValue():\tstart" << endl;
            while( !reader.atEnd() && !reader.isEndElement() )
            {
                data += reader.text().toString();
                reader.readNext();
            }

            if( reader.hasError() )
            {
                m_log << "getValue():\terror" << endl;
                m_lastError = reader.errorString();
                return false;
            }

            m_log << "getValue():\tend. data: " << data << endl;

            return true;
        }

        bool    Parser::getAttribute( QXmlStreamReader & reader, const QString & name, QString & data, AttributeOption option )
        {
            m_log << "getAttribute():\tstart. name: " << name << endl;
            auto && attributes = reader.attributes();
            if( !attributes.hasAttribute( name ) )
            {
                m_log << "getAttribute():\tnot have attribute: " + name << endl;
                if( option == AttributeOption::Optional )
                {
                    return true;
                }
                m_log << "getAttribute():\terror" << endl;
                auto elementName = reader.name().toString();
                m_lastError = "Element \"" + reader.name().toString() +
                    "\" not have attribute: " + name;
                return false;
            }
            data = attributes.value( name ).toString();
            m_log << "getAttribute():\tend. name: " << name << ",\t data: " << data << endl;
            return true;
        }

        bool    Parser::getRequiredAttribute( QXmlStreamReader & reader, const QString & name, QString & data )
        {
            return getAttribute( reader, name, data, AttributeOption::Required );
        }

        bool    Parser::getOptionalAttribute( QXmlStreamReader & reader, const QString & name, QString & data )
        {
            return getAttribute( reader, name, data, AttributeOption::Optional );
        }

        bool    Parser::goToElementEnd( QXmlStreamReader & reader )
        {
            m_log << "goToEnd():\tstart" << endl;
            int level = 0;
            while( !reader.atEnd() )
            {
                reader.readNext();
                if( reader.isEndElement() )
                {
                    if( level <= 0 )
                    {
                        break;
                    }
                    --level;
                }
                if( reader.isStartElement() )
                {
                    ++level;
                }
            }

            if( reader.hasError() )
            {
                m_log << "goToEnd():\terror" << endl;
                m_lastError = reader.errorString();
                return false;
            }
            m_log << "goToEnd():\tend" << endl;

            return true;
        }

        bool    Parser::parseChilds( QXmlStreamReader & reader, const ObjectPtr & object )
        {
            m_log << "parseChilds():\tstart" << endl;
            while( !reader.atEnd() )
            {
                reader.readNext();
                if( reader.isEndElement() )
                {
                    break;
                }
                if( !reader.isStartElement() )
                {
                    continue;
                }

                auto name = reader.name().toString();
                m_log << "parseChilds():\tcurrent tag: " << name << endl;
                if( m_functions.contains( name ) )
                {
                    m_log << "parseChilds():\tuse func for: " << name << endl;
                    auto func = m_functions[ name ];
                    if( !func( reader, object ) )
                    {
                        return false;
                    }
                }
                else
                {
                    m_log << "parseChilds():\tgoToElementEnd: " << name << endl;
                    if( !goToElementEnd( reader ) )
                    {
                        return false;
                    }
                }
            }

            if( reader.hasError() )
            {
                m_log << "parseChilds():\terror" << endl;
                m_lastError = reader.errorString();
                return false;
            }

            m_log << "parseChilds():\tend" << endl;
            return true;
        }

        bool    Parser::parseDocument( const QString & text )
        {
            QXmlStreamReader reader( text );

            m_report = ReportPtr( new Report() );
            if( !parseChilds( reader, m_report ) )
            {
                return false;
            }

            return !reader.hasError();
        }

        bool	Parser::parseReport( QXmlStreamReader & reader, const ReportPtr & report )
        {
            QString name;
            if( !getRequiredAttribute( reader, "name", name ) )
            {
                return false;
            }

            QString leftMargin;
            if( !getOptionalAttribute( reader, "leftMargin", leftMargin ) )
            {
                return false;
            }

            QString rightMargin;
            if( !getOptionalAttribute( reader, "rightMargin", rightMargin ) )
            {
                return false;
            }

            QString topMargin;
            if( !getOptionalAttribute( reader, "topMargin", topMargin ) )
            {
                return false;
            }

            QString bottomMargin;
            if( !getOptionalAttribute( reader, "bottomMargin", bottomMargin ) )
            {
                return false;
            }

            QString orientationString;
            if( !getOptionalAttribute( reader, "orientation", orientationString ) )
            {
                return false;
            }

            QString pageWidthString;
            if( !getOptionalAttribute( reader, "pageWidth", pageWidthString ) )
            {
                return false;
            }

            QString pageHeightString;
            if( !getOptionalAttribute( reader, "pageHeight", pageHeightString ) )
            {
                return false;
            }

            if( !parseChilds( reader, report ) )
            {
                return false;
            }

            report->setTagName( "report" );
            report->setName( name );

            if( !leftMargin.isEmpty() )
            {
                report->setLeftMargin( leftMargin.toInt() );
            }

            if( !topMargin.isEmpty() )
            {
                report->setTopMargin( topMargin.toInt() );
            }

            if( !rightMargin.isEmpty() )
            {
                report->setRightMargin( rightMargin.toInt() );
            }

            if( !bottomMargin.isEmpty() )
            {
                report->setBottomMargin( bottomMargin.toInt() );
            }

            if( !orientationString.isEmpty() )
            {
                auto orientation = isEquals( orientationString, "portrait" ) ?
                    QPrinter::Orientation::Portrait :
                    QPrinter::Orientation::Landscape;
                report->setOrientation( orientation );
            }

            if( !pageWidthString.isEmpty() )
            {
                report->setWidth( pageWidthString.toInt() );
            }

            if( !pageHeightString.isEmpty() )
            {
                report->setHeight( pageHeightString.toInt() );
            }

            return !reader.hasError();
        }


        bool    Parser::parseStyle( QXmlStreamReader & reader, const ReportPtr & report )
        {
            QString nameString;
            if( !getRequiredAttribute( reader, "name", nameString ) )
            {
                return false;
            }

            QString isDefaultString;
            if( !getOptionalAttribute( reader, "isDefault", isDefaultString ) )
            {
                return false;
            }

            QString fontNameString;
            if( !getOptionalAttribute( reader, "fontName", fontNameString ) )
            {
                return false;
            }

            QString fontSizeString;
            if( !getOptionalAttribute( reader, "fontSize", fontSizeString ) )
            {
                return false;
            }

            QString fontColorString;
            if( !getOptionalAttribute( reader, "fontColor", fontColorString ) )
            {
                return false;
            }

            QString isBoldString;
            if( !getOptionalAttribute( reader, "isBold", isBoldString ) )
            {
                return false;
            }

            QString isItalicString;
            if( !getOptionalAttribute( reader, "isItalic", isItalicString ) )
            {
                return false;
            }

            QString isUnderlineString;
            if( !getOptionalAttribute( reader, "isUnderline", isUnderlineString ) )
            {
                return false;
            }

            QString isStrikeThroughString;
            if( !getOptionalAttribute( reader, "isStrikeThrough", isStrikeThroughString ) )
            {
                return false;
            }

            QString pdfFontNameString;
            if( !getOptionalAttribute( reader, "pdfFontName", pdfFontNameString ) )
            {
                return false;
            }

            QString pdfEncodingString;
            if( !getOptionalAttribute( reader, "pdfEncoding", pdfEncodingString ) )
            {
                return false;
            }

            QString isPdfEmbeddedString;
            if( !getOptionalAttribute( reader, "isPdfEmbedded", isPdfEmbeddedString ) )
            {
                return false;
            }

            while( !reader.atEnd() && !reader.isEndElement() )
            {
                reader.readNext();
            }

            if( reader.hasError() )
            {
                m_lastError = reader.errorString();
                return false;
            }

            //isBold = "false" isItalic = "false" isUnderline = "false" isStrikeThrough = "false"

            StylePtr style( new Style() );
            style->setTagName( "style" );
            style->setName( nameString );

            if( !isDefaultString.isEmpty() )
            {
                bool isDefault = toBool( isDefaultString );
                style->setAsDefault( isDefault );
                if( isDefault )
                {
                    report->setDefaultStyle( style );
                }
            }

            if( !fontNameString.isEmpty() )
            {
                style->setFontName( fontNameString );
            }

            if( !fontColorString.isEmpty() )
            {
                style->setFontColor( QColor( fontColorString ) );
            }

            if( !fontSizeString.isEmpty() )
            {
                style->setFontSize( fontSizeString.toInt() );
            }

            if( !isBoldString.isEmpty() )
            {
                style->setBold( toBool( isBoldString ) );
            }

            if( !isItalicString.isEmpty() )
            {
                style->setItalic( toBool( isItalicString ) );
            }

            if( !isUnderlineString.isEmpty() )
            {
                style->setUnderline( toBool( isUnderlineString ) );
            }

            if( !isStrikeThroughString.isEmpty() )
            {
                style->setStrikeThrough( toBool( isStrikeThroughString ) );
            }

            if( !pdfFontNameString.isEmpty() )
            {
                style->setPDFFontName( pdfFontNameString );
            }

            if( !pdfEncodingString.isEmpty() )
            {
                style->setPDFEncoding( pdfEncodingString );
            }

            if( !isPdfEmbeddedString.isEmpty() )
            {
                style->setPDFEmbedded( toBool( isPdfEmbeddedString ) );
            }

            report->setStyle( nameString, style );

            return !reader.hasError();
        }

        bool    Parser::parseField( QXmlStreamReader & reader, const ReportPtr & report )
        {
            QString name;
            if( !getRequiredAttribute( reader, "name", name ) )
            {
                return false;
            }

            QString className;
            if( !getRequiredAttribute( reader, "class", className ) )
            {
                return false;
            }
            /*
            while( !reader.atEnd() && !reader.isEndElement() ) {
                reader.readNext();
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }
            */
            FieldPtr field( new Field() );
            if( !parseChilds( reader, field ) )
            {
                return false;
            }

            field->setTagName( "field" );
            field->setName( name );
            field->setClassName( className );
            report->setField( name, field );

            return !reader.hasError();
        }

        bool	Parser::parseTitle( QXmlStreamReader & reader, const ReportPtr & report )
        {
            TitlePtr title( new Title() );
            if( !parseChilds( reader, title ) )
            {
                return false;
            }

            title->setTagName( "title" );
            title->setWidth( report->getWidth() );
            report->setTitle( title );

            return !reader.hasError();
        }

        bool	Parser::parseDetail( QXmlStreamReader & reader, const ReportPtr & report )
        {
            DetailPtr detail( new Detail() );
            if( !parseChilds( reader, detail ) )
            {
                return false;
            }

            detail->setTagName( "detail" );
            detail->setWidth( report->getWidth() );
            report->setDetail( detail );

            return !reader.hasError();
        }

        bool	Parser::parseBand( QXmlStreamReader & reader, const SectionPtr & section )
        {
            QString height;
            if( !getRequiredAttribute( reader, "height", height ) )
            {
                return false;
            }

            BandPtr band( new Band() );
            if( !parseChilds( reader, band ) )
            {
                return false;
            }

            band->setTagName( "band" );
            band->setHeight( height.toInt() );
            band->setWidth( section->getWidth() );
            section->addBand( band );

            return !reader.hasError();
        }

        bool	Parser::parseStaticText( QXmlStreamReader & reader, const BandPtr & band )
        {
            StaticTextPtr staticText( new StaticText() );
            if( !parseChilds( reader, staticText ) )
            {
                return false;
            }

            staticText->setTagName( "staticText" );
            band->addStaticText( staticText );

            return !reader.hasError();
        }

        bool	Parser::parseTextField( QXmlStreamReader & reader, const BandPtr & band )
        {
            TextFieldPtr textField( new TextField() );
            if( !parseChilds( reader, textField ) )
            {
                return false;
            }

            textField->setTagName( "textField" );
            band->addTextField( textField );

            return !reader.hasError();
        }

        bool Parser::parseLine( QXmlStreamReader & reader, const BandPtr & band )
        {
            LinePtr line( new Line() );
            if( !parseChilds( reader, line ) )
            {
                return false;
            }

            line->setTagName( "line" );
            band->addLine( line );

            return !reader.hasError();
        }

        bool Parser::parseRect( QXmlStreamReader & reader, const BandPtr & band )
        {
            RectPtr rect( new Rect() );
            if( !parseChilds( reader, rect ) )
            {
                return false;
            }

            rect->setTagName( "rect" );
            band->addRect( rect );

            return !reader.hasError();
        }

        bool    Parser::parseEllipse( QXmlStreamReader & reader, const BandPtr & band )
        {
            EllipsePtr ellipse( new Ellipse() );
            if( !parseChilds( reader, ellipse ) )
            {
                return false;
            }

            ellipse->setTagName( "ellipse" );
            band->addEllipse( ellipse );

            return !reader.hasError();
        }

        bool    Parser::parseImage( QXmlStreamReader & reader, const BandPtr & band )
        {
            ImagePtr image( new Image() );
            if( !parseChilds( reader, image ) )
            {
                return false;
            }

            image->setTagName( "image" );
            band->addImage( image );

            return !reader.hasError();
        }

        bool	Parser::parseReportElement( QXmlStreamReader & reader, const WidgetPtr & widget )
        {
            QString xString;
            if( !getRequiredAttribute( reader, "x", xString ) )
            {
                return false;
            }

            QString yString;
            if( !getRequiredAttribute( reader, "y", yString ) )
            {
                return false;
            }

            QString widthString;
            if( !getRequiredAttribute( reader, "width", widthString ) )
            {
                return false;
            }

            QString heightString;
            if( !getRequiredAttribute( reader, "height", heightString ) )
            {
                return false;
            }

            QString styleString;
            if( !getOptionalAttribute( reader, "style", styleString ) )
            {
                return false;
            }

            if( !goToElementEnd( reader ) )
            {
                return false;
            }

            if( !xString.isEmpty() )
            {
                widget->setX( xString.toInt() );
            }

            if( !yString.isEmpty() )
            {
                widget->setY( yString.toInt() );
            }

            if( !widthString.isEmpty() )
            {
                auto width = widthString.toInt();
                //if( widthString.contains( "%" ) )
                //{
                    //auto percentString = widthString.split( "%" ).at( 0 );
                    //auto percent = 0.01 * std::max( 0, std::min( 100, percentString.toInt() ) );
                    //width = static_cast< int >( percent * m_report->getWidth() );
                //}
                widget->setWidth( width );
            }

            if( !heightString.isEmpty() )
            {
                widget->setHeight( heightString.toInt() );
            }
            
            if( !styleString.isEmpty() )
            {
                widget->setStyle( styleString );
            }

            //widget->setRect( QRect( x, y, width, height ) );

            return !reader.hasError();
        }

        bool	Parser::parseTextElement( QXmlStreamReader & reader, const WidgetPtr & widget )
        {
            QString textAlignment;
            if( !getRequiredAttribute( reader, "textAlignment", textAlignment ) )
            {
                return false;
            }

            QString textVAlignment;
            if( !getOptionalAttribute( reader, "textVAlignment", textVAlignment ) )
            {
                return false;
            }

            if( !parseChilds( reader, widget ) )
            {
                return false;
            }

            auto isCenter = isEquals( textAlignment, "Center" );
            auto isRight = isEquals( textAlignment, "Right" );

            auto isVTop = isEquals( textVAlignment, "Top" );
            auto isVBottom = isEquals( textVAlignment, "Bottom" );

            auto hFlag = isCenter ? Qt::AlignCenter : isRight ? Qt::AlignRight : Qt::AlignLeft;
            auto vFlag = isVTop ? Qt::AlignTop : isVBottom ? Qt::AlignBottom : Qt::AlignVCenter;

            widget->setAlignment( hFlag | vFlag );

            return !reader.hasError();
        }

        bool	Parser::parseFont( QXmlStreamReader & reader, const WidgetPtr & widget )
        {
            QString isBold;
            if( !getOptionalAttribute( reader, "isBold", isBold ) )
            {
                return false;
            }

            if( !goToElementEnd( reader ) )
            {
                return false;
            }

            if( !isBold.isEmpty() )
            {
                widget->setBold( toBool( isBold ) );
            }

            return !reader.hasError();
        }

        bool	Parser::parseText( QXmlStreamReader & reader, const StaticTextPtr & staticText )
        {
            QString text;
            if( !getValue( reader, text ) )
            {
                return false;
            }

            staticText->setOriginalText( text );

            return !reader.hasError();
        }

        bool	Parser::parseTextFieldExpression( QXmlStreamReader & reader, const TextFieldPtr & textField )
        {
            QString className;
            if( !getRequiredAttribute( reader, "class", className ) )
            {
                return false;
            }

            QString text;
            if( !getValue( reader, text ) )
            {
                return false;
            }

            textField->setOriginalText( text );
            textField->setClassName( className );

            return !reader.hasError();
        }

        bool    Parser::parseImageExpression( QXmlStreamReader & reader, const ImagePtr & image )
        {
            //QString className;
            //if( !getRequiredAttribute( reader, "class", className ) )
            //{
            //    return false;
            //}

            QString text;
            if( !getValue( reader, text ) )
            {
                return false;
            }

            image->setOriginalText( text );
            //image->setClassName( className );

            return !reader.hasError();
        }

        bool	Parser::parseQueryString( QXmlStreamReader & reader, const ReportPtr & report )
        {
            QString text;
            if( !getValue( reader, text ) )
            {
                return false;
            }

            report->setQuery( text );
            report->setTagName( "queryString" );

            return !reader.hasError();
        }

        const ReportPtr			Parser::getReport() const
        {
            return m_report;
        }

        const QString			Parser::getLastError() const
        {
            return m_lastError;
        }

        const QString           Parser::getLog() const
        {
            return *m_log.string();
        }

    }
}
