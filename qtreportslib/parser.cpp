#include <QFile>
#include <QMessageBox>
#include "parser.hpp"

namespace qtreports {
    namespace detail {

        Parser::Parser() {
            //m_functions[ "band" ] = &Parser::parseBand;
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

        bool    Parser::getAttribute( QXmlStreamReader & reader, const QString & name, QString & data ) {
            auto && attributes = reader.attributes();
            if( !attributes.hasAttribute( name ) ) {
                auto elementName = reader.name().toString();
                m_lastError =   "Element \"" + reader.name().toString() +
                                "\" not have attribute: " + name;
                return false;
            }
            data = attributes.value( name ).toString();

            return true;
        }

        bool    Parser::parseDocument( const QString & text ) {
            QXmlStreamReader reader( text );
            while( !reader.atEnd() ) {
                reader.readNext();
                if( reader.isEndElement() ) {
                    break;
                }
                if( !reader.isStartElement() ) {
                    continue;
                }

                auto name = reader.name().toString();
                if( isEquals( name, "report" ) ) {
                    if( !parseReport( reader ) ) {
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

        bool	Parser::parseReport( QXmlStreamReader & reader ) {
            QString name;
            if( !getAttribute( reader, "name", name ) ) {
                return false;
            }

            ReportPtr report( new Report() );
            while( !reader.atEnd() ) {
                reader.readNext();
                if( reader.isEndElement() ) {
                    break;
                }
                if( !reader.isStartElement() ) {
                    continue;
                }

                auto name = reader.name().toString();
                if( isEquals( name, "style" ) ) {
                    if( !parseStyle( reader, report ) ) {
                        return false;
                    }
                }
                else if( isEquals( name, "queryString" ) ) {
                    if( !parseQueryString( reader, report ) ) {
                        return false;
                    }
                }
                else if( isEquals( name, "field" ) ) {
                    if( !parseField( reader, report ) ) {
                        return false;
                    }
                }
                else if( isEquals( name, "detail" ) ) {
                    if( !parseDetail( reader, report ) ) {
                        return false;
                    }
                }
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

            report->setTagName( "report" );
            report->setName( name );
            m_report = report;

            return true;
        }

        bool    toBool( const QString & string ) {
            return isEquals( string, "true" ) || isEquals( string, "1" );
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
            while( !reader.atEnd() ) {
                reader.readNext();
                if( reader.isEndElement() ) {
                    break;
                }
                if( !reader.isStartElement() ) {
                    continue;
                }

                auto name = reader.name().toString();
                if( isEquals( name, "band" ) ) {
                    if( !parseBand( reader, detail ) ) {
                        return false;
                    }
                }
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
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
            while( !reader.atEnd() ) {
                reader.readNext();
                if( reader.isEndElement() ) {
                    break;
                }
                if( !reader.isStartElement() ) {
                    continue;
                }

                auto name = reader.name().toString();
                //QMessageBox::warning( 0, "", name );
                if( isEquals( name, "staticText" ) ) {
                    if( !parseStaticText( reader, band ) ) {
                        return false;
                    }
                }
                else if( isEquals( name, "textField" ) ) {
                    if( !parseTextField( reader, band ) ) {
                        return false;
                    }
                }
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

            band->setTagName( "band" );
            band->setSize( QSize( 0, height.toInt() ) );
            detail->addBand( band );

            return true;
        }

        bool	Parser::parseStaticText( QXmlStreamReader & reader, const BandPtr & band ) {
            StaticTextPtr staticText( new StaticText() );
            while( !reader.atEnd() ) {
                reader.readNext();
                if( reader.isEndElement() ) {
                    break;
                }
                if( !reader.isStartElement() ) {
                    continue;
                }

                auto name = reader.name().toString();
                if( isEquals( name, "reportElement" ) ) {
                    if( !parseReportElement( reader, staticText ) ) {
                        return false;
                    }
                }
                else if( isEquals( name, "text" ) ) {
                    if( !parseText( reader, staticText ) ) {
                        return false;
                    }
                }
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

            staticText->setTagName( "staticText" );
            band->addStaticText( staticText );

            return true;
        }

        bool	Parser::parseTextField( QXmlStreamReader & reader, const BandPtr & band ) {
            TextFieldPtr textField( new TextField() );
            while( !reader.atEnd() ) {
                reader.readNext();
                if( reader.isEndElement() ) {
                    break;
                }
                if( !reader.isStartElement() ) {
                    continue;
                }

                auto name = reader.name().toString();
                if( isEquals( name, "reportElement" ) ) {
                    if( !parseReportElement( reader, textField ) ) {
                        return false;
                    }
                }
                else if( isEquals( name, "textFieldExpression" ) ) {
                    if( !parseTextFieldExpression( reader, textField ) ) {
                        return false;
                    }
                }
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
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
