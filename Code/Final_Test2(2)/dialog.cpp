#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <cmath>
#include <QApplication>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    TitleBar *pTitleBar = new TitleBar(this);
    installEventFilter(pTitleBar);

    QString title="<p align=center><span style= font-size:11pt; font-weight:600;>Chaos in Pendulum</span></p>";
    setWindowTitle(title);
    setWindowIcon(QIcon(QPixmap(":/new/prefix1/images/chaos-theory-250.png")));

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(125, 125, 125));
    setAutoFillBackground(true);
    setPalette(pal);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pTitleBar);
    pLayout->addStretch();
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(pLayout);

    setFixedSize( this->width (),this->height ());
    ui->MainWidget->setStyleSheet("QWidget#MainWidget{border-image: url(:/new/prefix1/images/lorenz_attractor_by_projecttina.png);}"
                                  "QWidget#MainWidget{border:2px groove gray;border-radius:10px;padding:2px 4px;}");
    ui->MainWidget->setAutoFillBackground(true);

    connect(pTitleBar,SIGNAL(save1()),this,SLOT(showsaving1()));
    connect(pTitleBar,SIGNAL(save2()),this,SLOT(showsaving2()));
    connect(pTitleBar,SIGNAL(save1()),this,SLOT(save1()));
    connect(pTitleBar,SIGNAL(save2()),this,SLOT(save2()));


    connect(ui->Exit,SIGNAL(clicked()),this,SLOT(close()));
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("star river.mp3"));
    player->play();
    player->setVolume(40);

/*********************************************************************************************************************/
    fun = new Fun;
    Run = new QPushButton;
    Return = new QPushButton;
    Stop = new QPushButton;
    Reset = new QPushButton;
    mylabel1 = new QLabel(tr("M1"));
    mylabel2 = new QLabel(tr("M2"));
    mylabel3 = new QLabel("w1");
    mylabel4 = new QLabel("w2");
    myslider1 = new QSlider(Qt::Horizontal);
    myslider2 = new QSlider(Qt::Horizontal);
    myslider3 = new QSlider(Qt::Horizontal);
    myslider4 = new QSlider(Qt::Horizontal);
    mylineEdit1 = new QLineEdit;
    mylineEdit2 = new QLineEdit;
    mylineEdit3 = new QLineEdit;
    mylineEdit4 = new QLineEdit;
    mylineEdit1->setEnabled(false);
    mylineEdit2->setEnabled(false);
    mylineEdit3->setEnabled(false);
    mylineEdit4->setEnabled(false);
    mylineEdit1->setFixedWidth(50);
    mylineEdit2->setFixedWidth(50);
    mylineEdit3->setFixedWidth(50);
    mylineEdit4->setFixedWidth(50);
    mylabel1->setFixedWidth(60);
    mylabel2->setFixedWidth(60);
    mylabel3->setFixedWidth(60);
    mylabel4->setFixedWidth(60);
    mylabel1->setStyleSheet("font: 75 10pt Microsoft YaHei UI;");
    mylabel2->setStyleSheet("font: 75 10pt Microsoft YaHei UI;");
    mylabel3->setStyleSheet("font: 75 12pt Symbol;");
    mylabel4->setStyleSheet("font: 75 12pt Symbol;");
    myslider1->setRange(1,10);
    myslider2->setRange(1,10);
    myslider3->setRange(-500,500);
    myslider4->setRange(-500,500);
    myslider1->setPageStep(1);
    myslider2->setPageStep(1);
    myslider3->setValue(0);
    myslider4->setValue(0);
    connect(myslider1,SIGNAL(valueChanged(int)),this,SLOT(transmit()));
    connect(myslider2,SIGNAL(valueChanged(int)),this,SLOT(transmit()));
    connect(myslider3,SIGNAL(valueChanged(int)),this,SLOT(transmit()));
    connect(myslider4,SIGNAL(valueChanged(int)),this,SLOT(transmit()));
    mylineEdit1->setText("1");
    mylineEdit2->setText("1");
    mylineEdit3->setText("0");
    mylineEdit4->setText("0");

    Run->setText("Run");
    Run->setStyleSheet("QPushButton{font: 75 italic 20pt Yu Mincho Demibold;}");


    Return->setText("Return");
    Return->setStyleSheet("QPushButton{font: 75 italic 20pt Yu Mincho Demibold;}");


    Stop->setText("Stop");
    Stop->setStyleSheet("QPushButton{font: 75 italic 20pt Yu Mincho Demibold;}");


    Reset->setText("Reset");
    Reset->setStyleSheet("QPushButton{font: 75 italic 20pt Yu Mincho Demibold;}");


    graph_two = new Graph2(this);
    graph_two->setFixedSize(510,510);
    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->addWidget(graph_two,0,0);
    QGridLayout *rightLayout = new QGridLayout;
    rightLayout->addWidget(mylabel1,0,0);
    rightLayout->addWidget(mylabel2,1,0);
    rightLayout->addWidget(mylabel3,2,0);
    rightLayout->addWidget(mylabel4,3,0);
    rightLayout->addWidget(myslider1,0,1);
    rightLayout->addWidget(myslider2,1,1);
    rightLayout->addWidget(myslider3,2,1);
    rightLayout->addWidget(myslider4,3,1);
    rightLayout->addWidget(mylineEdit1,0,2);
    rightLayout->addWidget(mylineEdit2,1,2);
    rightLayout->addWidget(mylineEdit3,2,2);
    rightLayout->addWidget(mylineEdit4,3,2);
    rightLayout->addWidget(Run,0,3);
    rightLayout->addWidget(Stop,1,3);
    rightLayout->addWidget(Reset,2,3);
    rightLayout->addWidget(Return,3,3);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    connect(Return,SIGNAL(clicked()),this,SLOT(Return_clicked()));
    connect(Run,SIGNAL(clicked()),this,SLOT(Run_clicked()));
    connect(Stop,SIGNAL(clicked()),this,SLOT(Stop_clicked()));
    connect(Reset,SIGNAL(clicked()),this,SLOT(Reset_clicked()));
    connect(Run,SIGNAL(pressed()),this,SLOT(Run_pressed()));
    connect(Run,SIGNAL(released()),this,SLOT(Run_released()));
    ui->SubStart5->setLayout(mainLayout);

/***********************************************************************************************************************/

    Calculating=new CalculateWidget(this);
    Calculating->setTipInfo("Calculating...");
    Calculating->setTipIcon(QPixmap(":/new/prefix1/images/about.png"));
    Calculating->hide();

    Saving = new CalculateWidget(this);
    Saving->setTipInfo("Saved successfully!!");
    Saving->setTipIcon(QPixmap(":/new/prefix1/images/about.png"));
    Saving->hide();

    Nothing = new CalculateWidget(this);
    Nothing->setTipInfo("Nothing Saved!!");
    Nothing->setTipIcon(QPixmap(":/new/prefix1/images/about.png"));
    Nothing->hide();

    Loading = new CalculateWidget(this);
    Loading->setTipInfo("Loading");
    Loading->setTipIcon(QPixmap(":/new/prefix1/images/about.png"));
    Loading->hide();

