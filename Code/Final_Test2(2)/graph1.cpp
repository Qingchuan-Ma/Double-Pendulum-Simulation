#include "graph1.h"
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
GLUquadricObj* disk;
GLuint m_listbox;

/*float angel = 0,Z_leave = 0;
GLUquadricObj* disk;
GLuint m_listbox;//显示列表的标号
//--------------贴图自定义函数---------------------------------------//
GLuint g_bitmap[2];//纹理对应的编号 定义纹理的映射个数
unsigned  char *LoadBMP(const char *path,int &width,int &height)
{
    unsigned char *imagedate = NULL;
    FILE *pFile = fopen(path,"rb");
    if(pFile)
    {
        BITMAPFILEHEADER bfh;
        fread(&bfh,sizeof(BITMAPFILEHEADER),1,pFile);
        if(bfh.bfType=0x4d42)
        {
            BITMAPINFOHEADER bih;
            fread(&bih,sizeof(BITMAPINFOHEADER),1,pFile);
            width = bih.biWidth;
            height = bih.biHeight;
            imagedate = new unsigned char[width*height*3];
            fseek(pFile,bfh.bfOffBits,SEEK_SET);

            fread(imagedate,1,width*height*3,pFile);
            fclose(pFile);
        }
    }
    return  imagedate;
}
bool  LoadGLTextures1( char *filename,GLuint &texture)	//加载位图文件
{
    int imageWidth,imageHeight;
    unsigned char * imageDate = LoadBMP(filename,imageWidth,imageHeight);
    glGenTextures(1, &texture); //生成贴图
    glBindTexture(GL_TEXTURE_2D, texture); //贴图生效
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //缩小时线性滤波
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR); //扩大时线性滤波
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,imageWidth,imageHeight,0,GL_RGB ,GL_UNSIGNED_BYTE,imageDate);
    //gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imageWidth, imageHeight, GL_RGB, GL_UNSIGNED_BYTE, imageDate); //贴图数据
    return true;
}
void  LoadTextMap(void) //加载图
{
    LoadGLTextures1("Loading.bmp", g_bitmap[0]);//加载第一个图
    LoadGLTextures1("Completed.bmp", g_bitmap[1]);//加载第二个图

}

//----------------------------------------------------------------------------------------------//
void DrawLoading()
{
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glRotatef(180,1.0,0.0,0.0);
    glScalef(0.03,0.03,1.0);
    glEnable(GL_TEXTURE_2D);//---------------------------启动纹理
    //qian
    glBindTexture(GL_TEXTURE_2D, g_bitmap[0]);//---------对纹理进行绑定 不能放在glbegin() 和glend()之前 ，否则多次加载无限
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,1.0); glVertex3f(-10.0f,-5.0f,-10.0f);//纹理坐标映射
    glTexCoord2f(1.0,1.0); glVertex3f(10.0f,-5.0f,-10.0f);//纹理坐标映射
    glTexCoord2f(1.0,0.0); glVertex3f(10.0f,5.0f,-10.0f);//纹理坐标映射
    glTexCoord2f(0.0,0.0); glVertex3f(-10.0f,5.0f,-10.0f);//纹理坐标映射
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void DrawComplete()
{
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glRotatef(angel,0.0f,1.0f,0.0f);


    glRotatef(180,1.0,0.0,0.0);
    glScalef(0.03,0.03,1.0);
//	glTranslatef(0.0,0.0,0.05);
    glEnable(GL_TEXTURE_2D);//---------------------------启动纹理
    //qian
    glBindTexture(GL_TEXTURE_2D, g_bitmap[1]);//---------对纹理进行绑定 不能放在glbegin() 和glend()之前 ，否则多次加载无限
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.9); glVertex3f(-5.0f,-5.0f,-1.0f);//纹理坐标映射
    glTexCoord2f(0.9,0.9); glVertex3f(5.0f,-5.0f,-1.0f);//纹理坐标映射
    glTexCoord2f(0.9,0.0); glVertex3f(5.0f,5.0f,-1.0f);//纹理坐标映射
    glTexCoord2f(0.0,0.0); glVertex3f(-5.0f,5.0f,-1.0f);//纹理坐标映射
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}*/

