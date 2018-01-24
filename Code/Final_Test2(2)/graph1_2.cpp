#include "graph1_2.h"

Graph1_2::Graph1_2(QWidget *parent)
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
    moveX = 0;
    moveY = 0;
    moveZ = -8;
    j=0;
}

Graph1_2::~Graph1_2()
{

}

void Graph1_2::set_y3_y4(double *output_y_3, double *output_y_4)
{
    y3= new double [n_graph1_2+1];
    y4= new double [n_graph1_2+1];
    for(int i=0;i<=n_graph1_2;i++)
    {
        y3[i]=output_y_3[i];
    }
    for(int i=0;i<=n_graph1_2;i++)
    {
        y4[i]=output_y_4[i];
    }
}

void Graph1_2::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    resizeGL(this->width(), this->height());
}

void Graph1_2::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    qreal aspectRatio = qreal(w) / qreal(h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1 * aspectRatio, 1 * aspectRatio, -1, 1, 1, -1);
    gluPerspective(75, aspectRatio, 0.1, 400000000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Graph1_2::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(moveX, moveY, moveZ);

    glBegin(GL_POINTS);
    for(int i=0;i<n_graph1_2;i++)
    {
        glVertex3f(2.5*y3[i],0.5*y4[i],-3);
    }
    glEnd();
    //画点
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex3f(0.0,-100,-3);
        glVertex3f(0.0,100,-3);
    glEnd();
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex3f(-100,0.0,-3);
        glVertex3f(100,0.0,-3);
    glEnd();
    //画坐标轴

    for(double i=-500;i<=500;i++)
    {
        glLineWidth(0.05);
        glBegin(GL_LINES);
            glVertex3f(i/5,-j,-3);
            glVertex3f(i/5,j,-3);
        glEnd();
        glBegin(GL_LINES);
            glVertex3f(j,i/5,-3);
            glVertex3f(-j,i/5,-3);
        glEnd();
    }
    glFlush();
}

void Graph1_2::paintEvent(QPaintEvent *event)
{
    paintGL();
}

void Graph1_2::resizeEvent(QResizeEvent *event)
{
    resizeGL(this->width(), this->height());
    this->update();
}

void Graph1_2::keyPressEvent(QKeyEvent *f)
{
    static bool yes;
    if (f->key() == Qt::Key_W)
    {
        moveY -= 0.65;
    }
    if (f->key() == Qt::Key_S)
    {
        moveY += 0.65;
    }
    if (f->key() == Qt::Key_A)
    {
        moveX += 0.65;
    }
    if (f->key() == Qt::Key_D)
    {
        moveX -= 0.65;
    }
    if (f->key() == Qt::Key_Equal)
    {
        moveZ += 0.65;
    }
    if (f->key() == Qt::Key_Minus)
    {
        moveZ -= 0.65;
    }
    if (f->key() == Qt::Key_Escape)
    {
        this->close();
    }
    if(f->key() == Qt::Key_H)
    {
        yes=!yes;
        if(yes)
        {
            j=100;
        }
        else
        {
            j=0;
        }
    }
    if(f->key() == Qt::Key_R)
    {
        moveX=0;
        moveY=0;
        moveZ=-8;
    }
    this->update();
}