/**************************************************************************************************************************/
    Run_2 = new QPushButton;
    Return_2 = new QPushButton;
    Stop_2 = new QPushButton;
    Reset_2 = new QPushButton;
    Some = new QPushButton;
    mylabel1_2 = new QLabel(tr("M1/M3"));
    mylabel2_2 = new QLabel(tr("M2/M3"));
    mylabel3_2 = new QLabel("   w1");
    mylabel4_2 = new QLabel("   w2");
    mylabel5_2 = new QLabel("   w3");
    myslider1_2 = new QSlider(Qt::Horizontal);
    myslider2_2 = new QSlider(Qt::Horizontal);
    myslider3_2 = new QSlider(Qt::Horizontal);
    myslider4_2 = new QSlider(Qt::Horizontal);
    myslider5_2 = new QSlider(Qt::Horizontal);
    mylineEdit1_2 = new QLineEdit;
    mylineEdit2_2 = new QLineEdit;
    mylineEdit3_2 = new QLineEdit;
    mylineEdit4_2 = new QLineEdit;
    mylineEdit5_2 = new QLineEdit;
    mylineEdit1_2->setEnabled(false);
    mylineEdit2_2->setEnabled(false);
    mylineEdit3_2->setEnabled(false);
    mylineEdit4_2->setEnabled(false);
    mylineEdit5_2->setEnabled(false);
    mylineEdit1_2->setFixedWidth(50);
    mylineEdit2_2->setFixedWidth(50);
    mylineEdit3_2->setFixedWidth(50);
    mylineEdit4_2->setFixedWidth(50);
    mylineEdit5_2->setFixedWidth(50);
    mylabel1_2->setFixedWidth(60);
    mylabel2_2->setFixedWidth(60);
    mylabel3_2->setFixedWidth(60);
    mylabel4_2->setFixedWidth(60);
    mylabel5_2->setFixedWidth(60);
    mylabel1_2->setStyleSheet("font: 75 10pt Microsoft YaHei UI;");
    mylabel2_2->setStyleSheet("font: 75 10pt Microsoft YaHei UI;");
    mylabel3_2->setStyleSheet("font: 75 12pt Symbol;");
    mylabel4_2->setStyleSheet("font: 75 12pt Symbol;");
    mylabel5_2->setStyleSheet("font: 75 12pt Symbol;");
    myslider1_2->setRange(2,50);
    myslider2_2->setRange(2,50);
    myslider3_2->setRange(-500,500);
    myslider4_2->setRange(-500,500);
    myslider5_2->setRange(-500,500);
    myslider1_2->setPageStep(1);
    myslider2_2->setPageStep(1);
    myslider1_2->setValue(10);
    myslider2_2->setValue(10);
    myslider3_2->setValue(0);
    myslider4_2->setValue(0);
    myslider5_2->setValue(0);
    connect(myslider1_2,SIGNAL(valueChanged(int)),this,SLOT(transmit_2()));
    connect(myslider2_2,SIGNAL(valueChanged(int)),this,SLOT(transmit_2()));
    connect(myslider3_2,SIGNAL(valueChanged(int)),this,SLOT(transmit_2()));
    connect(myslider4_2,SIGNAL(valueChanged(int)),this,SLOT(transmit_2()));
    connect(myslider5_2,SIGNAL(valueChanged(int)),this,SLOT(transmit_2()));
    mylineEdit1_2->setText("1");
    mylineEdit2_2->setText("1");
    mylineEdit3_2->setText("0");
    mylineEdit4_2->setText("0");
    mylineEdit5_2->setText("0");

    Run_2->setText("Run");
    Run_2->setStyleSheet("QPushButton{font: 75 italic 20pt Yu Mincho Demibold;}");

    Return_2->setText("Return");
    Return_2->setStyleSheet("QPushButton{font: 75 italic 20pt Yu Mincho Demibold;}");

    Stop_2->setText("Stop");
    Stop_2->setStyleSheet("QPushButton{font: 75 italic 20pt Yu Mincho Demibold;}");

    Reset_2->setText("Reset");
    Reset_2->setStyleSheet("QPushButton{font: 75 italic 20pt Yu Mincho Demibold;}");

    Some->setText("Fun");
    Some->setStyleSheet("QPushButton{font: 75 italic 20pt Yu Mincho Demibold;}");

    graph_four = new Graph4(this);
    graph_four->setFixedSize(510,510);
    QGridLayout *leftLayout_2 = new QGridLayout;
    leftLayout_2->addWidget(graph_four,0,0);
    QGridLayout *rightLayout_2 = new QGridLayout;
    rightLayout_2->addWidget(mylabel1_2,3,0);
    rightLayout_2->addWidget(mylabel2_2,4,0);
    rightLayout_2->addWidget(mylabel3_2,0,0);
    rightLayout_2->addWidget(mylabel4_2,1,0);
    rightLayout_2->addWidget(mylabel5_2,2,0);
    rightLayout_2->addWidget(myslider1_2,3,1);
    rightLayout_2->addWidget(myslider2_2,4,1);
    rightLayout_2->addWidget(myslider3_2,0,1);
    rightLayout_2->addWidget(myslider4_2,1,1);
    rightLayout_2->addWidget(myslider5_2,2,1);
    rightLayout_2->addWidget(mylineEdit1_2,3,2);
    rightLayout_2->addWidget(mylineEdit2_2,4,2);
    rightLayout_2->addWidget(mylineEdit3_2,0,2);
    rightLayout_2->addWidget(mylineEdit4_2,1,2);
    rightLayout_2->addWidget(mylineEdit5_2,2,2);
    rightLayout_2->addWidget(Run_2,0,3);
    rightLayout_2->addWidget(Stop_2,1,3);
    rightLayout_2->addWidget(Reset_2,2,3);
    rightLayout_2->addWidget(Return_2,3,3);
    rightLayout_2->addWidget(Some,4,3);

    QHBoxLayout *mainLayout_2 = new QHBoxLayout;
    mainLayout_2->addLayout(leftLayout_2);
    mainLayout_2->addLayout(rightLayout_2);
    connect(Return_2,SIGNAL(clicked()),this,SLOT(Return_2_clicked()));
    connect(Run_2,SIGNAL(clicked()),this,SLOT(Run_2_clicked()));
    connect(Stop_2,SIGNAL(clicked()),this,SLOT(Stop_2_clicked()));
    connect(Reset_2,SIGNAL(clicked()),this,SLOT(Reset_2_clicked()));
    connect(Run_2,SIGNAL(pressed()),this,SLOT(Run_2_pressed()));
    connect(Run_2,SIGNAL(released()),this,SLOT(Run_2_released()));
    connect(Some,SIGNAL(clicked()),this,SLOT(Some_clicked()));
    ui->SubStart7->setLayout(mainLayout_2);

/********************************************************************************************************************/

    clicktimeone=0;
    clicktimetwo=0;
    loadtime=0;

    ui->StartButton->setFocus();
    ui->StartButton->setDefault(true);

    ui->pushButton_9->setFocus();
    ui->pushButton_9->setDefault(true);

    Run->setFocus();
    Run->setDefault(true);

    Run_2->setFocus();
    Run_2->setDefault(true);

    ui->pushButton_3->setFocus();
    ui->pushButton_3->setDefault(true);

    ui->StartButton_2->setFocus();
    ui->StartButton_2->setDefault(true);

    ui->pushButton_5->setFocus();
    ui->pushButton_5->setDefault(true);

    ui->pushButton_7->setFocus();
    ui->pushButton_7->setDefault(true);

    ui->pushButton_11->setFocus();
    ui->pushButton_11->setDefault(true);

    ui->StartButton_2->setFocus();
    ui->StartButton_2->setDefault(true);

    ui->StartButton_4->setFocus();
    ui->StartButton_4->setDefault(true);

    ui->pushButton_12->setFocus();
    ui->pushButton_12->setDefault(true);

    ui->pushButton_15->setFocus();
    ui->pushButton_15->setDefault(true);

}

