#ifndef GRAPH3_H
#define GRAPH3_H
#include <QOpenGLWindow>
#include <QMainWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <glut.h>
#include <QTimer>
#include <QGLWidget>
#include <cmath>
#include <QEvent>

struct ball3{

    float zposition;
    float radius;
    float (*ambient)[4];//很多次反射后最终遗留在环境中的光线强度（颜色），AMBIENT和DIFFUSE都取相同的值，可以达到比较真实的效果。
    float (*diffuse)[4];//漫反射后形成的光线强度（颜色）
    float (*specular)[4];//镜面反射后形成的光线强度（颜色）
    float (*emission)[4];//底色
    float shininess;//“镜面指数”，取值范围是0到128。该值越小，表示材质越粗糙
};

class Graph3: public QOpenGLWindow
{
Q_OBJECT
public:
explicit Graph3(QWidget *parent = 0);
~Graph3();
    void set_n(int n){n_graph1=n;}
    void set_y1_to_y6(double *output_y_1,double *output_y_2,double *output_y_3,double *output_y_4,double *output_y_5,double *output_y_6);
    void BeginAnimate();
    void set_l1_l3(double l_1, double l_2, double l_3, double l_);
    void set_step_n(int n ){ step_n=n;}
    int get_n(){return n_graph1;}
    double get_y1(int i){return y1[i];}
    double get_y2(int i){return y2[i];}
    double get_y3(int i){return y3[i];}
    double get_y4(int i){return y4[i];}
    double get_y5(int i){return y5[i];}
    double get_y6(int i){return y6[i];}
    double get_l1(){return l1;}
    double get_l2(){return l2;}
    double get_l3(){return l3;}
    int get_step_n(){return step_n;}

protected:
void keyPressEvent(QKeyEvent *event);
virtual void initializeGL();
virtual void resizeGL(int w, int h);
virtual void paintGL();
void paintEvent(QPaintEvent *event);
void resizeEvent(QResizeEvent *event);

private:
QEvent *event;
QTimer *timer;
QOpenGLContext* context;
QOpenGLFunctions* openGLFunctions;
int n_graph1;
double *y1;
double *y2;
double *y3;
double *y4;
double *y5;
double *y6;
int step_n;
double *xposition0;
double *yposition0;
double *xposition1;
double *yposition1;
double *xposition2;
double *yposition2;
double *xposition3;
double *yposition3;
double l1;
double l2;
double l3;
double l;
ball3 myball;
ball3 myball_2;
ball3 myball_3;
int h_time;

public slots:
void updateAnimation();
};
#endif // GRAPH3_H
