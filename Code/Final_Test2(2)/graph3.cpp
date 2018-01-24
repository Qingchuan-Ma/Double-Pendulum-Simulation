#include "graph3.h"
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

Graph3::Graph3(QWidget *parent)
{
    setSurfaceType(QWindow::OpenGLSurface);
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2, 1); // OpenGL 2.1
    setFormat(format);
    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);
    openGLFunctions = context->functions();
    step_n= 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    timer->stop();
}

Graph3::~Graph3()
{
    timer->stop();
}

void Graph3::BeginAnimate()
{
    timer->start(1);
}

void Graph3::set_l1_l3(double l_1, double l_2, double l_3,double l_)
{
    l1=l_1;
    l2=l_2;
    l3=l_3;
    l=l_;
}

void Graph3::set_y1_to_y6(double* output_y_1, double *output_y_2, double *output_y_3, double *output_y_4,double *output_y_5,double *output_y_6)
{
    double length=15;
    y1= new double [n_graph1+1];
    y2= new double [n_graph1+1];
    y3= new double [n_graph1+1];
    y4= new double [n_graph1+1];
    y5= new double [n_graph1+1];
    y6= new double [n_graph1+1];
    xposition0= new double [n_graph1+1];
    yposition0= new double [n_graph1+1];
    xposition1= new double [n_graph1+1];
    yposition1= new double [n_graph1+1];
    xposition2= new double [n_graph1+1];
    yposition2= new double [n_graph1+1];
    xposition3= new double [n_graph1+1];
    yposition3= new double [n_graph1+1];
    for(int i=0;i<=n_graph1;i++){
        xposition0[i]=0;
    }
    for(int i=0;i<=n_graph1;i++){
        yposition0[i]=30;
    }
    for(int i=0;i<=n_graph1;i++)
    {
        y1[i]=output_y_1[i];
    }
    for(int i=0;i<=n_graph1;i++)
    {
        y2[i]=output_y_2[i];
    }
    for(int i=0;i<=n_graph1;i++)
    {
        y3[i]=output_y_3[i];
    }
    for(int i=0;i<=n_graph1;i++)
    {
        y4[i]=output_y_4[i];
    }
    for(int i=0;i<=n_graph1;i++)
    {
        y5[i]=output_y_5[i];
    }
    for(int i=0;i<=n_graph1;i++)
    {
        y6[i]=output_y_6[i];
    }
    for(int i=0;i<=n_graph1;i++)
    {
        xposition1[i]=length*l1*sin(y1[i]);
    }
    for(int i=0;i<=n_graph1;i++){
        yposition1[i]=yposition0[1]-length*l1*cos(y1[i]);
    }
    for(int i=0;i<=n_graph1;i++){
        xposition2[i]=length*l1*sin(y1[i])+length*l2*sin(y3[i]);
    }
    for(int i=0;i<=n_graph1;i++){
        yposition2[i]=yposition0[1]-length*l1*cos(y1[i])-length*l2*cos(y3[i]);
    }
    for(int i=0;i<=n_graph1;i++){
        xposition3[i]=length*l1*sin(y1[i])+length*l2*sin(y3[i])+length*l3*sin(y5[i]);
    }
    for(int i=0;i<=n_graph1;i++){
        yposition3[i]=yposition0[1]-length*l1*cos(y1[i])-length*l2*cos(y3[i])-length*l3*cos(y5[i]);
    }
}

void Graph3::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    resizeGL(this->width(), this->height());
}

