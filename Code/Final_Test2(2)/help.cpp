#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    setWindowTitle("Helper");
    setWindowIcon(QIcon(QPixmap(":/new/prefix1/images/chaos-theory-250.png")));
    setFixedSize(this->width(),this->height());
    ui->pushButton->setFocus();
    ui->pushButton->setDefault(true);
}

Help::~Help()
{
    delete ui;
}
