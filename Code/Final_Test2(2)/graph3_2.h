#ifndef GRAPH3_2_H
#define GRAPH3_2_H
#include <QOpenGLWindow>
#include <QMainWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/glu.h>
#include <QGLWidget>


class Graph3_2 : public QOpenGLWindow
{
    Q_OBJECT
    public:
    explicit Graph3_2(QWidget *parent = 0);
    ~Graph3_2();
    void set_n(int n){n_graph3_2=n;}
    void set_y3_y4(double *output_y_3,double *output_y_4);
protected:
void keyPressEvent(QKeyEvent *f);
virtual void initializeGL();
virtual void resizeGL(int w, int h);
virtual void paintGL();
void paintEvent(QPaintEvent *event);
void resizeEvent(QResizeEvent *event);
QOpenGLContext* context;
QOpenGLFunctions* openGLFunctions;
private:
float moveX;
float moveZ;
float moveY;
int n_graph3_2;
double *y3;
double *y4;
int j;
};

#endif // GRAPH3_2_H
