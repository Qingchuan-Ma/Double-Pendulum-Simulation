#ifndef GRAPH1_1_H
#define GRAPH1_1_H
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>

class Graph1_1:public QOpenGLWindow
{
    Q_OBJECT

public:
    explicit Graph1_1(QWidget *parent = 0);
    ~Graph1_1();
    void set_n(int n){n_graph1_1=n;}
    void set_y1_y2(double *output_y_1, double *output_y_2);

protected:
    void keyPressEvent(QKeyEvent *f);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    QOpenGLContext* context;
    QOpenGLFunctions* openGLFunctions;

private:
    float moveX;
    float moveZ;
    float moveY;
    int n_graph1_1;
    double *y1;
    double *y2;
    int j;
};

#endif // GRAPH1_1_H