/*********************************************************************************************************/

Dialog::~Dialog()
{
    delete ui;
}

/********第一个布局和计算***********************************************************************************************/

void Dialog::transmit()
{
    double m1=double(myslider1->value());
    QString str1 = QString("%1").arg(m1);
    mylineEdit1->setText(str1);
    double m2=double(myslider2->value());
    QString str2 = QString("%1").arg(m2);
    mylineEdit2->setText(str2);
    double w1=(double(myslider3->value())*2)/100;
    QString str3 = QString("%1").arg(w1);
    mylineEdit3->setText(str3);
    double w2=(double(myslider4->value())*2)/100;
    QString str4 = QString("%1").arg(w2);
    mylineEdit4->setText(str4);
}

void Dialog::Reset_clicked()
{
    graph_two->reset();
    Run->setEnabled(true);
}

void Dialog::Return_clicked()
{
    ui->MainWidget->setCurrentIndex(4);
}

void Dialog::Stop_clicked()
{
    graph_two->StopAnimate();
    Run->setEnabled(true);
}

void Dialog::Run_clicked()
{
    int step_n=graph_two->get_step_n();
    graph_two->set_step_n(step_n);
    double_pendulum=new Double_Pendulum_Culculate;
    double value_y2= (mylineEdit3->text()).toDouble();
    double value_y4= (mylineEdit4->text()).toDouble();
    double value_m1= (mylineEdit1->text()).toDouble();
    double value_m2= (mylineEdit2->text()).toDouble();

    PVector w= new Vector;
    double value_y1,value_y3;
    if(graph_two->yposition2[step_n]<=graph_two->yposition1[step_n])
    {
        value_y1= atan((graph_two->xposition1[step_n]/(20-graph_two->yposition1[step_n])));
        value_y3= atan(-(((graph_two->xposition2[step_n])-(graph_two->xposition1[step_n]))
                         /((graph_two->yposition2[step_n])-(graph_two->yposition1[step_n]))));
    }
    if(graph_two->yposition2[step_n]>graph_two->yposition1[step_n])
    {
        value_y1= atan((graph_two->xposition1[step_n]/(20-graph_two->yposition1[step_n])));
        value_y3= 3.141592654-atan((((graph_two->xposition2[step_n])-(graph_two->xposition1[step_n]))
                                    /((graph_two->yposition2[step_n])-(graph_two->yposition1[step_n]))));
    }

    double value_l1= sqrt((graph_two->xposition1[step_n])*(graph_two->xposition1[step_n])
                          +(graph_two->yposition1[step_n]-20)*(graph_two->yposition1[step_n]-20));
    double value_l2= sqrt(((graph_two->xposition2[step_n])-(graph_two->xposition1[step_n]))
                          *((graph_two->xposition2[step_n])-(graph_two->xposition1[step_n]))
                          +((graph_two->yposition2[step_n])-(graph_two->yposition1[step_n]))
                          *((graph_two->yposition2[step_n])-(graph_two->yposition1[step_n])));

    double_pendulum->set_l(value_l1/value_l2);
    double_pendulum->set_begin_time(0);
    double_pendulum->set_last_time(200);
    double_pendulum->set_m(value_m1/value_m2);
    double_pendulum->calculate_n();

    int n_graph=double_pendulum->get_n();
    double* output_y_1=new double [n_graph+1];
    double* output_y_2=new double [n_graph+1];
    double* output_y_3=new double [n_graph+1];
    double* output_y_4=new double [n_graph+1];
    double* output_t=new double [n_graph+1];

    double_pendulum->RKCK4_solve(*double_pendulum,value_y1,value_y2,value_y3,value_y4,w,output_y_1,output_y_2,output_y_3,output_y_4,output_t);
    graph_two->set_l1_l2(value_l1,value_l2);
    graph_two->set_n(n_graph+2);
    graph_two->set_y1_to_y4(output_y_1,output_y_2,output_y_3,output_y_4);
    graph_two->BeginAnimate();

    Calculating->hide();
}

void Dialog::Run_pressed()
{
    Calculating->show();
}

void Dialog::Run_released()
{
    Run->setEnabled(false);
}

/*********第二个布局和计算********************************************************************************************************/

void Dialog::transmit_2()
{
    double m1_m3=double(myslider1_2->value());
    QString str1 = QString("%1").arg((m1_m3)/10);
    mylineEdit1_2->setText(str1);
    double m2_m3=double(myslider2_2->value());
    QString str2 = QString("%1").arg((m2_m3)/10);
    mylineEdit2_2->setText(str2);
    double w1=(double(myslider3_2->value())*2)/100;
    QString str3 = QString("%1").arg(w1);
    mylineEdit3_2->setText(str3);
    double w2=(double(myslider4_2->value())*2)/100;
    QString str4 = QString("%1").arg(w2);
    mylineEdit4_2->setText(str4);
    double w3=(double(myslider5_2->value()));
    QString str5 = QString("%1").arg(w3);
    mylineEdit5_2->setText(str5);
}

void Dialog::Reset_2_clicked()
{
    graph_four->reset();
    Run_2->setEnabled(true);
}

void Dialog::Return_2_clicked()
{
    ui->MainWidget->setCurrentIndex(4);
}

void Dialog::Stop_2_clicked()
{
    graph_four->StopAnimate();
    Run_2->setEnabled(true);
}

