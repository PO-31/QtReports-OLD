#ifndef PAINTER_H
#define PAINTER_H

#include <QString>

#include "Style.h"

/* Осуществляет отображение отчета в некоторые форматы. */

class Painter
{
public:
    Painter();

    bool beginPDF_Drawing(QString path); /* Эта функция задает формат и файл, в которые будет транслирован готовый отчет.
                                           Вызывается перед началом рисования один раз. */

    int beginObjectDrawing(); /* Вызывается перед отрисовкой конкретного объекта, возвращает его код. Теперь все последующие
                                действия (задание рабочей зоны, рисование объектов, задание стиля и пр.) будут ассойиированы
                                с этим объектом. */
    bool setWorkspace(int x, int y, int w, int h); /* Устанавливает зону отрисовки для последнего объекта,
                                                      вызвавшего begin_object_drawing().
                                                      Причем координаты x и y задаются относительно координат области объекта,
                                                      вызвавшего setWorkspace выше. Т.е. рабочие области вкладываются.
                                                      Кроме того, рабочая область потомка не может выходить за пределы рабочей
                                                      области родителя. */

    bool endObjectDrawing(int workspace_id); /* Заканчивает рисовать объект. */

    void pageDrawingComplete(); /* Завершает отрисовку данной страницы, используется объектом Report. */

    bool drawLine(int x1, int y1, int x2, int y2);

    bool drawText(int x, int y, QString text);

    void setFont();
    void setPen();
    void setBrush();

    void newPageRequest(); // Вызывается, если объект требует новую страницу для отрисовки
    bool isNewPageRequested();

    bool setCurrentPage(int ind);
    int pagesCount();

    int currPage();

    void setStyle(int style_id);

    QString lastError();

protected:

    void newPage(); // Создать новую страницу

    void setStyle(const Style& style); // Задать стиль отрисовки
};

#endif // PAINTER_H