struct Cylinder
{
    float color[3];//圆柱颜色
    float pos[3];//圆柱位置
    float vel[3];//圆柱来的速度
    float Max_vel;//圆柱最大的速度
    float angle;//圆柱的角度
    float zbuttom;//圆柱停靠的位置
    int polyMode;//填充方式
    Cylinder()
    {
        Max_vel = 0.01f;
        polyMode = 1;
        color[0] = (float)rand() / (float)RAND_MAX;//颜色随机
        color[1] = (float)rand() / (float)RAND_MAX;
        color[2] = (float)rand() / (float)RAND_MAX;

        pos[0] = 5 - 10 * (float)rand() / (float)RAND_MAX;//设置圆柱位置
        pos[1] = 5 - 10 * (float)rand() / (float)RAND_MAX;
        if ((float)rand() / (float)RAND_MAX<0.1)
            pos[2] = -100;
        else  //if((float)rand()/(float)RAND_MAX>0.3)
            pos[2] = -150;

        vel[0] = 0;//Max_vel*(0.5f-(float)rand()/(float)RAND_MAX);//设置速度
        vel[1] = 0;//Max_vel*(float)rand()/(float)RAND_MAX;
        vel[2] = 20.0;//设置圆柱来的速度

        zbuttom = 100.0f;//设置圆柱停靠的位置

        angle = 0.0f;//60.0f*(float)rand()/(float)RAND_MAX;
    }

    void Update(float delta)//刷新
    {
        if (pos[2]<zbuttom)//当圆柱z值是zbuttom 就不进行刷新
        {
            pos[0] += 0;// vel[0]*delta;//速度乘以时间
            pos[1] += 0;//vel[1]*delta;
            pos[2] += vel[2]*0.7 ;
        }
    }

    void Draw()//绘制圆柱
    {

        glPushMatrix();
        glColor3f(color[0], color[1], color[2]);
        glTranslatef(pos[0], pos[1], pos[2]);//圆柱绘制的位置
        glRotatef(angle, 0.0f, 0.0f, 1.0f);//圆柱绘制的角度
        glCallList(m_listbox);//绘制圆柱
        glPopMatrix();
    }

};

int  many_Cylinder = 30;//显示圆柱的个数
Cylinder m_Cylinder[30];

Graph1::Graph1(QWidget *parent)
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
    h_time=0;
}

Graph1::~Graph1()
{
    timer->stop();
}

void Graph1::BeginAnimate()
{
    timer->start(1);
}

void DrawCylinder()//绘制圆柱
{
    m_listbox = glGenLists(1);  //------------------------------申请一个显示列表
    glNewList(m_listbox, GL_COMPILE);  // -----------------------------创建显示列表
    glPushMatrix();
    gluCylinder(disk, 0.1f, 0.1f, 30.0f, 500, 500);
    glPopMatrix();
    glEndList();//--------------------------------------------结束
}

void Graph1::set_l1_l2(double l_1, double l_2, double l_)
{
    l1=l_1;
    l2=l_2;
    l=l_;
}

void Graph1::set_y1_to_y4(double* output_y_1, double *output_y_2, double *output_y_3, double *output_y_4)
{
    double length=50/l;
    y1= new double [n_graph1+1];
    y2= new double [n_graph1+1];
    y3= new double [n_graph1+1];
    y4= new double [n_graph1+1];
    xposition0= new double [n_graph1+1];
    yposition0= new double [n_graph1+1];
    xposition1= new double [n_graph1+1];
    yposition1= new double [n_graph1+1];
    xposition2= new double [n_graph1+1];
    yposition2= new double [n_graph1+1];
    for(int i=0;i<=n_graph1;i++)
    {
        xposition0[i]=0;
    }
    for(int i=0;i<=n_graph1;i++)
    {
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
        xposition1[i]=length*l1*sin(y1[i]);
    }
    for(int i=0;i<=n_graph1;i++)
    {
        yposition1[i]=yposition0[1]-length*l1*cos(y1[i]);
    }
    for(int i=0;i<=n_graph1;i++)
    {
        xposition2[i]=length*l1*sin(y1[i])+length*l2*sin(y3[i]);
    }
    for(int i=0;i<=n_graph1;i++)
    {
        yposition2[i]=yposition0[1]-length*l1*cos(y1[i])-length*l2*cos(y3[i]);
    }
}

void Graph1::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    resizeGL(this->width(), this->height());
}

void Graph1::resizeGL(int w, int h)
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

