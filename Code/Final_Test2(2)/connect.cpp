#include "connect.h"
#include "ui_connect.h"

Connect::Connect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connect)
{
    ui->setupUi(this);
    setWindowTitle("About this");
    setWindowIcon(QIcon(QPixmap(":/new/prefix1/images/chaos-theory-250.png")));
    setFixedSize(this->width(),this->height());
    ui->pushButton->setFocus();
    ui->pushButton->setDefault(true);
}

Connect::~Connect()
{
    delete ui;
}