void Dialog::Run_2_clicked()
{
    int step_n=graph_four->get_step_n();
    graph_four->set_step_n(step_n);
    triple_pendulum=new Triple_Pendulum_Culculate;
    double value_y2= (mylineEdit3_2->text()).toDouble();//w1
    double value_y4= (mylineEdit4_2->text()).toDouble();//w2
    double value_y6= (mylineEdit5_2->text()).toDouble();//w3
    double value_m1_m3= (mylineEdit1_2->text()).toDouble();//m1/m3
    double value_m2_m3= (mylineEdit2_2->text()).toDouble();//m2/m3

    TVector w= new tVector;
    double value_y1,value_y3,value_y5;
    if(graph_four->yposition2[step_n]<=graph_four->yposition1[step_n])
    {
        if(graph_four->yposition3[step_n]<=graph_four->yposition2[step_n])
        {
            value_y1= atan((graph_four->xposition1[step_n]/(40-graph_four->yposition1[step_n])));
            value_y3= atan(-(((graph_four->xposition2[step_n])-(graph_four->xposition1[step_n]))/((graph_four->yposition2[step_n])-(graph_four->yposition1[step_n]))));
            value_y5= atan(-(((graph_four->xposition3[step_n])-(graph_four->xposition2[step_n]))/((graph_four->yposition3[step_n])-(graph_four->yposition2[step_n]))));
        }
        else
        {
            value_y1= atan((graph_four->xposition1[step_n]/(40-graph_four->yposition1[step_n])));
            value_y3= atan(-(((graph_four->xposition2[step_n])-(graph_four->xposition1[step_n]))/((graph_four->yposition2[step_n])-(graph_four->yposition1[step_n]))));
            value_y5= 3.141592654-atan((((graph_four->xposition3[step_n])-(graph_four->xposition2[step_n]))/((graph_four->yposition3[step_n])-(graph_four->yposition2[step_n]))));
        }
    }
    if(graph_four->yposition2[step_n]>graph_four->yposition1[step_n])
    {
        if(graph_four->yposition3[step_n]<=graph_four->yposition2[step_n])
        {
            value_y1= atan((graph_four->xposition1[step_n]/(40-graph_four->yposition1[step_n])));
            value_y3= 3.141592654-atan((((graph_four->xposition2[step_n])-(graph_four->xposition1[step_n]))/((graph_four->yposition2[step_n])-(graph_four->yposition1[step_n]))));
            value_y5= atan(-(((graph_four->xposition3[step_n])-(graph_four->xposition2[step_n]))/((graph_four->yposition3[step_n])-(graph_four->yposition2[step_n]))));
        }
        else
        {
            value_y1= atan((graph_four->xposition1[step_n]/(40-graph_four->yposition1[step_n])));
            value_y3= 3.141592654-atan((((graph_four->xposition2[step_n])-(graph_four->xposition1[step_n]))/((graph_four->yposition2[step_n])-(graph_four->yposition1[step_n]))));
            value_y5= 3.141592654-atan((((graph_four->xposition3[step_n])-(graph_four->xposition2[step_n]))/((graph_four->yposition3[step_n])-(graph_four->yposition2[step_n]))));
        }
    }

    double value_l1= sqrt((graph_four->xposition1[step_n])
                              *(graph_four->xposition1[step_n])
                              +(graph_four->yposition1[step_n]-40)
                              *(graph_four->yposition1[step_n]-40));
    double value_l2= sqrt(((graph_four->xposition2[step_n])-(graph_four->xposition1[step_n]))
                              *((graph_four->xposition2[step_n])-(graph_four->xposition1[step_n]))
                              +((graph_four->yposition2[step_n])-(graph_four->yposition1[step_n]))
                              *((graph_four->yposition2[step_n])-(graph_four->yposition1[step_n])));
    double value_l3= sqrt(((graph_four->xposition3[step_n])-(graph_four->xposition2[step_n]))
                              *((graph_four->xposition3[step_n])-(graph_four->xposition2[step_n]))
                              +((graph_four->yposition3[step_n])-(graph_four->yposition2[step_n]))
                              *((graph_four->yposition3[step_n])-(graph_four->yposition2[step_n])));
    triple_pendulum->set_l_1(value_l1/value_l3);
    triple_pendulum->set_l_2(value_l2/value_l3);
    triple_pendulum->set_m_1(value_m1_m3);
    triple_pendulum->set_m_2(value_m2_m3);
    triple_pendulum->set_begin_time(0);
    triple_pendulum->set_last_time(200);
    triple_pendulum->calculate_n();

    int n_graph=triple_pendulum->get_n();
    double* output_y_1=new double [n_graph+1];
    double* output_y_2=new double [n_graph+1];
    double* output_y_3=new double [n_graph+1];
    double* output_y_4=new double [n_graph+1];
    double* output_y_5=new double [n_graph+1];
    double* output_y_6=new double [n_graph+1];
    double* output_t=new double [n_graph+1];

    triple_pendulum->RK4_solve_triple(*triple_pendulum,value_y1,value_y2,value_y3,value_y4,value_y5,value_y6,w,output_y_1,output_y_2
                                      ,output_y_3,output_y_4,output_y_5,output_y_6,output_t);

    graph_four->set_l1_to_l3(value_l1,value_l2,value_l3);
    graph_four->set_n(n_graph+2);
    graph_four->set_y1_to_y6(output_y_1,output_y_2,output_y_3,output_y_4,output_y_5,output_y_6);
    graph_four->BeginAnimate();
    Calculating->hide();
}

void Dialog::Run_2_pressed()
{
    Calculating->show();
}

void Dialog::Run_2_released()
{
    Run_2->setEnabled(false);
}

void Dialog::Some_clicked()
{
    fun->show();
}

/*********************************************鼠标移动事件*******************************************************/

void Dialog::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons()&Qt::LeftButton)
    {
        if(e->x()<=520 && e->x()>=0 && e->y()<=520 && e->y()>=0)
        {
            graph_two->transmitposition1(e->x()-20,e->y()-50);
            graph_four->transmitposition1(e->x()-20,e->y()-50);
        }
    }
    else if(e->buttons()&Qt::RightButton)
    {
        if(e->x()<=520 && e->x()>=0 && e->y()<=520 && e->y()>=0)
        {
            graph_two->transmitposition2(e->x()-20,e->y()-50);
            graph_four->transmitposition3(e->x()-20,e->y()-50);
        }
    }
    else if(e->buttons()&Qt::MidButton)
    {
        if(e->x()<=520 && e->x()>=0 && e->y()<=520 && e->y()>=0)
        {
            graph_four->transmitposition2(e->x()-20,e->y()-50);
        }
    }
}

/*********************************************关闭事件************************************************************/

void Dialog::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, tr("Exit"),
                                   QString(tr("Really Exit?")),
                                   QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No) {
          event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes) {
          event->accept();  //接受退出信号，程序退出
    }
}

/*********************************************键盘事件**************************************************************/

void Dialog::keyPressEvent( QKeyEvent *e )
{

    switch ( e->key() )
{
    case Qt::Key_Escape:
        close();
        break;
}
}

/*********************************************第一个按钮按下***************************************************************/
void Dialog::on_pushButton_5_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    graph_one = new Graph1(this);
    graph_one_one=new Graph1_1(this);
    graph_one_two=new Graph1_2(this);
    graph_one_three=new Graph1_3(this);
    if(clicktimeone >= 1)
    {
        graph_one->set_h_time(90);
    }
    double_pendulum=new Double_Pendulum_Culculate;

    double value_y1 = ui->number_1->value();
    double value_y2 = ui->number_2->value();
    double value_y3 = ui->number_3->value();
    double value_y4 = ui->number_4->value();
    double value_m1 = ui->number_5->value();
    double value_m2 = ui->number_6->value();
    double_pendulum->set_m(value_m1/value_m2);

    double value_l1 = ui->number_7->value();
    double value_l2 = ui->number_8->value();
    double_pendulum->set_l(value_l1/value_l2);

    double value_t = ui->number_9->value();
    double_pendulum->set_last_time(value_t);

    double_pendulum->set_begin_time(0);
    double_pendulum->calculate_n();
    int n_graph=double_pendulum->get_n();

    double* output_y_1=new double [n_graph+1];
    double* output_y_2=new double [n_graph+1];
    double* output_y_3=new double [n_graph+1];
    double* output_y_4=new double [n_graph+1];
    double* output_t=new double [n_graph+1];

    PVector w= new Vector;
    double_pendulum->RKCK4_solve(*double_pendulum,value_y1,value_y2,value_y3,value_y4,w,output_y_1,output_y_2,output_y_3,output_y_4,output_t);
    graph_one->set_l1_l2(value_l1,value_l2,value_l1+value_l2);
    graph_one->set_n(n_graph+1);
    graph_one->set_y1_to_y4(output_y_1,output_y_2,output_y_3,output_y_4);

    graph_one_one->set_n(n_graph+1);
    graph_one_one->set_y1_y2(output_y_1,output_y_2);
    graph_one_two->set_n(n_graph+1);
    graph_one_two->set_y3_y4(output_y_3,output_y_4);
    graph_one_three->set_n(n_graph+1);
    graph_one_three->set_y1_y3(output_y_1,output_y_3);

    ui->MainWidget->setCurrentIndex(1);
    clicktimeone+=1;
    Calculating->hide();
    QApplication::restoreOverrideCursor();
}

