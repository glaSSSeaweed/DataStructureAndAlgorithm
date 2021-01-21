#include "widget.h"
#include "ui_widget.h"
#include "calc.h"
#include <QPushButton>
#include <string>
#include <iostream>
#include <QString>

using namespace std;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //1-9
    buttons.push_back(ui->pushButton);
    buttons.push_back(ui->pushButton_2);
    buttons.push_back(ui->pushButton_3);
    buttons.push_back(ui->pushButton_4);
    buttons.push_back(ui->pushButton_5);
    buttons.push_back(ui->pushButton_6);
    buttons.push_back(ui->pushButton_7);
    buttons.push_back(ui->pushButton_8);
    buttons.push_back(ui->pushButton_9);
    //()0
    buttons.push_back(ui->pushButton_10);
    buttons.push_back(ui->pushButton_11);
    buttons.push_back(ui->pushButton_12);
    buttons.push_back(ui->pushButton_13);
    buttons.push_back(ui->pushButton_14);
    buttons.push_back(ui->pushButton_15);
    buttons.push_back(ui->pushButton_16);
    buttons.push_back(ui->pushButton_17);
    buttons.push_back(ui->pushButton_18);
    buttons.push_back(ui->pushButton_19);
    buttons.push_back(ui->pushButton_20);

    //calc
    buttons.push_back(ui->calc);
    for(int i =0; i< 20; ++i){
        buttons[i]->setStyleSheet("QPushButton{font-family:'宋体';font-size:32px;color:rgb(0,0,0,255);}\
        QPushButton{background-color:rgb(170,200,50)}\ QPushButton:hover{background-color:rgb(50, 170, 200)}");
        connect(buttons[i], &QPushButton::clicked, this, Widget::clickedButton);
    }
    ui->calc->setStyleSheet("QPushButton{font-family:'宋体';font-size:32px;color:rgb(0,0,0,255);}\
    QPushButton{background-color:rgb(170,200,50)}\ QPushButton:hover{background-color:rgb(50, 170, 200)}");

    connect(ui->calc, &QPushButton::clicked, this, Widget::calculate);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::clickedButton(){
    QPushButton* bt = static_cast<QPushButton *>(sender());
    int id = buttons.indexOf(bt);
    switch (id) {
    case 0:case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:
         ui->lineEdit->setText(ui->lineEdit->text()+QString::number(id+1));break;
    case 9:ui->lineEdit->setText(ui->lineEdit->text()+"(");break;
    case 10:ui->lineEdit->setText(ui->lineEdit->text()+")");break;
    case 11:ui->lineEdit->setText(ui->lineEdit->text()+"0");break;
    case 12:ui->lineEdit->setText(ui->lineEdit->text()+"sin");break;
    case 13:ui->lineEdit->setText(ui->lineEdit->text()+"cos");break;
    case 14:ui->lineEdit->setText(ui->lineEdit->text()+"tan");break;
    case 15:
        ui->lineEdit->setText(ui->lineEdit->text().left(ui->lineEdit->text().size()-1));
        break;
    case 16:ui->lineEdit->setText(ui->lineEdit->text()+"+");break;
    case 17:ui->lineEdit->setText(ui->lineEdit->text()+"-");break;
    case 18:ui->lineEdit->setText(ui->lineEdit->text()+"*");break;
    case 19:ui->lineEdit->setText(ui->lineEdit->text()+"/");break;
    default:break;



    }
}

void Widget::calculate(){
    string formula(ui->lineEdit->text().toStdString());
    Calc::decodeFormula(formula);
    formula.append("#");
    Calc c(formula);
    ui->lineEdit->setText(QString::number(c.ans(), 'g'));
}

