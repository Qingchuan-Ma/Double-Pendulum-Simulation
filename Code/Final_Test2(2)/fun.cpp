#include "fun.h"
#include "ui_fun.h"

Fun::Fun(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fun)
{
    ui->setupUi(this);
    setWindowTitle("Fun");
    setWindowIcon(QIcon(QPixmap(":/new/prefix1/images/chaos-theory-250.png")));
    setFixedSize(this->width(),this->height());
    ui->pushButton->setFocus();
    ui->pushButton->setDefault(true);
}

Fun::~Fun()
{
    delete ui;
}