/*********************************************第一个Run按下*********************************************************************/

void Dialog::on_pushButton_9_clicked()
{
    graph_one->setGeometry(50,50,950,950);
    graph_one_one->setGeometry(1050,50,400,400);
    graph_one_two->setGeometry(1050,500,400,400);
    graph_one_three->setGeometry(1500,500,400,400);
    graph_one->setTitle("Animate");
    graph_one_one->setTitle(tr("θ1~ω1"));
    graph_one_two->setTitle(tr("θ2~ω2"));
    graph_one_three->setTitle(tr("θ1~θ2"));
    bool animate=ui->checkBox_5->isChecked();
    bool phase_one=ui->checkBox_2->isChecked();
    bool phase_two=ui->checkBox_3->isChecked();
    bool phase_three=ui->checkBox_4->isChecked();
    if(animate)
    {
        graph_one->BeginAnimate();
        graph_one->show();
    }
    if(phase_one){graph_one_one->show();}
    if(phase_two){graph_one_two->show();}
    if(phase_three){graph_one_three->show();}
}

/*********************************************第二个按钮按下********************************************************/

void Dialog::on_pushButton_7_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    clicktimetwo=clicktimetwo+1;
    graph_three=new Graph3(this);
    graph_three_one=new Graph3_1(this);
    graph_three_two=new Graph3_2(this);
    graph_three_three=new Graph3_3(this);

    triple_pendulum=new Triple_Pendulum_Culculate;

    double value_y1 = ui->number3_1->value();
    double value_y2 = ui->number3_2->value();
    double value_y3 = ui->number3_3->value();
    double value_y4 = ui->number3_4->value();
    double value_y5 = ui->number3_5->value();
    double value_y6 = ui->number3_6->value();
    double value_m1_m3 = ui->number3_7->value();
    double value_m2_m3 = ui->number3_8->value();
    double value_l1_l3 = ui->number3_9->value();
    double value_l2_l3 = ui->number3_10->value();
    double value_t = ui->number3_11->value();
    triple_pendulum->set_m_1(value_m1_m3);
    triple_pendulum->set_m_2(value_m2_m3);
    triple_pendulum->set_l_1(value_l1_l3);
    triple_pendulum->set_l_2(value_l2_l3);

    triple_pendulum->set_last_time(value_t);

    triple_pendulum->set_begin_time(0);
    triple_pendulum->calculate_n();
    int n_graph=triple_pendulum->get_n();

    double* output3_y_1=new double [n_graph+1];
    double* output3_y_2=new double [n_graph+1];
    double* output3_y_3=new double [n_graph+1];
    double* output3_y_4=new double [n_graph+1];
    double* output3_y_5=new double [n_graph+1];
    double* output3_y_6=new double [n_graph+1];
    double* output3_t=new double [n_graph+1];

    TVector w= new tVector;
    triple_pendulum->RK4_solve_triple(*triple_pendulum,value_y1,value_y2,value_y3,value_y4,
                                        value_y5,value_y6,w,output3_y_1,output3_y_2,output3_y_3,output3_y_4,output3_y_5,output3_y_6,output3_t);
    graph_three->set_l1_l3(value_l1_l3*1,value_l2_l3*1,1,value_l1_l3*1+value_l2_l3*1+1);
    graph_three->set_n(n_graph+1);
    graph_three->set_y1_to_y6(output3_y_1,output3_y_2,output3_y_3,output3_y_4,output3_y_5,output3_y_6);


    graph_three_one->set_n(n_graph+1);
    graph_three_one->set_y1_y2(output3_y_1,output3_y_2);
    graph_three_two->set_n(n_graph+1);
    graph_three_two->set_y3_y4(output3_y_3,output3_y_4);
    graph_three_three->set_n(n_graph+1);
    graph_three_three->set_y5_y6(output3_y_5,output3_y_6);

    ui->MainWidget->setCurrentIndex(7);
    Calculating->hide();
    QApplication::restoreOverrideCursor();
}

/********************************************第二个Run按下**********************************************************/

void Dialog::on_pushButton_11_clicked()
{

    graph_three->setGeometry(50,50,950,950);
    graph_three_one->setGeometry(1050,50,400,400);
    graph_three_two->setGeometry(1050,500,400,400);
    graph_three_three->setGeometry(1500,500,400,400);
    graph_three->setTitle("Animate");
    graph_three_one->setTitle(tr("θ1~ω1"));
    graph_three_two->setTitle(tr("θ2~ω2"));
    graph_three_three->setTitle(tr("θ3~ω3"));
    bool animate2=ui->checkBox_6->isChecked();
    bool phase_one2=ui->checkBox_9->isChecked();
    bool phase_two2=ui->checkBox_8->isChecked();
    bool phase_three2=ui->checkBox_7->isChecked();
    if(animate2)
    {
        graph_three->BeginAnimate();
        graph_three->show();
    }
    if(phase_one2){graph_three_one->show();}
    if(phase_two2){graph_three_two->show();}
    if(phase_three2){graph_three_three->show();}
}

/********************************************页码的跳转************************************************************/

void Dialog::on_StartButton_2_clicked()//控制start的选项和mouse的跳页
{
    bool d=ui->Double->isChecked();
    bool mouse=ui->radioButton->isChecked();
    if(d)
    {
        if(mouse)
        {
            ui->MainWidget->setCurrentIndex(2);
        }
        else
            ui->MainWidget->setCurrentIndex(5);
    }
    if(!d)
    {
        if(mouse)
        {
            ui->MainWidget->setCurrentIndex(8);
        }
        else
            ui->MainWidget->setCurrentIndex(6);
    }
}

void Dialog::on_pushButton_10_clicked()
{
    ui->MainWidget->setCurrentIndex(6);
}

void Dialog::on_pushButton_8_clicked()
{
    ui->MainWidget->setCurrentIndex(5);
}

void Dialog::on_pushButton_6_clicked()
{
    ui->MainWidget->setCurrentIndex(4);
}

void Dialog::on_ContinueButton_clicked()//同时判断是否save文件了
{
    QFile file_1("theta1 of double pendulum.txt");
    QFile file_2("theta1 of triple pendulum.txt");
    if(!file_1.exists())
    {
        ui->Double_2->setCheckable(false);
        ui->Double_2->setChecked(false);
    }
    if(file_1.exists()&&!file_2.exists())
    {
        ui->Double_2->setCheckable(true);
        ui->Double_2->setChecked(true);
    }
    if(!file_2.exists())
    {
        ui->Triple_2->setCheckable(false);
        ui->Triple_2->setChecked(false);
    }
    if(file_2.exists()&&!file_1.exists())
    {
        ui->Triple_2->setChecked(true);
        ui->Triple_2->setCheckable(true);
    }
    if(file_2.exists()&&file_1.exists())
    {
        ui->Triple_2->setChecked(false);
        ui->Triple_2->setCheckable(true);
        ui->Double_2->setCheckable(true);
        ui->Double_2->setChecked(true);
    }
    bool double_2=ui->Double_2->isChecked();
    bool triple_2=ui->Triple_2->isChecked();
    if(!double_2&&!triple_2)
    {
        ui->StartButton_4->setEnabled(false);
    }
    ui->MainWidget->setCurrentIndex(9);
}

