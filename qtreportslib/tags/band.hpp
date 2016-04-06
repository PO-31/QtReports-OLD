#pragma once
#ifndef BAND_HPP
#define BAND_HPP
#include <QVector>
#include <QSharedPointer>
#include "statictext.hpp"
#include "textfield.hpp"
#include "line.hpp"
#include "rect.hpp"
#include "ellipse.hpp"
#include "image.hpp"
#include "widget.hpp"

namespace qtreports {
    namespace detail {
        
        /*! @~russian
        @brief Класс, реализующий тэг <Band>
        Класс, реализующий тэг <Band
        */
        class Band : public Widget {

        public:
            Band();
            ~Band();
            
            /*! @~russian
            Добавляет <StaticText> в <Band>
            @param[in] staticText Статичный текст
            */
            void                            addStaticText( const StaticTextPtr & staticText );
            /*! @~russian
            Получаем вектор <StaticText>
            */
            const QVector< StaticTextPtr >  getStaticTexts() const;
            /*! @~russian
            Возвращает  <StaticText> по индексу
            @param[in] index индекс
            */            
            const StaticTextPtr             getStaticText( int index ) const;
            /*! @~russian
            Возращате размер <StaticText>
            */            
            int                             getStaticTextsSize() const;

            /*! @~russian
            Добавляем вычисляемое поле в <Band>
            @param[in] TextField вычисляемое поле
            */
            void                            addTextField( const TextFieldPtr & staticText );
            /*! @~russian
            Получаем вектор <TextFields>
            */            
            const QVector< TextFieldPtr >   getTextFields() const;
            /*! @~russian
            Возвращает  <TextFields> по индексу
            @param[in] index индекс
            */            
            const TextFieldPtr              getTextField( int index ) const;
            /*! @~russian
            Возвращает размер <TextFields>
            */            
            int                             getTextFieldsSize() const;

            /*! @~russian
            Возвращает размер <TextWidgets>
            */  
            int                             getTextWidgetsSize() const;
            /*! @~russian
            Плучаем вектор <TextWidgets>
            */              
            QVector< TextWidgetPtr >        getTextWidgets() const;

            /*! @~russian
            Добавить линию в <Band>
            @param[in] Line линия
            */ 
            void                            addLine( const LinePtr & line );
            /*! @~russian
            Возвращает <Line> по индексу
            @param[in] index индекс
            */             
            const LinePtr                   getLine( int index ) const;
            /*! @~russian
            Возвращает размер <Line>
            */            
            int                             getLinesSize() const;
            /*! @~russian
            Возвращает вектор <Line>
            */             
            const QVector< LinePtr >        getLines() const;

            /*! @~russian
            Добавляем квадрат в <Band>
            @param[in] Rect квадрат
            */  
            void                            addRect( const RectPtr & rect );
            /*! @~russian
            Возвращает <Rect> по индексу
            @param[in] index индекс
            */              
            const RectPtr                   getRect( int index ) const;
            /*! @~russian
            Возвращает размер <Rect>
            */              
            int                             getRectsSize() const;
            /*! @~russian
            Возвращает вектор <Rect>
            */              
            const QVector< RectPtr >        getRects() const;

            /*! @~russian
            Добавляем эллипс в <Band>
            @param[in] Ellipse эллипс
            */   
            void                            addEllipse( const EllipsePtr & rect );
            /*! @~russian
            Возвращает <Ellipse> по индексу
            @param[in] index индекс
            */               
            const EllipsePtr                getEllipse( int index ) const;
             /*! @~russian
            Возвращает размер <Ellipse>
            */              
            int                             getEllipsesSize() const;
            /*! @~russian
            Возвращает вектор <Ellipse>
            */               
            const QVector< EllipsePtr >     getEllipses() const;

            /*! @~russian
            Добавляем изображение в <Band>
            @param[in] Image изображение
            */ 
            void                            addImage( const ImagePtr & rect );
            /*! @~russian
            Возвращает <Image> по индексу
            @param[in] index индекс
            */             
            const ImagePtr                  getImage( int index ) const;
            /*! @~russian
            Возвращает размер <Image>
            */             
            int                             getImagesSize() const;
            /*! @~russian
            Возвращает вектор <Image>
            */             
            const QVector< ImagePtr >       getImages() const;

        private://Храним вектора со значеними
            QVector< StaticTextPtr >    m_staticTexts;
            QVector< TextFieldPtr >     m_textFields;
            QVector< TextWidgetPtr >    m_textWidgets;
            QVector< LinePtr >          m_lines;
            QVector< RectPtr >          m_rects;
            QVector< EllipsePtr >       m_ellipses;
            QVector< ImagePtr >         m_images;

        };
        typedef QSharedPointer< Band > BandPtr;

    }
}

#endif // BAND_HPP
