#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include "parser.hpp"

namespace qtreports {
    namespace detail {

        ParseFunc    bindParseFunc( Parser * obj, ParseMethodPtr method ) {
            using namespace std::placeholders;
            auto func = std::bind( method, obj, _1, _2 );
            return func;
        }

        template < typename T1 >
        ParseFunc    toParseFunc( Parser * obj, bool( Parser::*method )( QXmlStreamReader &, const T1 & ) ) {
            //Cast second parameter to ObjectPtr type;
            auto parseMethodPtr = reinterpret_cast< ParseMethodPtr >( method );
            return bindParseFunc( obj, parseMethodPtr );
        }

        bool    toBool( const QString & string ) {
            return isEquals( string, "true" ) || isEquals( string, "1" );
        }

        Parser::Parser() : m_log( new QString() ) {
            m_functions[ "report" ] = toParseFunc( this, &Parser::parseReport );
            m_functions[ "style" ] = toParseFunc( this, &Parser::parseStyle );
            m_functions[ "queryString" ] = toParseFunc( this, &Parser::parseQueryString );
            m_functions[ "field" ] = toParseFunc( this, &Parser::parseField );
            m_functions[ "title" ] = toParseFunc( this, &Parser::parseTitle );
            m_functions[ "detail" ] = toParseFunc( this, &Parser::parseDetail );
            m_functions[ "band" ] = toParseFunc( this, &Parser::parseBand );
            m_functions[ "staticText" ] = toParseFunc( this, &Parser::parseStaticText );
            m_functions[ "textField" ] = toParseFunc( this, &Parser::parseTextField );
            m_functions[ "reportElement" ] = toParseFunc( this, &Parser::parseReportElement );
            m_functions[ "text" ] = toParseFunc( this, &Parser::parseText );
            m_functions[ "textFieldExpression" ] = toParseFunc( this, &Parser::parseTextFieldExpression );
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
            m_log << "getValue: start" << endl;
            while( !reader.atEnd() && !reader.isEndElement() ) {
                data += reader.text().toString();
                reader.readNext();
            }

            if( reader.hasError() ) {
                m_log << "getValue: error" << endl;
                m_lastError = reader.errorString();
                return false;
            }

            m_log << "getValue: end. data: " << data << endl;

            return true;
        }

        bool    Parser::getAttribute( QXmlStreamReader & reader, const QString & name, QString & data, AttributeOption option ) {
            m_log << "getAttribute: start. name: " << name << endl;
            auto && attributes = reader.attributes();
            if( !attributes.hasAttribute( name ) ) {
                m_log << "getAttribute: !hasAttribute" << endl;
                if( option != AttributeOption::Required ) {
                    return true;
                }
                m_log << "getAttribute: error" << endl;
                auto elementName = reader.name().toString();
                m_lastError =   "Element \"" + reader.name().toString() +
                                "\" not have attribute: " + name;
                return false;
            }
            data = attributes.value( name ).toString();
            m_log << "getAttribute: end. name: " << name << ", data: " << data << endl;
            return true;
        }

        bool    Parser::goToElementEnd( QXmlStreamReader & reader ) {
            m_log << "goToEnd: start" << endl;
            int level = 0;
            while( !reader.atEnd() ) {
                reader.readNext();
                if( reader.isEndElement() ) {
                    if( level <= 0 ) {
                        break;
                    }
                    --level;
                }
                if( reader.isStartElement() ) {
                    ++level;
                }
            }

            if( reader.hasError() ) {
                m_log << "goToEnd: error" << endl;
                m_lastError = reader.errorString();
                return false;
            }
            m_log << "goToEnd: end" << endl;

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
                else {
                    if( !goToElementEnd( reader ) ) {
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
            if( !getAttribute( reader, "pdfFontName", pdfFontName, AttributeOption::Optional ) ) {
                return false;
            }

            QString pdfEncoding;
            if( !getAttribute( reader, "pdfEncoding", pdfEncoding, AttributeOption::Optional ) ) {
                return false;
            }

            QString isPdfEmbedded;
            if( !getAttribute( reader, "isPdfEmbedded", isPdfEmbedded, AttributeOption::Optional ) ) {
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
            if( !parseChilds( reader, field ) ) {
                return false;
            }
            
            field->setTagName( "field" );
            field->setName( name );
            field->setClassName( className );
            report->setField( name, field );
            
            return !reader.hasError();
        }

        bool	Parser::parseTitle( QXmlStreamReader & reader, const ReportPtr & report ) {
            TitlePtr title( new Title() );
            if( !parseChilds( reader, title ) ) {
                return false;
            }
            
            title->setTagName( "title" );
            report->setTitle( title );

            return true;
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

        bool	Parser::parseBand( QXmlStreamReader & reader, const SectionPtr & section ) {
            QString height;
            if( !getAttribute( reader, "height", height ) ) {
                return false;
            }

            BandPtr band( new Band() );
            if( !parseChilds( reader, band ) ) {
                return false;
            }

            band->setTagName( "band" );
            band->setHeight( height.toInt() );
            section->addBand( band );

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

            QRect rect( x.toInt(), y.toInt(), width.toInt(), height.toInt() );
            widget->setRect( rect );

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

        const QString           Parser::getLog() const {
            return *m_log.string();
        }

    }
}