void Dialog::on_StartButton_3_clicked()
{
    ui->MainWidget->setCurrentIndex(0);
}

void Dialog::on_StartButton_5_clicked()
{
    ui->MainWidget->setCurrentIndex(0);
}

void Dialog::on_pushButton_13_clicked()
{
    ui->MainWidget->setCurrentIndex(9);
}

void Dialog::on_pushButton_14_clicked()
{
    ui->MainWidget->setCurrentIndex(9);
}

void Dialog::on_pushButton_3_clicked()
{
    ui->MainWidget->setCurrentIndex(0);
}

void Dialog::on_SettingButton_clicked()
{
    ui->MainWidget->setCurrentIndex(3);
}

void Dialog::on_StartButton_clicked()
{
    ui->MainWidget->setCurrentIndex(4);
}

void Dialog::on_pushButton_4_clicked()
{
    ui->MainWidget->setCurrentIndex(4);
}

/**********************************************音量的转化*****************************************************************/

void Dialog::on_Audio_valueChanged(int value)
{
    player->setVolume(value);
}

/*********************************************Graph1数据的转化***********************************************************/

void Dialog::on_number_1_valueChanged(double arg1)
{
    int arg_1=arg1*10000;
    ui->horizontalSlider->setValue(arg_1);
}

void Dialog::on_number_2_valueChanged(double arg1)
{
    int arg_2=(arg1*100)/2;
    ui->horizontalSlider_2->setValue(arg_2);
}

void Dialog::on_number_3_valueChanged(double arg1)
{
    int arg_2=arg1*10000;
    ui->horizontalSlider_3->setValue(arg_2);
}

void Dialog::on_number_4_valueChanged(double arg1)
{
    int arg_2=(arg1*100)/2;
    ui->horizontalSlider_4->setValue(arg_2);
}

void Dialog::on_number_5_valueChanged(double arg1)
{
    int arg_2=arg1;
    ui->horizontalSlider_5->setValue(arg_2);
}

void Dialog::on_number_6_valueChanged(double arg1)
{
    int arg_2=arg1;
    ui->horizontalSlider_6->setValue(arg_2);
}

void Dialog::on_number_7_valueChanged(double arg1)
{
    int arg_2=arg1;
    ui->horizontalSlider_7->setValue(arg_2);
}

void Dialog::on_number_8_valueChanged(double arg1)
{
    int arg_2=arg1;
    ui->horizontalSlider_8->setValue(arg_2);
}

void Dialog::on_number_9_valueChanged(double arg1)
{
    int arg_2=arg1;
    ui->horizontalSlider_9->setValue(arg_2);
}

void Dialog::on_horizontalSlider_valueChanged(int value)
{
    double value_1=double(value);
    ui->number_1->setValue(value_1/10000);
}

void Dialog::on_horizontalSlider_2_valueChanged(int value)
{
    double value_2=double(value);
    ui->number_2->setValue((value_2*2)/100);
}

void Dialog::on_horizontalSlider_3_valueChanged(int value)
{
    double value_3=double(value);
    ui->number_3->setValue(value_3/10000);
}

void Dialog::on_horizontalSlider_4_valueChanged(int value)
{
    double value_2=double(value);
    ui->number_4->setValue((value_2*2)/100);
}

void Dialog::on_horizontalSlider_5_valueChanged(int value)
{
    double value_2=double(value);
    ui->number_5->setValue(value_2);
}

void Dialog::on_horizontalSlider_6_valueChanged(int value)
{
    double value_2=double(value);
    ui->number_6->setValue(value_2);
}

void Dialog::on_horizontalSlider_7_valueChanged(int value)
{
    double value_2=double(value);
    ui->number_7->setValue(value_2);
}

void Dialog::on_horizontalSlider_8_valueChanged(int value)
{
    double value_2=double(value);
    ui->number_8->setValue(value_2);
}

void Dialog::on_horizontalSlider_9_valueChanged(int value)
{
    double value_2=double(value);
    ui->number_9->setValue(value_2);
}

/**********************************************Graph3数据的转化**********************************************************/

void Dialog::on_verticalSlider_valueChanged(int value)
{
    double value_11=double(value);
    ui->number3_11->setValue(value_11);
}

void Dialog::on_horizontalSlider_10_valueChanged(int value)
{
    double value_1=double(value);
    ui->number3_1->setValue(value_1/10000);
}

void Dialog::on_horizontalSlider_11_valueChanged(int value)
{
    double value_2=double(value);
    ui->number3_2->setValue((value_2*2)/100);
}

void Dialog::on_horizontalSlider_12_valueChanged(int value)
{
    double value_3=double(value);
    ui->number3_3->setValue(value_3/10000);
}

void Dialog::on_horizontalSlider_13_valueChanged(int value)
{
    double value_4=double(value);
    ui->number3_4->setValue((value_4*2)/100);
}

void Dialog::on_horizontalSlider_14_valueChanged(int value)
{
    double value_5=double(value);
    ui->number3_5->setValue(value_5/10000);
}

void Dialog::on_horizontalSlider_15_valueChanged(int value)
{
    double value_6=double(value);
    ui->number3_6->setValue((value_6*2)/100);
}

void Dialog::on_horizontalSlider_16_valueChanged(int value)
{
    double value_7=double(value);
    ui->number3_7->setValue((value_7)/10);
}

void Dialog::on_horizontalSlider_17_valueChanged(int value)
{
    double value_8=double(value);
    ui->number3_8->setValue(value_8/10);
}

void Dialog::on_horizontalSlider_18_valueChanged(int value)
{
    double value_9=double(value);
    ui->number3_9->setValue(value_9/10);
}

void Dialog::on_horizontalSlider_19_valueChanged(int value)
{
    double value_10=double(value);
    ui->number3_10->setValue(value_10/10);
}

void Dialog::on_number3_1_valueChanged(double arg1)
{
    int arg_2=arg1*10000;
    ui->horizontalSlider_10->setValue(arg_2);
}

void Dialog::on_number3_2_valueChanged(double arg1)
{
    int arg_2=(arg1*100)/2;
    ui->horizontalSlider_11->setValue(arg_2);
}

void Dialog::on_number3_3_valueChanged(double arg1)
{
    int arg_2=arg1*10000;
    ui->horizontalSlider_12->setValue(arg_2);
}

void Dialog::on_number3_4_valueChanged(double arg1)
{
    int arg_2=(arg1*100)/2;
    ui->horizontalSlider_13->setValue(arg_2);
}

void Dialog::on_number3_5_valueChanged(double arg1)
{
    int arg_2=arg1*10000;
    ui->horizontalSlider_14->setValue(arg_2);
}

void Dialog::on_number3_6_valueChanged(double arg1)
{
    int arg_2=(arg1*100)/2;
    ui->horizontalSlider_15->setValue(arg_2);
}

void Dialog::on_number3_7_valueChanged(double arg1)
{
    int arg_2=(arg1*10);
    ui->horizontalSlider_16->setValue(arg_2);
}

void Dialog::on_number3_8_valueChanged(double arg1)
{
    int arg_2=(arg1*10);
    ui->horizontalSlider_17->setValue(arg_2);
}

void Dialog::on_number3_9_valueChanged(double arg1)
{
    int arg_2=(arg1*10);
    ui->horizontalSlider_18->setValue(arg_2);
}

void Dialog::on_number3_10_valueChanged(double arg1)
{
    int arg_2=(arg1*10);
    ui->horizontalSlider_19->setValue(arg_2);
}

