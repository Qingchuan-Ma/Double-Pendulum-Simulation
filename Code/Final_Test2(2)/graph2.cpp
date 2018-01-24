#include "graph2.h"
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

Graph2::Graph2(QWidget* parent)
    :QGLWidget(parent)
{
    initializeGL();
    yposition1[0]=5;
    yposition2[0]=-10;
    step_n=0;
}

void Graph2::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClearDepth(1.0);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
void Graph2::set_step_n(int k)
{
    step_n=k;
}

void Graph2::BeginAnimate()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    timer->start(1);
}

void Graph2::updateAnimation()
{
step_n +=1;
if( step_n >=n_graph2)         step_n= 0;
this->update();
}

void Graph2::set_y1_to_y4(double* output_y_1, double *output_y_2, double *output_y_3, double *output_y_4)
{

    y1= new double [n_graph2+1];
    y2= new double [n_graph2+1];
    y3= new double [n_graph2+1];
    y4= new double [n_graph2+1];
    for(int i=step_n;i<=n_graph2;i++)
    {
        y1[i]=output_y_1[i-step_n];
    }
    for(int i=step_n;i<=n_graph2;i++)
    {
        y2[i]=output_y_2[i-step_n];
    }
    for(int i=step_n;i<=n_graph2;i++)
    {
        y3[i]=output_y_3[i-step_n];
    }
    for(int i=step_n;i<=n_graph2;i++)
    {
        y4[i]=output_y_4[i-step_n];
    }
    for(int i=step_n;i<=n_graph2;i++)
    {
        xposition1[i]=l1*sin(y1[i]);
    }
    for(int i=step_n;i<=n_graph2;i++){
        yposition1[i]=20-l1*cos(y1[i]);
    }
    for(int i=step_n;i<=n_graph2;i++){
        xposition2[i]=l1*sin(y1[i])+l2*sin(y3[i]);
    }
    for(int i=step_n;i<=n_graph2;i++){
        yposition2[i]=20-l1*cos(y1[i])-l2*cos(y3[i]);
    }
}

void Graph2::paintGL()
{
    float emission[4]={(float)32/255, (float)1/255, (float)172/255, 1.0f};
    float ambient[4]={(float)24/255, (float)205/255, (float)176/255, 1.0f};
    float diffuse[4]={(float)24/255, (float)205/255, (float)176/255, 1.0f};
    float specular[4]={1.0f, 1.0f, 1.0f, 1.0f};

    float emission1[4]={(float)131/255, (float)27/255, (float)28/255, 1.0f};
    float ambient1[4]={(float)223/255, (float)35/255, (float)35/255, 1.0f};
    float diffuse1[4]={(float)223/255, (float)35/255, (float)35/255, 1.0f};
    float specular1[4]={1.0f, 1.0f, 1.0f, 1.0f};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       //初始化
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, 1.0f, 1000.0f, 20.0f);
    //设置视角
    //glTranslatef(moveX, moveY, moveZ);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, -25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//请修改第三个数，使time-300的终值约为50

    // 定义光源，它是一种白色的光源
        GLfloat sun_light_position[] = {20.0f, 20.0f, 20.0f, 0.0f};
        GLfloat sun_light_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
        GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT,  sun_light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  sun_light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);

    myball.zposition=0;
    myball.ambient=&ambient;
    myball.diffuse=&diffuse;
    myball.specular=&specular;
    myball.emission=&emission;
    myball.shininess=30;
    myball.radius=2;

    myball_2.zposition=0;
    myball_2.ambient=&ambient1;
    myball_2.diffuse=&diffuse1;
    myball_2.specular=&specular1;
    myball_2.emission=&emission1;
    myball_2.shininess=30;
    myball_2.radius=2;

    glTranslatef(xposition1[step_n],yposition1[step_n],myball.zposition);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   *myball.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   *myball.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  *myball.specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  *myball.emission);
    glMaterialf (GL_FRONT, GL_SHININESS, myball.shininess);
    glutSolidSphere(myball.radius, 32, 32);
    glTranslatef(-xposition1[step_n],-yposition1[step_n],-myball.zposition);//复位

    glTranslatef(xposition2[step_n],yposition2[step_n],myball_2.zposition);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   *myball_2.ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   *myball_2.diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  *myball_2.specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  *myball_2.emission);
    glMaterialf (GL_FRONT, GL_SHININESS, myball_2.shininess);
    glutSolidSphere(myball_2.radius, 32, 32);
    glTranslatef(-xposition2[step_n],-yposition2[step_n],-myball_2.zposition);//复位

glDisable(GL_LIGHTING);
glLineWidth(4);
glBegin(GL_LINES);
    glVertex2f(0, 20);
    glColor4f(0.0f, 0.0f, 0.0f,1.0f);
    glVertex2f(xposition1[step_n],yposition1[step_n]);
glEnd();
glBegin(GL_LINES);
    glVertex2f(xposition1[step_n], yposition1[step_n]);
    glColor4f(0.0f, 0.0f, 0.0f,1.0f);
    glVertex2f(xposition2[step_n],yposition2[step_n]);
glEnd();
glDisable(GL_LIGHTING);
glFlush();
}

void Graph2::resizeGL(int width, int height)
{
    if(0 == height)
    {
        height = 1;
    }
    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLdouble aspectRatio = (GLfloat)width/(GLfloat)height;
    GLdouble zNear = 0.1;
    GLdouble zFar = 100.0;
    GLdouble rFov = 45.0 * 3.14159265 / 180.0;
     glFrustum( -zNear * tan( rFov / 2.0 ) * aspectRatio,
               zNear * tan( rFov / 2.0 ) * aspectRatio,
               -zNear * tan( rFov / 2.0 ),
               zNear * tan( rFov / 2.0 ),
               zNear, zFar );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graph2::StopAnimate()
{
    timer->stop();
    this->update();
}

void Graph2::transmitposition1(int x,int y)
{
    double x1=double(x);
    double y1=double(y);
    xposition1[step_n]=-(x1-260)/10;
    yposition1[step_n]=-(y1-260)/10;
    this->update();
}
void Graph2::transmitposition2(int x,int y)
{
    double x1=double(x);
    double y1=double(y);
    xposition2[step_n]=-(x1-260)/10;
    yposition2[step_n]=-(y1-260)/10;
    this->update();
}
void Graph2::reset()
{
    if(timer->isActive())
    {timer->stop();}
    step_n=0;
    xposition1[0]=0;
    xposition2[0]=0;
    yposition1[0]=5;
    yposition2[0]=-10;
    this->update();
}
