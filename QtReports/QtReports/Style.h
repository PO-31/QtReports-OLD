#ifndef STYLE_H
#define STYLE_H


#include <QString>
#include <QColor>

class Style
{
public:
    Style();

    int id() const;
    void setId(int _id);

    QString getName() const;
    void setName(QString name);

    bool isDefault() const; // Стиль по умолчанию
    void setDefault(bool def);

    int fontSize() const; // Размер шрифта
    void setFontSize(int size);

    QColor fontColor() const; // Цвет шрифта
    void setFontColor(QColor f_color);

    QString fontName() const; // Имя шрифта
    void setFontName(QString f_name);

    bool isBold() const; // Жирный шрифт
    void setBold(bool flag);

    bool isItalic() const; // Курсив
    void setItalic(bool flag);

protected:
};

#endif // STYLE_H
