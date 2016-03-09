#include <QFile>
#include <QMessageBox>
#include "parser.hpp"

namespace qtreports {
    namespace detail {

        auto    bindParseFunc( ParseMethodPtr method, Parser * obj ) {
            using namespace std::placeholders;
            auto func = std::bind( method, obj, _1, _2 );
            return func;
        }

        template < typename T1 >
        auto    toParseFunc( bool( Parser::*method )( QXmlStreamReader &, const T1 & ), Parser * obj ) {
            //Cast second parameter to ObjectPtr type;
            auto parseMethodPtr = reinterpret_cast< ParseMethodPtr >( method );
            return bindParseFunc( parseMethodPtr, obj );
        }

        bool    toBool( const QString & string ) {
            return isEquals( string, "true" ) || isEquals( string, "1" );
        }

        Parser::Parser() {
            m_functions[ "report" ] = toParseFunc( &Parser::parseReport, this );
            m_functions[ "style" ] = toParseFunc( &Parser::parseStyle, this );
            m_functions[ "queryString" ] = toParseFunc( &Parser::parseQueryString, this );
            m_functions[ "field" ] = toParseFunc( &Parser::parseField, this );
            m_functions[ "detail" ] = toParseFunc( &Parser::parseDetail, this );
            m_functions[ "band" ] = toParseFunc( &Parser::parseBand, this );
            m_functions[ "staticText" ] = toParseFunc( &Parser::parseStaticText, this );
            m_functions[ "textField" ] = toParseFunc( &Parser::parseTextField, this );
            m_functions[ "reportElement" ] = toParseFunc( &Parser::parseReportElement, this );
            m_functions[ "text" ] = toParseFunc( &Parser::parseText, this );
            m_functions[ "textFieldExpression" ] = toParseFunc( &Parser::parseTextFieldExpression, this );
        }

        Parser::~Parser() {}

        bool	Parser::parse( const QString & path ) {
            if( !QFile::exists( path ) ) {
                m_lastError = "The file not exists";
                return false;
            }

            QFile file( path );
            file.open( QIODevice::OpenModeFlag::ReadOnly | QIODevice::Text );
            if( !file.isOpen() ) {
                m_lastError = "The file can not be opened";
                return false;
            }

            return parseDocument( file.readAll() );//.replace( " ", "" )
        }