void Graph3::resizeGL(int w, int h)
{
    // Set the viewport
    glViewport(0, 0, w, h);
    qreal aspectRatio = qreal(w) / qreal(h);
    // Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1 * aspectRatio, 1 * aspectRatio, -1, 1, 1, -1);
    gluPerspective(75, aspectRatio, 0.1, 400000000);
    // Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graph3::paintGL()
{
    float emission[4]={(float)32/255, (float)1/255, (float)172/255, 1.0f};
    float ambient[4]={(float)24/255, (float)205/255, (float)176/255, 1.0f};
    float diffuse[4]={(float)24/255, (float)205/255, (float)176/255, 1.0f};
    float specular[4]={1.0f, 1.0f, 1.0f, 1.0f};

    float emission1[4]={(float)131/255, (float)27/255, (float)28/255, 1.0f};
    float ambient1[4]={(float)223/255, (float)35/255, (float)35/255, 1.0f};
    float diffuse1[4]={(float)223/255, (float)35/255, (float)35/255, 1.0f};
    float specular1[4]={1.0f, 1.0f, 1.0f, 1.0f};

    float emission2[4]={(float)191/255, (float)189/255, (float)0/255, 1.0f};
    float ambient2[4]={(float)255/255, (float)252/255, (float)0/255, 1.0f};
    float diffuse2[4]={(float)255/255, (float)252/255, (float)0/255, 1.0f};
    float specular2[4]={1.0f, 1.0f, 1.0f, 1.0f};


     //glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       //初始化
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(90.0f, 1.0f, 1000.0f, 20.0f);
     //设置视角
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(0.0, 0.0, -50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//请修改第三个数，使time-300的终值约为50
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

     myball_3.zposition=0;
     myball_3.ambient=&ambient2;
     myball_3.diffuse=&diffuse2;
     myball_3.specular=&specular2;
     myball_3.emission=&emission2;
     myball_3.shininess=30;
     myball_3.radius=2;

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


         glTranslatef(xposition3[step_n],yposition3[step_n],myball_3.zposition);
         glMaterialfv(GL_FRONT, GL_AMBIENT,   *myball_3.ambient);
         glMaterialfv(GL_FRONT, GL_DIFFUSE,   *myball_3.diffuse);
         glMaterialfv(GL_FRONT, GL_SPECULAR,  *myball_3.specular);
         glMaterialfv(GL_FRONT, GL_EMISSION,  *myball_3.emission);
         glMaterialf (GL_FRONT, GL_SHININESS, myball_3.shininess);
         glutSolidSphere(myball_3.radius, 32, 32);
         glTranslatef(-xposition3[step_n],-yposition3[step_n],-myball_3.zposition);//复位

     glDisable(GL_LIGHTING);
     glLineWidth(4);
     glBegin(GL_LINES);
         glVertex2f(xposition0[step_n], yposition0[step_n]);
         glColor4f(1.0f, 1.0f, 1.0f,1.0f);
         glVertex2f(xposition1[step_n],yposition1[step_n]);
     glEnd();
     glBegin(GL_LINES);
         glVertex2f(xposition1[step_n], yposition1[step_n]);
         glColor4f(1.0f, 1.0f, 1.0f,1.0f);
         glVertex2f(xposition2[step_n],yposition2[step_n]);
     glEnd();
     glBegin(GL_LINES);
         glVertex2f(xposition2[step_n], yposition2[step_n]);
         glColor4f(1.0f, 1.0f, 1.0f,1.0f);
         glVertex2f(xposition3[step_n],yposition3[step_n]);
     glEnd();
     glDisable(GL_LIGHTING);
     glPointSize(2);
     glColor4f(1.0f, 1.0f, 1.0f,1.0f);
     glBegin(GL_POINTS);
           for(int i=0;i<=step_n;i++)
           {
               glVertex2f(xposition2[step_n-i],yposition2[step_n-i]);

           }
         glEnd();
     glFlush();
}

void Graph3::paintEvent(QPaintEvent *event)
{
    paintGL();
}

void Graph3::resizeEvent(QResizeEvent *event)
{
    resizeGL(this->width(), this->height());
    this->update();
}

void Graph3::updateAnimation()
{
step_n +=1;
if( step_n >=n_graph1)         step_n= 0;
this->update();
}

void Graph3::keyPressEvent(QKeyEvent *event)
{
if (event->key() == Qt::Key_Escape)
{
this->close();
}
}
