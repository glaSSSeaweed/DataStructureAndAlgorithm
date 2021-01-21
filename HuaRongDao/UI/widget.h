#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QVector>
#include <stack>
class HRD;
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
    void move();
    void autoMove();
    Ui::Widget *ui;
    HRD* h;
    QVector<QPushButton*>* buttons;
    std::vector<std::vector<int>>* edge;
    std::stack<int>* p;
    int cur;
    bool flag;
};

#endif // WIDGET_H
