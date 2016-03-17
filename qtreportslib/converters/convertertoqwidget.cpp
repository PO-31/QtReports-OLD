//#include <QTextBrowser>
//#include "convertertohtml.hpp"
#include <QFrame>
#include <QLabel>
#include "convertertoqwidget.hpp"

namespace qtreports {
    namespace detail {

        ConverterToQWidget::ConverterToQWidget( const ReportPtr & report ) :
            m_report( report ) {}

        ConverterToQWidget::~ConverterToQWidget() {}

        bool    ConverterToQWidget::convert() {
            return createQWidget( m_report );
        }

        bool    ConverterToQWidget::convert( const ReportPtr & report ) {
            return createQWidget( report );
        }

        void    addVerticalBorder( QBoxLayout * parent, int height, int left, int right ) {
            auto layout = new QHBoxLayout();
            layout->setMargin( 0 );
            layout->setSpacing( 0 );

            auto leftFrame = new QFrame();
            leftFrame->setFixedWidth( left );
            leftFrame->setFixedHeight( height );
            leftFrame->setStyleSheet( "border: 1px solid gray; border-width: 0px 1px 0px 0px; " );

            auto centerFrame = new QFrame();
            centerFrame->setFixedHeight( height );
            centerFrame->setStyleSheet( "border: 1px solid gray; border-width: 0px 0px 0px 0px; " );

            auto rightFrame = new QFrame();
            rightFrame->setFixedWidth( right );
            rightFrame->setFixedHeight( height );
            rightFrame->setStyleSheet( "border: 1px solid gray; border-width: 0px 0px 0px 1px; " );

            layout->addWidget( leftFrame );
            layout->addWidget( centerFrame );
            layout->addWidget( rightFrame );

            parent->addLayout( layout );
        }

        void    addEmptySection( QBoxLayout * parent, int left, int right ) {
            auto layout = new QHBoxLayout();
            layout->setMargin( 0 );
            layout->setSpacing( 0 );

            auto leftFrame = new QFrame();
            leftFrame->setFixedWidth( left );
            leftFrame->setStyleSheet( "border: 1px solid gray; border-width: 1px 1px 1px 0px; " );

            auto centerFrame = new QFrame();
            centerFrame->setObjectName( "frame" );
            centerFrame->setStyleSheet( "#frame { border: 1px solid gray; border-width: 1px 0px 1px 0px; }" );

            auto rightFrame = new QFrame();
            rightFrame->setFixedWidth( right );
            rightFrame->setStyleSheet( "border: 1px solid gray; border-width: 1px 0px 1px 1px; " );

            layout->addWidget( leftFrame );
            layout->addWidget( centerFrame );
            layout->addWidget( rightFrame );

            parent->addLayout( layout );
        }

        QFrame *    addSectionLayout( QBoxLayout * parent, int height, int left, int right ) {
            auto layout = new QHBoxLayout();
            layout->setMargin( 0 );
            layout->setSpacing( 0 );

            auto leftFrame = new QFrame();
            leftFrame->setFixedHeight( height );
            leftFrame->setFixedWidth( left );
            leftFrame->setStyleSheet( "border: 1px solid gray; border-width: 1px 1px 0px 0px; " );

            auto centerFrame = new QFrame();
            centerFrame->setFixedHeight( height );
            centerFrame->setObjectName( "frame" );
            centerFrame->setStyleSheet( "#frame { border: 1px solid gray; border-width: 1px 0px 0px 0px; }" );

            auto rightFrame = new QFrame();
            rightFrame->setFixedHeight( height );
            rightFrame->setFixedWidth( right );
            rightFrame->setStyleSheet( "border: 1px solid gray; border-width: 1px 0px 0px 1px; " );

            layout->addWidget( leftFrame );
            layout->addWidget( centerFrame );
            layout->addWidget( rightFrame );

            parent->addLayout( layout );

            return centerFrame;
        }

        bool    ConverterToQWidget::createQWidget( const ReportPtr & report ) {
            if( report.isNull() ) {
                m_lastError = "Report is empty";
                return false;
            }

            auto detail = report->getDetail();
            if( detail.isNull() ) {
                m_lastError = "Report->Detail is empty";
                return false;
            }

            m_qwidget = QWidgetPtr( new QWidget() );

            auto layout = new QVBoxLayout( m_qwidget.data() );
            layout->setMargin( 0 );
            layout->setSpacing( 0 );
            addVerticalBorder( layout, report->getTopMargin(), report->getLeftMargin(), report->getRightMargin() );
            
            auto title = report->getTitle();
            if( !title.isNull() ) {
                auto sectionWidget = addSectionLayout( layout, title->getHeight(), report->getLeftMargin(), m_report->getRightMargin() );
                if( !createSection( sectionWidget, title ) ) {
                    return false;
                }
            }

            for( int i = 0; i < report->getRowCount(); ++i ) {
                auto sectionWidget = addSectionLayout( layout, detail->getHeight(), report->getLeftMargin(), m_report->getRightMargin() );
                if( !createSection( sectionWidget, detail ) ) {
                    return false;;
                }
            }
            
            addEmptySection( layout, report->getLeftMargin(), report->getRightMargin() );
            addVerticalBorder( layout, report->getBottomMargin(), report->getLeftMargin(), report->getRightMargin() );

            return true;
        }


        bool    ConverterToQWidget::createSection( QWidget * parent, const SectionPtr & section ) {
            auto label = new QLabel( parent );
            label->setText( section->getTagName() );
            label->setAttribute( Qt::WA_TranslucentBackground );
            label->setStyleSheet( "font-size: 26px; color: gray" );
            label->setAlignment( Qt::AlignCenter );
            label->resize( parent->size() );

            if( !createBands( parent, section ) ) {
                return false;;
            }

            return true;
        }

        bool    ConverterToQWidget::createBands( QWidget * parent, const SectionPtr & section ) {
            for( auto && band : section->getBands() ) {
                auto frame = new QFrame( parent );
                for( auto && staticText : band->getStaticTexts() ) {
                    auto label = new QLabel( frame );
                    QString style = "";
                    if( staticText->isBold() ) {
                        style += "font-weight: bold; ";
                    }
                    style += "border: 1px solid gray; ";
                    label->setStyleSheet( style );
                    label->setGeometry( staticText->getRect() );
                    label->setAlignment( staticText->getAlignment() );
                    label->setText( staticText->getText() );
                }
                for( auto && textField : band->getTextFields() ) {
                    auto label = new QLabel( frame );
                    QString style = "";
                    if( textField->isBold() ) {
                        style += "font-weight: bold; ";
                    }
                    style += "border: 1px solid gray; ";
                    label->setStyleSheet( style );
                    label->setGeometry( textField->getRect() );
                    label->setAlignment( textField->getAlignment() );
                    label->setText( textField->getText() );
                }
            }

            return true;
        }

        const QString       ConverterToQWidget::getLastError() const {
            return m_lastError;
        }

        const QWidgetPtr    ConverterToQWidget::getQWidget() const {
            return m_qwidget;
        }

    }
}
