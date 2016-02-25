#ifndef PAINTER_H
#define PAINTER_H

#include <QString>

/* Осуществляет отображение отчета в некоторые форматы. */

class Painter
{
public:
    Painter();

    bool beginPDF_Drawing(QString path); // Вызывается первой

    int beginObjectDrawing(); // Вызывается перед отрисовкой конкретного объекта, возвращает его код
    bool setWorkspace(int x, int y, int w, int h); /* Устанавливает зону отрисовки для последнего объекта,
                                                      вызвавшего begin_object_drawing(). */
    bool endObjectDrawing(int workspace_id);

    void pageDrawingComplete(); // Завершает отрисовку данной страницы, используется объектом Report

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

    QString lastError();

protected:

    void newPage(); // Создать новую страницу
};

#endif // PAINTER_H
