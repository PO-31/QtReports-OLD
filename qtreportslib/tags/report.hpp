#pragma once
#ifndef REPORT_HPP
#define REPORT_HPP

#include <QString>
#include <QSize>
#include <QMap>
#include <QVector>
#include <QSharedPointer>
#include <QMargins>
#include <QPrinter>

#include "object.hpp"
#include "field.hpp"
#include "style.hpp"
#include "title.hpp"
#include "detail.hpp"

namespace qtreports {
    namespace detail {

        /*! @~russian
        @brief Класс, реализующий тэг <Report>
        Класс, реализующий тэг <Report>
        */
        class Report : public Object {
                 
        public:
            Report();
            ~Report();

            /*! @~russian
            Устанавливает стиль по умолчанию
            @param[in] имя стиля
            */
            void                                setDefaultStyle( const StylePtr & style );
            /*! @~russian
            Возвращает стиль по умолчанию
            */
            const StylePtr                      getDefaultStyle() const;

            /*! @~russian
            Устанавливает стиль 
            @param[in] имя стиля
            @param[in] имя стиля
            */
            void                                setStyle( const QString & name, const StylePtr & style );
            /*! @~russian
            Возвращает имя стиля стиль по умолчанию
            @param[in] имя стиля
            */
            const StylePtr                      getStyle( const QString & name ) const;
            /*! @~russian
            Возвращате QMap стилей
            */
            const QMap< QString, StylePtr >     getStyles() const;

            /*! @~russian
            Устанавливает запрос
            @param[in] запрос
            */
            void                                setQuery( const QString & query );
            /*! @~russian
            Возвращате запрос
            */
            const QString                       getQuery() const;

            /*! @~russian
            Устанавливает Field 
            @param[in] имя Field 
            @param[in] содержимое Field
            */
            void                                setField( const QString & name, const FieldPtr & field );            
            /*! @~russian
            Возвращате Field
            @param[in] имя Field 
            */
            const FieldPtr                      getField( const QString & name ) const;            
            /*! @~russian
            Возвращате Field
            */
            const QMap< QString, FieldPtr >     getFields() const;
            /*! @~russian
            Устанавливает данные Field 
            @param[in] имя Field 
            @param[in] вектор данных Field
            */
            void                                setFieldData( const QString & name, const QVector< QVariant > & data );

            /*! @~russian
            Устанавливает название отчета
            @param[in] название
            */
            void                                setTitle( const TitlePtr & title );
            /*! @~russian
            Возвращате название отчета
            */
            const TitlePtr                      getTitle() const;

            /*! @~russian
            Устанавливает Detail
            @param[in] название Detail
            */
            void                                setDetail( const DetailPtr & detail );
            /*! @~russian
            Возвращате Detail
            */
            const DetailPtr                     getDetail() const;

            /*! @~russian
            Устанавливаются ссылки на обьекты
            @param[in] имя
            @param[in] значение
            */
            void                                setParameter( const QString & name, const QVariant & value );
            /*! @~russian
            Устанавливаем QMap ссылок на обьекты
            @param[in] Ссылки на параметры
            */            
            void                                setParameters( const QMap< QString, QVariant > & parameters );
            /*! @~russian
            Возвращате имя параметра
            */            
            const QVariant                      getParameter( const QString & name ) const;
            /*! @~russian
            Возвращате карту параметров с названием и значением
            */            
            const QMap< QString, QVariant >     getParameters() const;

            /*! @~russian
            Устанавливаем количество строк
            @param[in] количество
            */
            void    setRowCount( int count );
            /*! @~russian
            Возвращате количество строк
            */
            int     getRowCount() const;

            /*! @~russian
            Устанавливаем ориентации отчета книжная/альбомная
            @param[in] ориентация
            */
            void                    setOrientation( QPrinter::Orientation orientation );
            QPrinter::Orientation   getOrientation() const;

            /*! @~russian
            Устанавливаем размер отчета
            @param[in] размер
            */
            void            setSize( const QSize & size );
            const QSize     getSize() const;

            /*! @~russian
            Устанавливаем ширину отчета
            @param[in] значение ширины
            */
            void            setWidth( int width );
            int             getWidth() const;

            /*! @~russian
            Устанавливаем высоту отчета
            @param[in] значение высоты
            */
            void            setHeight( int height );
            int             getHeight() const;
            
            /*! @~russian
            Устанавливаем левый отступ
            @param[in] значение 
            */
            void    setLeftMargin( int left );
            int     getLeftMargin() const;
            
            /*! @~russian
            Устанавливаем верхний отступ
            @param[in] значение
            */
            void    setTopMargin( int top );
            int     getTopMargin() const;
            
            /*! @~russian
            Устанавливаем правый отступ
            @param[in] значение
            */
            void    setRightMargin( int right );
            int     getRightMargin() const;
            
            /*! @~russian
            Устанавливаем нижний отступ
            @param[in] значение
            */
            void    setBottomMargin( int bottom );
            int     getBottomMargin() const;

            /*! @~russian
            Устанавливаем отступы от краев
            @param[in] слева
            @param[in] сверху
            @param[in] справа
            @param[in] снизу
            */
            void            setMargins( int left, int top, int right, int bottom );
            /*! @~russian
            Устанавливаем карту отступов
            @param[in] отступы
            */            void            setMargins( const QMargins & margins );
            const QMargins  getMargins() const;

        private:
            QPrinter::Orientation	    m_orientation;
            QSize	                    m_size;
            QMargins                    m_margins;
            int                         m_rowCount;
            StylePtr                    m_defaultStyle;
            QMap< QString, StylePtr >   m_styles;
            QString                     m_query;
            QMap< QString, FieldPtr >   m_fields;
            TitlePtr                    m_title;
            DetailPtr                   m_detail;
            QMap< QString, QVariant >   m_parameters;

        };
        typedef QSharedPointer< Report > ReportPtr;

    }
}

#endif // REPORT_HPP
