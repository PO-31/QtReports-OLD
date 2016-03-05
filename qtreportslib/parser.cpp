#include <QFile>
#include <QMessageBox>
#include "parser.hpp"

namespace qtreports {
    namespace detail {

        Parser::Parser() :
            m_report( new Report() ) {}

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

            return parseReport( file.readAll() );//.replace( " ", "" )
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

        bool	Parser::parseReport( const QString & text ) {
            QXmlStreamReader reader( text );
            
            //QString message;
            while( !reader.atEnd() ) {
                reader.readNext();
                if( !reader.isStartElement() ) {
                    continue;
                }

                auto name = reader.name().toString();
                //message += name + "\n";
                if( name == "style" ) {
                    if( !parseStyle( reader, m_report ) ) {
                        return false;
                    }
                }
                else if( name == "field" ) {
                    if( !parseField( reader, m_report ) ) {
                        return false;
                    }
                }
                else if( name == "detail" ) {
                    if( !parseDetail( reader, m_report ) ) {
                        return false;
                    }
                }
            }
            //QMessageBox::warning( 0, "", message );

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

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

            StylePtr field( new Style() );
            report->setStyle( name, field );

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

            FieldPtr field( new Field() );
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
                if( name == "band" ) {
                    if( !parseBand( reader, detail ) ) {
                        return false;
                    }
                }
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

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
                if( name == "staticText" ) {
                    if( !parseStaticText( reader, band ) ) {
                        return false;
                    }
                }
                else if( name == "textField" ) {
                    if( !parseTextField( reader, band ) ) {
                        return false;
                    }
                }
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

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
                if( name == "reportElement" ) {
                    if( !parseReportElement( reader, staticText ) ) {
                        return false;
                    }
                }
                else if( name == "text" ) {
                    if( !parseText( reader, staticText ) ) {
                        return false;
                    }
                }
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

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
                if( name == "reportElement" ) {
                    if( !parseReportElement( reader, textField ) ) {
                        return false;
                    }
                }
                else if( name == "textFieldExpression" ) {
                    if( !parseTextFieldExpression( reader, textField ) ) {
                        return false;
                    }
                }
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                return false;
            }

            band->addTextField( textField );

            return true;
        }

        bool	Parser::parseReportElement( QXmlStreamReader & reader, const WidgetPtr & staticText ) {
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

            QPoint pos( x.toInt(), y.toInt() );
            QSize size( width.toInt(), height.toInt() );
            staticText->setPosition( pos );
            staticText->setSize( size );

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
            QString text;
            if( !getValue( reader, text ) ) {
                return false;
            }

            textField->setText( text );

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
