#ifndef GRAPH1_3_H
#define GRAPH1_3_H
#include <QOpenGLWindow>
#include <QMainWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/glu.h>
#include <QGLWidget>

class Graph1_3 : public QOpenGLWindow
{
    Q_OBJECT

public:
    explicit Graph1_3(QWidget *parent = 0);
    ~Graph1_3();
    void set_n(int n){n_graph1_3=n;}
    void set_y1_y3(double *output_y_1, double *output_y_3);

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
    int n_graph1_3;
    double *y1;
    double *y3;
    int j;
};
#endif // GRAPH1_3_H
