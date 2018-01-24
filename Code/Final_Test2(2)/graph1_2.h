#ifndef GRAPH1_2_H
#define GRAPH1_2_H
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>

class Graph1_2 : public QOpenGLWindow
{
    Q_OBJECT

public:
    explicit Graph1_2(QWidget *parent = 0);
    ~Graph1_2();
    void set_n(int n){n_graph1_2=n;}
    void set_y3_y4(double *output_y_3, double *output_y_4);

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
    int n_graph1_2;
    double *y3;
    double *y4;
    int j;

};

#endif // GRAPH1_2_H
