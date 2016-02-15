#include <QFile>
#include <QXmlStreamReader>
#include <QLabel>
#include <QTextBrowser>
#include <QVBoxLayout>
#include "translator.hpp"

namespace qtreports {
	namespace detail {

		Translator::Translator() {}

		Translator::~Translator() {}

		bool	Translator::parse( const QString & path ) {
			if( !QFile::exists( path ) ) {
				m_lastError = "The file not exists";
				return false;
			}

			QFile file( path );
			file.open( QIODevice::OpenModeFlag::ReadOnly | QIODevice::Text );
			if ( !file.isOpen() ) {
				m_lastError = "The file can not be opened";
				return false;
			}

			QByteArray text = file.readAll();

			/*
			QXmlStreamReader reader ( file.readAll() );

			while( !reader.atEnd() ) {
				auto token = reader.readNext();
				if( token == QXmlStreamReader::StartElement ) {
					// or switch/case
					if( reader.name() == "element1" ) {
						reader.readNext();
						//reader.text().toString();
					}
					else if( reader.name() == "element2" ) {
						reader.readNext();
						//reader.text().toString();
					}
				}
				reader.readNext();
			}
			*/
			
			m_widget = QWidgetPtr( new QWidget() );
			m_widget->resize( 600, 400 );

			QTextBrowser * browser = new QTextBrowser();
			browser->setHtml( text );

			QVBoxLayout * layout = new QVBoxLayout( m_widget.data() );
			layout->setMargin( 0 );
			layout->addWidget( browser );
			
			//QLabel * label = new QLabel( m_widget.data() );
			//label->setText( "Hello, world!" );
			//label->resize( 400, 300 );
			//label->setAlignment( Qt::AlignmentFlag::AlignCenter );
			
			return true;
		}

		const QString	Translator::getLastError() const {
			return m_lastError;
		}

		const QWidgetPtr	Translator::getWidget() const {
			return m_widget;
		}

	}
}