void Dialog::on_number3_11_valueChanged(double arg1)
{
    int arg_2=arg1;
    ui->verticalSlider->setValue(arg_2);
}

/*****************************************************提示框的显示*************************************************************/

void Dialog::on_pushButton_5_pressed()
{
    Calculating->show();
}

void Dialog::on_pushButton_7_pressed()
{
    Calculating->show();
}

/*******************************************************数据的保存**************************************************************/

void Dialog::showsaving1()
{
    if(clicktimeone >= 1)
    {
        Saving->show();
    }
    else
    {
        Nothing->show();
    }
}

void Dialog::save1()
{
    if(clicktimeone>=1)
    {
    QApplication::setOverrideCursor(Qt::WaitCursor);
    int n=graph_one->get_n();
    double* y1=new double [n+1];
    double* y2=new double [n+1];
    double* y3=new double [n+1];
    double* y4=new double [n+1];

    for(int i=0 ;i<=n;i++)
    {
        y1[i]=graph_one->get_y1(i);
        y2[i]=graph_one->get_y2(i);
        y3[i]=graph_one->get_y3(i);
        y4[i]=graph_one->get_y4(i);
    }
    QFile file("theta1 of double pendulum.txt");
    QFile file2("omega1 of double pendulum.txt");
    QFile file3("theta2 of double pendulum.txt");
    QFile file4("omega2 of double pendulum.txt");
    QFile file5("parameters of double pendulum.txt");
    if (file2.open(QFile::ReadWrite | QIODevice::Truncate)|file.open(QFile::ReadWrite | QIODevice::Truncate)
        |file3.open(QFile::ReadWrite | QIODevice::Truncate)|file4.open(QFile::ReadWrite | QIODevice::Truncate)
            |file5.open(QFile::ReadWrite|QIODevice::Truncate))
    {
        QTextStream out(&file);
        QTextStream out2(&file2);
        QTextStream out3(&file3);
        QTextStream out4(&file4);
        QTextStream out5(&file5);
        for(int i=0 ;i<n;i++)
        {
            out<<y1[i]<<"\r\n";
            out2<<y2[i]<<"\r\n";
            out3<<y3[i]<<"\r\n";
            out4<<y4[i]<<"\r\n";
        }
        out5<<n<<"\r\n"<<graph_one->get_l1()<<"\r\n"<<graph_one->get_l2()<<"\r\n"<<graph_one->get_step_n();
        file.close();
        file2.close();
        file3.close();
        file4.close();
        file5.close();
        QApplication::restoreOverrideCursor();
    }
    }

}

void Dialog::showsaving2()
{
    if(clicktimetwo >=1)
    {
        Saving->show();
    }
    else
    {
        Nothing->show();
    }
}

void Dialog::save2()
{
    if(clicktimetwo>=1)
    {
    QApplication::setOverrideCursor(Qt::WaitCursor);
    int n=graph_three->get_n();
    double* y1_2=new double [n+1];
    double* y2_2=new double [n+1];
    double* y3_2=new double [n+1];
    double* y4_2=new double [n+1];
    double* y5_2=new double [n+1];
    double* y6_2=new double [n+1];
    for(int i=0 ;i<n;i++)
    {
        y1_2[i]=graph_three->get_y1(i);
        y2_2[i]=graph_three->get_y2(i);
        y3_2[i]=graph_three->get_y3(i);
        y4_2[i]=graph_three->get_y4(i);
        y5_2[i]=graph_three->get_y5(i);
        y6_2[i]=graph_three->get_y6(i);
    }
    QFile file_2("theta1 of triple pendulum.txt");
    QFile file2_2("omega1 of triple pendulum.txt");
    QFile file3_2("theta2 of triple pendulum.txt");
    QFile file4_2("omega2 of triple pendulum.txt");
    QFile file5_2("theta3 of triple pendulum.txt");
    QFile file6_2("omega3 of triple pendulum.txt");
    QFile file7_2("parameters of triple pendulum.txt");
    if (file2_2.open(QFile::ReadWrite | QIODevice::Truncate)|file_2.open(QFile::ReadWrite | QIODevice::Truncate)
        |file3_2.open(QFile::ReadWrite | QIODevice::Truncate)|file4_2.open(QFile::ReadWrite | QIODevice::Truncate)
            |file6_2.open(QFile::ReadWrite | QIODevice::Truncate)|file5_2.open(QFile::ReadWrite | QIODevice::Truncate)
            |file7_2.open(QFile::ReadWrite | QIODevice::Truncate))
    {
        QTextStream out(&file_2);
        QTextStream out2(&file2_2);
        QTextStream out3(&file3_2);
        QTextStream out4(&file4_2);
        QTextStream out5(&file5_2);
        QTextStream out6(&file6_2);
        QTextStream out7(&file7_2);
        for(int i=0 ;i<n;i++)
        {
            out<<y1_2[i]<<"\r\n";
            out2<<y2_2[i]<<"\r\n";
            out3<<y3_2[i]<<"\r\n";
            out4<<y4_2[i]<<"\r\n";
            out5<<y5_2[i]<<"\r\n";
            out6<<y6_2[i]<<"\r\n";
        }
        out7<<n<<"\r\n"<<graph_three->get_l1()<<"\r\n"<<graph_three->get_l2()<<"\r\n"
           <<graph_three->get_l3()<<"\r\n"<<graph_three->get_step_n();

        file_2.close();
        file2_2.close();
        file3_2.close();
        file4_2.close();
        file5_2.close();
        file6_2.close();
        file7_2.close();
    }
    QApplication::restoreOverrideCursor();
    }
}

/*************************************************load读取数据****************************************************************/

void Dialog::on_StartButton_4_pressed()
{
    Loading->show();
}

