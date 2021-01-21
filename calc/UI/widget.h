#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVector>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QVector<QPushButton*> buttons;
    Ui::Widget *ui;
    void clickedButton();
    void calculate();


};

#endif // WIDGET_H