        bool    Parser::getValue( QXmlStreamReader & reader, QString & data ) {
            while( !reader.atEnd() && !reader.isEndElement() ) {
                data += reader.text().toString();
                reader.readNext();
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

            return true;
        }

        bool    Parser::getAttribute( QXmlStreamReader & reader, const QString & name, QString & data, AttributeOption option ) {
            auto && attributes = reader.attributes();
            if( !attributes.hasAttribute( name ) ) {
                if( option != AttributeOption::Required ) {
                    return true;
                }
                auto elementName = reader.name().toString();
                m_lastError =   "Element \"" + reader.name().toString() +
                                "\" not have attribute: " + name;
                return false;
            }
            data = attributes.value( name ).toString();

            return true;
        }

        bool    Parser::parseChilds( QXmlStreamReader & reader, const ObjectPtr & object ) {
            while( !reader.atEnd() ) {
                reader.readNext();
                if( reader.isEndElement() ) {
                    break;
                }
                if( !reader.isStartElement() ) {
                    continue;
                }

                auto name = reader.name().toString();
                if( m_functions.contains( name ) ) {
                    auto func = m_functions[ name ];
                    if( !func( reader, object ) ) {
                        return false;
                    }
                }
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

            return true;
        }

        bool    Parser::parseDocument( const QString & text ) {
            QXmlStreamReader reader( text );
            
            ReportPtr report( new Report() );
            if( !parseChilds( reader, report ) ) {
                return false;
            }

            m_report = report;

            return true;
        }

        bool	Parser::parseReport( QXmlStreamReader & reader, const ReportPtr & report ) {
            QString name;
            if( !getAttribute( reader, "name", name ) ) {
                return false;
            }

            if( !parseChilds( reader, report ) ) {
                return false;
            }

            report->setTagName( "report" );
            report->setName( name );

            return true;
        }


        bool    Parser::parseStyle( QXmlStreamReader & reader, const ReportPtr & report ) {
            QString name;
            if( !getAttribute( reader, "name", name ) ) {
                return false;
            }

            QString isDefault;
            if( !getAttribute( reader, "isDefault", isDefault ) ) {
                return false;
            }

            QString fontName;
            if( !getAttribute( reader, "fontName", fontName ) ) {
                return false;
            }

            QString fontSize;
            if( !getAttribute( reader, "fontSize", fontSize ) ) {
                return false;
            }

            QString pdfFontName;
            if( !getAttribute( reader, "pdfFontName", pdfFontName ) ) {
                return false;
            }

            QString pdfEncoding;
            if( !getAttribute( reader, "pdfEncoding", pdfEncoding ) ) {
                return false;
            }

            QString isPdfEmbedded;
            if( !getAttribute( reader, "isPdfEmbedded", isPdfEmbedded ) ) {
                return false;
            }

            while( !reader.atEnd() && !reader.isEndElement() ) {
                reader.readNext();
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

            bool isDefaultBool = toBool( isDefault );
            StylePtr style( new Style() );
            style->setTagName( "style" );
            style->setName( name );
            style->setAsDefault( isDefaultBool );
            style->setFontName( fontName );
            style->setFontSize( fontSize.toInt() );
            style->setPDFFontName( pdfFontName );
            style->setPDFEncoding( pdfEncoding );
            style->setPDFEmbedded( toBool( isPdfEmbedded ) );
            report->setStyle( name, style );
            if( isDefaultBool ) {
                report->setDefaultStyle( style );
            }

            return !reader.hasError();
        }

        bool    Parser::parseField( QXmlStreamReader & reader, const ReportPtr & report ) {
            QString name;
            if( !getAttribute( reader, "name", name ) ) {
                return false;
            }

            QString className;
            if( !getAttribute( reader, "class", className ) ) {
                return false;
            }

            while( !reader.atEnd() && !reader.isEndElement() ) {
                reader.readNext();
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

            FieldPtr field( new Field() );
            field->setTagName( "field" );
            field->setName( name );
            field->setClassName( className );
            report->setField( name, field );
            
            return !reader.hasError();
        }

        bool	Parser::parseDetail( QXmlStreamReader & reader, const ReportPtr & report ) {
            DetailPtr detail( new Detail() );
            if( !parseChilds( reader, detail ) ) {
                return false;
            }

            detail->setTagName( "detail" );
            report->setDetail( detail );

            return true;
        }

        bool	Parser::parseBand( QXmlStreamReader & reader, const DetailPtr & detail ) {
            QString height;
            if( !getAttribute( reader, "height", height ) ) {
                return false;
            }

            BandPtr band( new Band() );
            if( !parseChilds( reader, band ) ) {
                return false;
            }

            band->setTagName( "band" );
            band->setSize( QSize( 0, height.toInt() ) );
            detail->addBand( band );

            return true;
        }

        bool	Parser::parseStaticText( QXmlStreamReader & reader, const BandPtr & band ) {
            StaticTextPtr staticText( new StaticText() );
            if( !parseChilds( reader, staticText ) ) {
                return false;
            }

            staticText->setTagName( "staticText" );
            band->addStaticText( staticText );

            return true;
        }

        bool	Parser::parseTextField( QXmlStreamReader & reader, const BandPtr & band ) {
            TextFieldPtr textField( new TextField() );
            if( !parseChilds( reader, textField ) ) {
                return false;
            }

            textField->setTagName( "textField" );
            band->addTextField( textField );

            return true;
        }

        bool	Parser::parseReportElement( QXmlStreamReader & reader, const WidgetPtr & widget ) {
            QString x;
            if( !getAttribute( reader, "x", x ) ) {
                return false;
            }

            QString y;
            if( !getAttribute( reader, "y", y ) ) {
                return false;
            }

            QString width;
            if( !getAttribute( reader, "width", width ) ) {
                return false;
            }

            QString height;
            if( !getAttribute( reader, "height", height ) ) {
                return false;
            }

            while( !reader.atEnd() && !reader.isEndElement() ) {
                reader.readNext();
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

            QPoint pos( x.toInt(), y.toInt() );
            QSize size( width.toInt(), height.toInt() );
            widget->setPosition( pos );
            widget->setSize( size );

            return !reader.hasError();
        }

        bool	Parser::parseText( QXmlStreamReader & reader, const StaticTextPtr & staticText ) {
            QString text;
            if( !getValue( reader, text ) ) {
                return false;
            }

            staticText->setText( text );

            return !reader.hasError();
        }

        bool	Parser::parseTextFieldExpression( QXmlStreamReader & reader, const TextFieldPtr & textField ) {
            QString className;
            if( !getAttribute( reader, "class", className ) ) {
                return false;
            }
            
            QString text;
            if( !getValue( reader, text ) ) {
                return false;
            }

            textField->setText( text );
            textField->setClassName( className );

            return !reader.hasError();
        }

        bool	Parser::parseQueryString( QXmlStreamReader & reader, const ReportPtr & report ) {
            QString text;
            if( !getValue( reader, text ) ) {
                return false;
            }

            report->setQuery( text );
            report->setTagName( "queryString" );

            return !reader.hasError();
        }

        const ReportPtr			Parser::getReport() const {
            return m_report;
        }

        const QString			Parser::getLastError() const {
            return m_lastError;
        }

    }
}
