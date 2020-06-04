#include "widget.h"
#include "ui_widget.h"

#include "game.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    game *newForm1;
    newForm1 = new game(0);
    newForm1->show();
}

void Widget::on_pushButton_2_clicked()
{
    game *newForm1;
    newForm1 = new game(1);
    newForm1->show();
}

void Widget::on_pushButton_3_clicked()
{
    game *newForm1;
    newForm1 = new game(2);
    newForm1->show();
}
