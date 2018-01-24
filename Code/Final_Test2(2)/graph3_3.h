#ifndef GRAPH3_3_H
#define GRAPH3_3_H
#include <QOpenGLWindow>
#include <QMainWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/glu.h>
#include <QGLWidget>

class Graph3_3 : public QOpenGLWindow
{
    Q_OBJECT
    public:
    explicit Graph3_3(QWidget *parent = 0);
    ~Graph3_3();
    void set_n(int n){n_graph3_3=n;}
    void set_y5_y6(double *output_y_5,double *output_y_6);
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
int n_graph3_3;
double *y5;
double *y6;
int j;
};
#endif // GRAPH3_3_H
