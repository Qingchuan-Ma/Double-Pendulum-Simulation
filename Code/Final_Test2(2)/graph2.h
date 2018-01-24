#ifndef GRAPH2_H
#define GRAPH2_H
#include <QtOpenGL>
#include <QtOpenGL>
#include <glut.h>

struct ball2{
    float zposition;
    float radius;
    float (*ambient)[4];//很多次反射后最终遗留在环境中的光线强度（颜色），AMBIENT和DIFFUSE都取相同的值，可以达到比较真实的效果。
    float (*diffuse)[4];//漫反射后形成的光线强度（颜色）
    float (*specular)[4];//镜面反射后形成的光线强度（颜色）
    float (*emission)[4];//底色
    float shininess;//“镜面指数”，取值范围是0到128。该值越小，表示材质越粗糙
};

class Graph2 : public QGLWidget
{
    Q_OBJECT

public:
    Graph2(QWidget* parent = 0);
    //void transmit(float movex,float movey,float movez){moveX=movex;moveY=movey;moveZ=movez;this->update();}
    void transmitposition1(int x, int y);
    void set_y1_to_y4(double *output_y_1,double *output_y_2,double *output_y_3,double *output_y_4);
    void transmitposition2(int x, int y);
    void BeginAnimate();
    void set_n(int n){n_graph2=n;}
    void set_l1_l2(double l_1, double l_2){l1=l_1;l2=l_2;}
    double xposition1[200010];
    double yposition1[200010];
    double xposition2[200010];
    double yposition2[200010];
    void StopAnimate();
    int get_step_n(){int n=step_n;return n;}
    void set_step_n(int k);
    void reset();
protected:
  void initializeGL();
  void paintGL();
  void resizeGL(int width, int height);

private:
  QTimer *timer;
 /* float moveX;
  float moveZ;
  float moveY;*/
  ball2 myball;
  ball2 myball_2;
  double l1;
  double l2;
  int step_n;
  int n_graph2;
  double *y1;
  double *y2;
  double *y3;
  double *y4;

public slots:
void updateAnimation();
};


#endif // GRAPH2_H