void Dialog::on_StartButton_4_clicked()//控制load的选项
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    bool d=ui->Double_2->isChecked();
    if(d)
    {
        QFile file("theta1 of double pendulum.txt");
        QFile file2("omega1 of double pendulum.txt");
        QFile file3("theta2 of double pendulum.txt");
        QFile file4("omega2 of double pendulum.txt");
        QFile file5("parameters of double pendulum.txt");
        int m[4];
        int i=0,j=0;
        if (file5.open(QFile::ReadWrite))
        {
            QTextStream in5(&file5);
            while(!in5.atEnd())
            {
                QString Str=in5.readLine();
                m[i]=Str.toDouble();
                i++;
            }
        }
        int n=int(m[0]);
        int step_n=int(m[3]);
        int l1=m[1],l2=m[2];
        double* y1=new double [n+1];
        double* y2=new double [n+1];
        double* y3=new double [n+1];
        double* y4=new double [n+1];
        if(file2.open(QFile::ReadWrite)|file.open(QFile::ReadWrite)
           |file3.open(QFile::ReadWrite)|file4.open(QFile::ReadWrite))
        {
            QTextStream in(&file);
            QTextStream in2(&file2);
            QTextStream in3(&file3);
            QTextStream in4(&file4);
            while(!in.atEnd())
            {
                QString Str1=in.readLine();
                y1[j]=Str1.toDouble();
                QString Str2=in2.readLine();
                y2[j]=Str2.toDouble();
                QString Str3=in3.readLine();
                y3[j]=Str3.toDouble();
                QString Str4=in4.readLine();
                y4[j]=Str4.toDouble();
                j++;
            }
        }
        graph_one_one= new Graph1_1(this);
        graph_one_two= new Graph1_2(this);
        graph_one_three= new Graph1_3(this);
        graph_load_one = new Graph1(this);

        graph_one_one->set_n(n+1);
        graph_one_one->set_y1_y2(y1,y2);
        graph_one_two->set_n(n+1);
        graph_one_two->set_y3_y4(y3,y4);
        graph_one_three->set_n(n+1);
        graph_one_three->set_y1_y3(y1,y3);

        graph_load_one->set_n(n);
        graph_load_one->set_step_n(step_n);
        graph_load_one->set_l1_l2(l1,l2,l1+l2);
        graph_load_one->set_y1_to_y4(y1,y2,y3,y4);
        if(loadtime>=1)
        {graph_load_one->set_h_time(90);}

        loadtime++;
        ui->MainWidget->setCurrentIndex(10);
    }
    if(!d)
    {
        QFile file_2("theta1 of triple pendulum.txt");
        QFile file2_2("omega1 of triple pendulum.txt");
        QFile file3_2("theta2 of triple pendulum.txt");
        QFile file4_2("omega2 of triple pendulum.txt");
        QFile file5_2("theta3 of triple pendulum.txt");
        QFile file6_2("omega3 of triple pendulum.txt");
        QFile file7_2("parameters of triple pendulum.txt");
        int m[5];
        int i=0,j=0;
        if (file7_2.open(QFile::ReadWrite))
        {
            QTextStream in7_2(&file7_2);
            while(!in7_2.atEnd())
            {
                QString Str=in7_2.readLine();
                m[i]=Str.toDouble();
                i++;
            }
        }
        int n=int(m[0]);
        int step_n=int(m[4]);
        int l1=m[1],l2=m[2],l3=m[3];
        double* y1=new double [n+1];
        double* y2=new double [n+1];
        double* y3=new double [n+1];
        double* y4=new double [n+1];
        double* y5=new double [n+1];
        double* y6=new double [n+1];
        if(file2_2.open(QFile::ReadWrite)|file_2.open(QFile::ReadWrite)
           |file3_2.open(QFile::ReadWrite)|file4_2.open(QFile::ReadWrite)
            |file5_2.open(QFile::ReadWrite)|file6_2.open(QFile::ReadWrite))
        {
            QTextStream in_2(&file_2);
            QTextStream in2_2(&file2_2);
            QTextStream in3_2(&file3_2);
            QTextStream in4_2(&file4_2);
            QTextStream in5_2(&file5_2);
            QTextStream in6_2(&file6_2);
            while(!in_2.atEnd())
            {
                QString Str1_2=in_2.readLine();
                y1[j]=Str1_2.toDouble();
                QString Str2_2=in2_2.readLine();
                y2[j]=Str2_2.toDouble();
                QString Str3_2=in3_2.readLine();
                y3[j]=Str3_2.toDouble();
                QString Str4_2=in4_2.readLine();
                y4[j]=Str4_2.toDouble();
                QString Str5_2=in5_2.readLine();
                y5[j]=Str5_2.toDouble();
                QString Str6_2=in6_2.readLine();
                y6[j]=Str6_2.toDouble();
                j++;
            }
        }

        graph_three_one= new Graph3_1(this);
        graph_three_two= new Graph3_2(this);
        graph_three_three= new Graph3_3(this);
        graph_load_three = new Graph3(this);

        graph_three_one->set_n(n+1);
        graph_three_one->set_y1_y2(y1,y2);
        graph_three_two->set_n(n+1);
        graph_three_two->set_y3_y4(y3,y4);
        graph_three_three->set_n(n+1);
        graph_three_three->set_y5_y6(y5,y6);

        graph_load_three->set_n(n);
        graph_load_three->set_step_n(step_n);
        graph_load_three->set_l1_l3(l1,l2,l3,l1+l2+l3);
        graph_load_three->set_y1_to_y6(y1,y2,y3,y4,y5,y6);
        Loading->hide();
        ui->MainWidget->setCurrentIndex(11);
    }
    QApplication::restoreOverrideCursor();
}

/**************************************************最后的选择*****************************************************************/

void Dialog::on_pushButton_12_clicked()
{
    graph_load_one->setGeometry(50,50,950,950);
    graph_one_one->setGeometry(1050,50,400,400);
    graph_one_two->setGeometry(1050,500,400,400);
    graph_one_three->setGeometry(1500,500,400,400);
    graph_load_one->setTitle("Animate");
    graph_one_one->setTitle(tr("θ1~ω1"));
    graph_one_two->setTitle(tr("θ2~ω2"));
    graph_one_three->setTitle(tr("θ1~θ2"));
    bool animate=ui->checkBox_10->isChecked();
    bool phase_one=ui->checkBox_12->isChecked();
    bool phase_two=ui->checkBox_11->isChecked();
    bool phase_three=ui->checkBox_13->isChecked();
    if(animate)
    {
        graph_load_one->BeginAnimate();
        graph_load_one->show();
    }
    if(phase_one){graph_one_one->show();}
    if(phase_two){graph_one_two->show();}
    if(phase_three){graph_one_three->show();}
}

void Dialog::on_pushButton_15_clicked()
{
    graph_load_three->setGeometry(50,50,950,950);
    graph_three_one->setGeometry(1050,50,400,400);
    graph_three_two->setGeometry(1050,500,400,400);
    graph_three_three->setGeometry(1500,500,400,400);
    graph_load_three->setTitle("Animate");
    graph_three_one->setTitle(tr("θ1~ω1"));
    graph_three_two->setTitle(tr("θ2~ω2"));
    graph_three_three->setTitle(tr("θ1~θ2"));
    bool animate=ui->checkBox_14->isChecked();
    bool phase_one=ui->checkBox_15->isChecked();
    bool phase_two=ui->checkBox_16->isChecked();
    bool phase_three=ui->checkBox_17->isChecked();
    if(animate)
    {
        graph_load_three->BeginAnimate();
        graph_load_three->show();
    }
    if(phase_one){graph_three_one->show();}
    if(phase_two){graph_three_two->show();}
    if(phase_three){graph_three_three->show();}
}

/***************************************************************一些小bug的修复*******************************************************/

void Dialog::on_Double_2_released()
{

    bool double_2=ui->Double_2->isChecked();
    bool triple_2=ui->Triple_2->isChecked();
    if(!double_2&&!triple_2)
    {
        ui->StartButton_4->setEnabled(false);
    }
    else
    {
        ui->StartButton_4->setEnabled(true);
    }
}

void Dialog::on_Triple_2_released()
{

    bool double_2=ui->Double_2->isChecked();
    bool triple_2=ui->Triple_2->isChecked();
    if(!double_2&&!triple_2)
    {
        ui->StartButton_4->setEnabled(false);
    }
    else
    {
        ui->StartButton_4->setEnabled(true);
    }
}

void Dialog::on_Double_released()
{
    bool double_1=ui->Double->isChecked();
    bool triple_1=ui->Triple->isChecked();
    if(!double_1&&!triple_1)
    {
        ui->StartButton_2->setEnabled(false);
    }
    else
    {
        ui->StartButton_2->setEnabled(true);
    }
}

void Dialog::on_Triple_released()
{
    bool double_1=ui->Double->isChecked();
    bool triple_1=ui->Triple->isChecked();
    if(!double_1&&!triple_1)
    {
        ui->StartButton_2->setEnabled(false);
    }
    else
    {
        ui->StartButton_2->setEnabled(true);
    }
}
