#pragma once
#ifndef REPLACER_HPP
#define REPLACER_HPP
#include <QString>
#include "tags/report.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, заменяющий параметры на реальные значения.

        Класс, заменяющий параметры на реальные значения в тэгах,
        производных от TextWidget
        */
        class Replacer {

        public:
            Replacer();
            ~Replacer();

            /*! @~russian
            Возвращает текст с подставленными значениями параметров.
            @param[in] report Указатель на отчет
            @param[in] text Исходный текст
            */
            static QString  replaceParameters( const ReportPtr & report, const QString & text );

            /*! @~russian
            Возвращает текст с подставленными значениями полей из источника данных.
            @param[in] report Указатель на отчет
            @param[in] text Исходный текст
            @param[in] i Текущая строка
            */
            static QString  replaceField( const ReportPtr & report, const QString & text, int i );

        private:

        };

    }
}

#endif // REPLACER_HPP
