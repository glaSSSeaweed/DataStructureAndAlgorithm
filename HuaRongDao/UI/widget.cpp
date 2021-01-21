#include "widget.h"
#include "ui_widget.h"
#include "HRD.h"
#include <vector>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include <stack>
#include <windows.h>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget), h(new HRD()), buttons(new QVector<QPushButton*>()),flag(true)
{
    edge = new std::vector<std::vector<int>>{{ 1, 3 },{ 0, 4, 2 },{ 1, 5 },{ 0, 4 , 6}, { 3, 1, 5 ,7},{ 4, 2, 8},{3, 7},{6, 4, 8},{7, 5}};
    ui->setupUi(this);
    const std::vector<int>& board = h->getBoard();
    buttons->push_back(ui->pushButton);
    buttons->push_back(ui->pushButton_2);
    buttons->push_back(ui->pushButton_3);
    buttons->push_back(ui->pushButton_4);
    buttons->push_back(ui->pushButton_5);
    buttons->push_back(ui->pushButton_6);
    buttons->push_back(ui->pushButton_7);
    buttons->push_back(ui->pushButton_8);
    buttons->push_back(ui->pushButton_9);
    for(int i =0; i< board.size(); ++i){
        (*buttons)[i]->setText(QString::number(board[i]));

        (*buttons)[i]->setStyleSheet("QPushButton{font-family:'宋体';font-size:36px;color:rgb(0,0,0,255);}\
        QPushButton{background-color:rgb(170,200,50)}\ QPushButton:hover{background-color:rgb(50, 170, 200)}");
        connect((*buttons)[i], &QPushButton::clicked, this, Widget::move);
    }
    connect(ui->pushButton_10, &QPushButton::clicked, this, Widget::autoMove);

    p = h->path();
    cur = p->top();
    p->pop();
}
void Widget::autoMove(){
    if(flag){
        const std::vector<int>& board = h->getBoard();
        for(int i =0; i< board.size(); ++i)
        (*buttons)[i]->setText(QString::number(board[i]));
        flag = false;
    }
    else{
        if(!p->empty()){
            qDebug()<<cur<<endl;
            int dest = p->top();
            //qDebug()<<dest;
            (*buttons)[cur]->setText((*buttons)[dest]->text());
            //qDebug()<<(*buttons)[cur]->text();
            (*buttons)[dest]->setText("0");
            Sleep(1000);
            p->pop();
            cur = dest;
        }
    }

}




void Widget::move(){
    QPushButton* bt = static_cast<QPushButton *>(sender());
    int id = buttons->indexOf(bt);
    if(bt->text() == "0"){
        return ;
    }
    for(auto i : (*edge)[id]){
        if((*buttons)[i]->text() == "0"){
           (*buttons)[i]->setText(bt->text());
            bt->setText("0");
           break;
        }
    }
}

Widget::~Widget()
{
    delete h;
    delete edge;
    delete buttons;
    delete ui;
    if(p) delete p;
}
