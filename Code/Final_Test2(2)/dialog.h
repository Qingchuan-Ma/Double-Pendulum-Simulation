#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QMediaPlayer>
#include <QGridLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QMouseEvent>
#include "titlebar.h"
#include "calculatewidget.h"
#include "help.h"
#include "double_pendulum_culculate.h"
#include "triple_pendulum_culculate.h"
#include "graph1.h"
#include "graph1_1.h"
#include "graph1_2.h"
#include "graph1_3.h"
#include "graph2.h"
#include "graph3.h"
#include "graph3_1.h"
#include "graph3_2.h"
#include "graph3_3.h"
#include "graph4.h"
#include "fun.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Double_Pendulum_Culculate *double_pendulum;
    Triple_Pendulum_Culculate *triple_pendulum;
    Graph1 *graph_one;
    Graph1 *graph_load_one;
    Graph1_1 *graph_one_one;
    Graph1_2 *graph_one_two;
    Graph1_3 *graph_one_three;
    Graph2 *graph_two;
    Graph3 *graph_three;
    Graph3 *graph_load_three;
    Graph3_1 *graph_three_one;
    Graph3_2 *graph_three_two;
    Graph3_3 *graph_three_three;
    Graph4 *graph_four;
    CalculateWidget *Calculating;
    CalculateWidget *Saving;
    CalculateWidget *Nothing;
    CalculateWidget *Loading;
    Fun *fun;
    QPushButton *Run;
    QPushButton *Stop;
    QPushButton *Return;
    QPushButton *Reset;
    QLabel* mylabel1;
    QLabel* mylabel2;
    QLabel* mylabel3;
    QLabel* mylabel4;
    QLineEdit *mylineEdit1;
    QLineEdit *mylineEdit2;
    QLineEdit *mylineEdit3;
    QLineEdit *mylineEdit4;
    QSlider *myslider1;
    QSlider *myslider2;
    QSlider *myslider3;
    QSlider *myslider4;
    QPushButton *Run_2;
    QPushButton *Stop_2;
    QPushButton *Return_2;
    QPushButton *Reset_2;
    QPushButton *Some;
    QLabel* mylabel1_2;
    QLabel* mylabel2_2;
    QLabel* mylabel3_2;
    QLabel* mylabel4_2;
    QLabel* mylabel5_2;
    QLineEdit *mylineEdit1_2;
    QLineEdit *mylineEdit2_2;
    QLineEdit *mylineEdit3_2;
    QLineEdit *mylineEdit4_2;
    QLineEdit *mylineEdit5_2;
    QSlider *myslider1_2;
    QSlider *myslider2_2;
    QSlider *myslider3_2;
    QSlider *myslider4_2;
    QSlider *myslider5_2;
    Ui::Dialog *ui;
    QMediaPlayer *player;
    int clicktimeone;
    int clicktimetwo;
    int loadtime;


private slots:
    void mouseMoveEvent(QMouseEvent *e);
    void keyPressEvent( QKeyEvent *e );
    void closeEvent(QCloseEvent *event);
    void on_pushButton_3_clicked();
    void on_SettingButton_clicked();
    void on_StartButton_clicked();
    void on_pushButton_4_clicked();
    void on_StartButton_2_clicked();
    void on_StartButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_Audio_valueChanged(int value);
    void on_pushButton_6_clicked();
    void on_ContinueButton_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();
    void on_number_1_valueChanged(double arg1);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_number_3_valueChanged(double arg1);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_number_2_valueChanged(double arg1);
    void on_horizontalSlider_4_valueChanged(int value);
    void on_number_4_valueChanged(double arg1);
    void on_horizontalSlider_5_valueChanged(int value);
    void on_horizontalSlider_6_valueChanged(int value);
    void on_number_5_valueChanged(double arg1);
    void on_number_6_valueChanged(double arg1);
    void on_horizontalSlider_7_valueChanged(int value);
    void on_horizontalSlider_8_valueChanged(int value);
    void on_horizontalSlider_9_valueChanged(int value);
    void on_number_7_valueChanged(double arg1);
    void on_number_8_valueChanged(double arg1);
    void on_number_9_valueChanged(double arg1);
    void on_pushButton_7_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();

    void Return_clicked();
    void Run_clicked();
    void Reset_clicked();
    void transmit();
    void Stop_clicked();
    void Run_pressed();
    void Run_released();

    void Return_2_clicked();
    void Run_2_clicked();
    void transmit_2();
    void Stop_2_clicked();
    void Reset_2_clicked();
    void Run_2_pressed();
    void Some_clicked();
    void Run_2_released();

    void on_horizontalSlider_10_valueChanged(int value);
    void on_horizontalSlider_12_valueChanged(int value);
    void on_horizontalSlider_14_valueChanged(int value);
    void on_horizontalSlider_11_valueChanged(int value);
    void on_horizontalSlider_13_valueChanged(int value);
    void on_horizontalSlider_15_valueChanged(int value);
    void on_horizontalSlider_16_valueChanged(int value);
    void on_horizontalSlider_17_valueChanged(int value);
    void on_horizontalSlider_18_valueChanged(int value);
    void on_horizontalSlider_19_valueChanged(int value);
    void on_verticalSlider_valueChanged(int value);
    void on_number3_1_valueChanged(double arg1);
    void on_number3_2_valueChanged(double arg1);
    void on_number3_3_valueChanged(double arg1);
    void on_number3_4_valueChanged(double arg1);
    void on_number3_5_valueChanged(double arg1);
    void on_number3_6_valueChanged(double arg1);
    void on_number3_7_valueChanged(double arg1);
    void on_number3_8_valueChanged(double arg1);
    void on_number3_9_valueChanged(double arg1);
    void on_number3_10_valueChanged(double arg1);
    void on_number3_11_valueChanged(double arg1);
    void on_StartButton_4_clicked();
    void on_StartButton_5_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_5_pressed();
    void on_pushButton_7_pressed();
    void save1();
    void save2();
    void showsaving1();
    void showsaving2();
    void on_pushButton_15_clicked();
    void on_pushButton_12_clicked();
    void on_StartButton_4_pressed();
    void on_Double_2_released();
    void on_Triple_2_released();
    void on_Double_released();
    void on_Triple_released();
};

#endif // DIALOG_H
