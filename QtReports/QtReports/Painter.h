#ifndef PAINTER_H
#define PAINTER_H

#include <QString>

/* Осуществляет отображение отчета в некоторые форматы. */

class Painter
{
public:
    Painter();

    bool begin_PDF_drawing(QString path); // Вызывается первой

    int begin_object_drawing(); // Вызывается перед отрисовкой конкретного объекта, возвращает его код
    bool set_workspace(int x, int y, int w, int h); /* Устанавливает зону отрисовки для последнего объекта,
                                                      вызвавшего begin_object_drawing(). */
    bool end_object_drawing(int workspace_id);

    void page_drawing_complete(); // Завершает отрисовку данной страницы, используется объектом Report

    bool draw_line(int x1, int y1, int x2, int y2);

    bool draw_text(int x, int y, QString text);

    void set_font();
    void set_pen();
    void set_brush();

    void new_page_request(); // Вызывается, если объект требует новую страницу для отрисовки
    bool is_new_page_requested();

    bool set_current_page(int ind);
    int pages_count();

    int curr_page();

    QString last_error();

protected:

    void new_page(); // Создать новую страницу
};

#endif // PAINTER_H
