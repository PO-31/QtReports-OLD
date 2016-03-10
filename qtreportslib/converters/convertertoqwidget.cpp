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
            return createQWidget();
        }

        QHBoxLayout *   ConverterToQWidget::createVerticalBorder( int height, int left, int right ) {
            auto layout = new QHBoxLayout();
            layout->setMargin( 0 );
            layout->setSpacing( 0 );

            auto leftFrame = new QFrame();
            leftFrame->setFixedWidth( left );
            leftFrame->setFixedHeight( height );
            leftFrame->setStyleSheet( "border: 1px solid black; border-width: 0px 1px 0px 0px; " );

            auto emptyFrame = new QFrame();
            emptyFrame->setFixedHeight( height );
            //emptyFrame->setStyleSheet( "border: 1px solid black; border-width: 0px 1px; " );

            auto rightFrame = new QFrame();
            rightFrame->setFixedWidth( right );
            rightFrame->setFixedHeight( height );
            rightFrame->setStyleSheet( "border: 1px solid black; border-width: 0px 0px 0px 1px; " );

            layout->addWidget( leftFrame );
            layout->addWidget( emptyFrame );
            layout->addWidget( rightFrame );

            return layout;
        }

        bool    ConverterToQWidget::createQWidget() {
            if( m_report.isNull() ) {
                m_lastError = "Report is empty";
                return false;
            }

            auto detail = m_report->getDetail();
            if( detail.isNull() ) {
                m_lastError = "Report->Detail is empty";
                return false;
            }

            m_qwidget = QWidgetPtr( new QWidget() );

            auto vLayout = new QVBoxLayout( m_qwidget.data() );
            vLayout->setMargin( 0 );
            vLayout->setSpacing( 0 );

            auto hLayout = new QHBoxLayout();
            hLayout->setMargin( 0 );
            hLayout->setSpacing( 0 );

            auto centerFrame = new QFrame();
            centerFrame->setObjectName( "centerFrame" );
            centerFrame->setStyleSheet( "#centerFrame { border: 1px solid gray; border-width: 1px 0px 0px 0px }" );
            auto center = new QVBoxLayout( centerFrame );
            center->setMargin( 0 );
            center->setSpacing( 0 );

            auto topVLayout = createVerticalBorder( 30, 30, 30 );
            auto bottomVLayout = createVerticalBorder( 30, 30, 30 );

            vLayout->addLayout( topVLayout );
            vLayout->addWidget( centerFrame );
            vLayout->addLayout( bottomVLayout );

            auto title = m_report->getTitle();
            if( !title.isNull() && !createSection( center, title ) ) {
                return false;
            }

            if( !createSection( center, detail ) ) {
                return false;;
            }

            auto empty = new QFrame();
            center->addWidget( empty );

            auto layout = new QHBoxLayout( empty );
            layout->setMargin( 0 );
            layout->setSpacing( 0 );

            auto left = new QFrame();
            left->setFixedWidth( 30 );
            left->setStyleSheet( "border: 1px solid gray; border-width: 0px 1px 1px 0px; " );

            auto right = new QFrame();
            right->setFixedWidth( 30 );
            right->setStyleSheet( "border: 1px solid gray; border-width: 0px 0px 1px 1px; " );
            
            auto frame = new QFrame();
            frame->setObjectName( "frame" );
            frame->setStyleSheet( "#frame { border: 1px solid gray; border-width: 0px 0px 1px 0px; }" );

            layout->addWidget( left );
            layout->addWidget( frame );
            layout->addWidget( right );

            return true;
        }

        bool    ConverterToQWidget::createSection( QBoxLayout * parent, const SectionPtr & section ) {
            auto layout = new QHBoxLayout();
            layout->setMargin( 0 );
            layout->setSpacing( 0 );
            parent->addLayout( layout );

            
            auto left = new QFrame();
            left->setFixedHeight( section->getHeight() );
            left->setFixedWidth( 30 );
            left->setStyleSheet( "border: 1px solid gray; border-width: 0px 1px 1px 0px; " );

            auto right = new QFrame();
            right->setFixedHeight( section->getHeight() );
            right->setFixedWidth( 30 );
            right->setStyleSheet( "border: 1px solid gray; border-width: 0px 0px 1px 1px; " );
            
            auto frame = new QFrame();
            frame->setFixedHeight( section->getHeight() );
            frame->setObjectName( "frame" );
            frame->setStyleSheet( "#frame { border: 1px solid gray; border-width: 0px 0px 1px 0px; }" );

            layout->addWidget( left );
            layout->addWidget( frame );
            layout->addWidget( right );

            auto label = new QLabel( frame );
            label->setText( section->getTagName() );
            label->setAttribute( Qt::WA_TranslucentBackground );
            label->setStyleSheet( "font-size: 26px; color: gray" );
            label->setAlignment( Qt::AlignCenter );
            label->resize( frame->size() );

            if( !createBands( frame, section ) ) {
                return false;;
            }

            return true;
        }

        bool    ConverterToQWidget::createBands( QWidget * parent, const SectionPtr & section ) {
            for( auto && band : section->getBands() ) {
                auto frame = new QFrame( parent );
                for( auto && staticText : band->getStaticTexts() ) {
                    auto label = new QLabel( frame );
                    label->setStyleSheet( "border: 1px solid gray;" );
                    label->setGeometry( staticText->getRect() );
                    label->setText( staticText->getText() );
                }
                for( auto && textField : band->getTextFields() ) {
                    auto label = new QLabel( frame );
                    label->setStyleSheet( "border: 1px solid gray;" );
                    label->setGeometry( textField->getRect() );
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