void Graph1::paintGL()
{
    if(h_time<90)
    {
    disk =gluNewQuadric();
    DrawCylinder();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    glLoadIdentity();// Reset The Current Modelview Matrix
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//相机
    for (int i = 0; i<many_Cylinder; i++)
    {
        m_Cylinder[i].Draw();
        m_Cylinder[i].Update(0.0005);
    }
    }
    if(h_time>=90){
    float emission[4]={(float)32/255, (float)1/255, (float)172/255, 1.0f};
    float ambient[4]={(float)24/255, (float)205/255, (float)176/255, 1.0f};
    float diffuse[4]={(float)24/255, (float)205/255, (float)176/255, 1.0f};
    float specular[4]={1.0f, 1.0f, 1.0f, 1.0f};

    float emission1[4]={(float)131/255, (float)27/255, (float)28/255, 1.0f};
    float ambient1[4]={(float)223/255, (float)35/255, (float)35/255, 1.0f};
    float diffuse1[4]={(float)223/255, (float)35/255, (float)35/255, 1.0f};
    float specular1[4]={1.0f, 1.0f, 1.0f, 1.0f};

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(90.0f, 1.0f, 1000.0f, 20.0f);//设置视角
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(0.0, 0.0, -50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

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
     glEnable(GL_DEPTH_TEST);// 定义光源，它是一种白色的光源

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
         glColor4f(0.0f, 0.0f, 0.0f,1.0f);
         glVertex2f(xposition0[step_n], yposition0[step_n]);
         glColor4f(0.0f, 0.0f, 0.0f,1.0f);
         glVertex2f(xposition1[step_n],yposition1[step_n]);
     glEnd();
     glBegin(GL_LINES);
         glColor4f(0.0f, 0.0f, 0.0f,1.0f);
         glVertex2f(xposition1[step_n], yposition1[step_n]);
         glColor4f(0.0f, 0.0f, 0.0f,1.0f);
         glVertex2f(xposition2[step_n],yposition2[step_n]);
     glEnd();
     glDisable(GL_LIGHTING);

     glPointSize(2);
     glColor4f(0.0f, 0.0f, 0.0f,1.0f);
     glBegin(GL_POINTS);
         for(int i=0;i<=step_n;i++)
         {
             glVertex2f(xposition2[step_n-i],yposition2[step_n-i]);
         }
     glEnd();
     glFlush();
     }
/*

     //glDisable(GL_LIGHTING);
     //glEnable(GL_BLEND);
     //glColor4f(0.0f, 0.0f, 0.0f, 0.5f);//颜色0.5 alpha值
     //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
     if(step_n<10)
     {
         for(int i=0;i<=step_n;i++)
         {
             glTranslatef(xposition1[step_n-i],yposition1[step_n-i],0);
             glColor4f((float)24/255, (float)205/255, (float)255/255,0.6-(float)i*0.05);
             gluSolidSphere(2, 32, 32);
             glTranslatef(-xposition1[step_n-i],-yposition1[step_n-i],0);
         }
     }
     if(step_n>=150)
     {
         for(int i=0;i<=10;i++){
             glTranslatef(xposition1[step_n-i],yposition1[step_n-i],0);
             glColor4f((float)24/255, (float)205/255, (float)255/255,0.6-(float)i*0.05);
             glutSolidSphere(2, 32, 32);
             glTranslatef(-xposition1[step_n-i],-yposition1[step_n-i],0);
         }
     }
     /*if(step_n<10)
     {
         for(int i=0;i<=step_n;i++)
         {
             glTranslatef(xposition2[step_n-i],yposition2[step_n-i],0);
             glColor4f((float)223/255, (float)35/255, (float)35/255,0.6-(float)i*0.05);
             glutSolidSphere(2, 32, 32);
             glTranslatef(-xposition2[step_n-i],-yposition2[step_n-i],0);
        }
     }
     if(step_n>=150)
     {
             for(int i=0;i<=10;i++)
             {
                 glTranslatef(xposition2[step_n-i],yposition2[step_n-i],0);
                 glColor4f((float)223/255, (float)35/255, (float)35/255,0.6-(float)i*0.05);
                 glutSolidSphere(2, 32, 32);
                 glTranslatef(-xposition2[step_n-i],-yposition2[step_n-i],0);
             }
     }
*/
}

void Graph1::paintEvent(QPaintEvent *event)
{
    paintGL();
}

void Graph1::resizeEvent(QResizeEvent *event)
{
    resizeGL(this->width(), this->height());
    this->update();
}

void Graph1::updateAnimation()
{
    h_time+=1;
    if(h_time>=90)
    {
        step_n += 1;
    if(step_n >= n_graph1)
    {
        step_n= 0;
    }
    }
    this->update();
}

void Graph1::keyPressEvent(QKeyEvent *event)
{
     if(event->key() == Qt::Key_Escape)
     {
         this->close();
     }
     if(event->key() == Qt::Key_S)
     {
         timer->stop();
     }
     if(event->key() == Qt::Key_C)
     {
         timer->start();
     }
}
