#include "double_pendulum_culculate.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#define g 39.24
#define h 0.001
#define a_2 1.0/5.0
#define a_3 3.0/10.0
#define a_4 4.0/5.0
#define a_5 8.0/9.0
#define a_6 1.0
#define a_7 1.0
#define b_21 1.0/5.0
#define b_31 3.0/40.0
#define b_32 9.0/40.0
#define b_41 44.0/45.0
#define b_42 -56.0/15.0
#define b_43 32.0/9.0
#define b_51 19372.0/6561.0
#define b_52 -25360.0/2187.0
#define b_53 64448.0/6561.0
#define b_54 -212.0/729.0
#define b_61 9017.0/3168.0
#define b_62 -355.0/33.0
#define b_63 46732.0/5247.0
#define b_64 49.0/176.0
#define b_65 -5103.0/18656.0
#define b_71 35.0/384.0
#define b_72 0.0
#define b_73 500.0/1113.0
#define b_74 1250/192.0
#define b_75 -2187.0/6784.0
#define b_76 11.0/84.0
#define c_1 35.0/384.0
#define c_2 0.0
#define c_3 500.0/1113.0
#define c_4 125.0/192.0
#define c_5 -2187.0/6784.0
#define c_6 11.0/84.0
#define c_7 0.0

using namespace std;
Double_Pendulum_Culculate::Double_Pendulum_Culculate()
{

}
void Double_Pendulum_Culculate::set_begin_time(double input_begin_time)
{
    begin_time=input_begin_time;
    t=input_begin_time;
}
void Double_Pendulum_Culculate::set_last_time(double input_last_time)
{
    last_time=input_last_time;
}
void Double_Pendulum_Culculate::set_y_1_initial(double y_1_initial)
{
    y_1=y_1_initial;
}
void Double_Pendulum_Culculate::set_y_2_initial(double y_2_initial)
{
    y_2=y_2_initial;
}
void Double_Pendulum_Culculate::set_y_3_initial(double y_3_initial)
{
    y_3=y_3_initial;
}
void Double_Pendulum_Culculate::set_y_4_initial(double y_4_initial)
{
    y_4=y_4_initial;
}

void Double_Pendulum_Culculate::calculate_n()
{
    n=last_time/h;
}

void Double_Pendulum_Culculate::f(Double_Pendulum_Culculate pendulum, double t, PVector y, PVector output)
{
    output->x[0]=(y->x[1]);
    output->x[1]=(g*sin(y->x[2])*cos(y->x[0]-y->x[2])
            -sin(y->x[0]-y->x[2])*(pow(y->x[3],2)
            +l*pow(y->x[1],2)*cos(y->x[0]-y->x[2]))
            -(m+1)*g*sin(y->x[0]))
            /(m+1-pow(cos(y->x[0]-y->x[2]),2));
    output->x[2]=y->x[3];;
    output->x[3]=((m+1)*l*sin(y->x[0]-y->x[2])*pow(y->x[1],2)
            +pow(y->x[3],2)*sin(y->x[0]-y->x[2])*cos(y->x[0]-y->x[2])
            -(m+1)*g*(sin(y->x[2])-sin(y->x[0])*cos(y->x[0]-y->x[2])))
            /(m+1-pow(cos(y->x[0]-y->x[2]),2));
}
void add1(PVector x, PVector y, double a, PVector output)
{
    output->x[0]=x->x[0]+a*y->x[0];
    output->x[1]=x->x[1]+a*y->x[1];
    output->x[2]=x->x[2]+a*y->x[2];
    output->x[3]=x->x[3]+a*y->x[3];
}
void add2(PVector x, PVector y, PVector z, double a, double b, PVector output)
{
    output->x[0]=x->x[0]+a*y->x[0]+b*z->x[0];
    output->x[1]=x->x[1]+a*y->x[1]+b*z->x[1];
    output->x[2]=x->x[2]+a*y->x[2]+b*z->x[2];
    output->x[3]=x->x[3]+a*y->x[3]+b*z->x[3];
}
void add3(PVector x, PVector y, PVector z, PVector m, double a, double b, double c, PVector output)
{
    output->x[0]=x->x[0]+a*y->x[0]+b*z->x[0]+c*m->x[0];
    output->x[1]=x->x[1]+a*y->x[1]+b*z->x[1]+c*m->x[1];
    output->x[2]=x->x[2]+a*y->x[2]+b*z->x[2]+c*m->x[2];
    output->x[3]=x->x[3]+a*y->x[3]+b*z->x[3]+c*m->x[3];
}
void add4(PVector x, PVector y, PVector z, PVector m, PVector n,
         double a, double b, double c, double d ,PVector output)
{
    output->x[0]=x->x[0]+a*y->x[0]+b*z->x[0]+c*m->x[0]+d*n->x[0];
    output->x[1]=x->x[1]+a*y->x[1]+b*z->x[1]+c*m->x[1]+d*n->x[1];
    output->x[2]=x->x[2]+a*y->x[2]+b*z->x[2]+c*m->x[2]+d*n->x[2];
    output->x[3]=x->x[3]+a*y->x[3]+b*z->x[3]+c*m->x[3]+d*n->x[3];
}
void add5(PVector x, PVector y, PVector z, PVector m, PVector n, PVector k,
         double a, double b, double c, double d, double e, PVector output)
{
    output->x[0]=x->x[0]+a*y->x[0]+b*z->x[0]+c*m->x[0]+d*n->x[0]+e*k->x[0];
    output->x[1]=x->x[1]+a*y->x[1]+b*z->x[1]+c*m->x[1]+d*n->x[1]+e*k->x[1];
    output->x[2]=x->x[2]+a*y->x[2]+b*z->x[2]+c*m->x[2]+d*n->x[2]+e*k->x[2];
    output->x[3]=x->x[3]+a*y->x[3]+b*z->x[3]+c*m->x[3]+d*n->x[3]+e*k->x[3];
}
void add6(PVector x, PVector y, PVector z, PVector m, PVector n, PVector k, PVector k_1,
         double a, double b, double c, double d, double e, double e_1, PVector output)
{
    output->x[0]=x->x[0]+a*y->x[0]+b*z->x[0]+c*m->x[0]+d*n->x[0]+e*k->x[0]+e_1*k_1->x[0];
    output->x[1]=x->x[1]+a*y->x[1]+b*z->x[1]+c*m->x[1]+d*n->x[1]+e*k->x[1]+e_1*k_1->x[1];
    output->x[2]=x->x[2]+a*y->x[2]+b*z->x[2]+c*m->x[2]+d*n->x[2]+e*k->x[2]+e_1*k_1->x[2];
    output->x[3]=x->x[3]+a*y->x[3]+b*z->x[3]+c*m->x[3]+d*n->x[3]+e*k->x[3]+e_1*k_1->x[3];
}
void sum(PVector x, PVector y, PVector z, PVector p, PVector q, PVector v, PVector output)
{
    output->x[0]=c_1*x->x[0]+c_2*y->x[0]+c_3*z->x[0]+c_4*p->x[0]+c_5*q->x[0]+c_6*v->x[0];
    output->x[1]=c_1*x->x[1]+c_2*y->x[1]+c_3*z->x[1]+c_4*p->x[1]+c_5*q->x[1]+c_6*v->x[1];
    output->x[2]=c_1*x->x[2]+c_2*y->x[2]+c_3*z->x[2]+c_4*p->x[2]+c_5*q->x[2]+c_6*v->x[2];
    output->x[3]=c_1*x->x[3]+c_2*y->x[3]+c_3*z->x[3]+c_4*p->x[3]+c_5*q->x[3]+c_6*v->x[3];
}
void sum(PVector x, PVector y, PVector z, PVector p, PVector q, PVector v, PVector v_1, PVector output)
{
    output->x[0]=c_1*x->x[0]+c_2*y->x[0]+c_3*z->x[0]+c_4*p->x[0]+c_5*q->x[0]+c_6*v->x[0]+c_7*v_1->x[0];
    output->x[1]=c_1*x->x[1]+c_2*y->x[1]+c_3*z->x[1]+c_4*p->x[1]+c_5*q->x[1]+c_6*v->x[1]+c_7*v_1->x[1];
    output->x[2]=c_1*x->x[2]+c_2*y->x[2]+c_3*z->x[2]+c_4*p->x[2]+c_5*q->x[2]+c_6*v->x[2]+c_7*v_1->x[2];
    output->x[3]=c_1*x->x[3]+c_2*y->x[3]+c_3*z->x[3]+c_4*p->x[3]+c_5*q->x[3]+c_6*v->x[3]+c_7*v_1->x[3];
}


void Double_Pendulum_Culculate::RKCK4_solve(Double_Pendulum_Culculate pendulum, double y_1_initial, double y_2_initial, double y_3_initial, double y_4_initial,
                                            PVector w, double* output_y_1, double* output_y_2,double* output_y_3, double* output_y_4, double* output_t)
{

    pendulum.calculate_n();
    pendulum.set_time(pendulum.get_time());
    pendulum.set_y_1_initial(y_1_initial);
    pendulum.set_y_2_initial(y_2_initial);
    pendulum.set_y_3_initial(y_3_initial);
    pendulum.set_y_4_initial(y_4_initial);

    PVector w1 = new Vector;
    PVector w2 = new Vector;
    PVector w3 = new Vector;
    PVector w4 = new Vector;
    PVector w5 = new Vector;
    PVector w6 = new Vector;
    PVector w7 = new Vector;
    PVector s1 = new Vector;
    PVector s2 = new Vector;
    PVector s3 = new Vector;
    PVector s4 = new Vector;
    PVector s5 = new Vector;
    PVector s6 = new Vector;
    PVector s7 = new Vector;

    w->x[0]=pendulum.get_y_1();
    w->x[1]=pendulum.get_y_2();
    w->x[2]=pendulum.get_y_3();
    w->x[3]=pendulum.get_y_4();

    for(int i=1;i<=pendulum.get_n()+1;i++)
    {
        f(pendulum,pendulum.get_time(),w,s1);
        add1(w,s1,b_21*h,w1);
        f(pendulum, pendulum.get_time()+h*a_2,w1,s2);
        add2(w,s1,s2,b_31*h,b_32*h,w2);
        f(pendulum, pendulum.get_time()+h*a_3,w2,s3);
        add3(w,s1,s2,s3,b_41*h,b_42*h,b_43*h,w3);
        f(pendulum, pendulum.get_time()+h*a_4, w3,s4);
        add4(w,s1,s2,s3,s4,b_51*h,b_52*h,b_53*h,b_54*h,w4);
        f(pendulum, pendulum.get_time()+h*a_5, w4,s5);
        add5(w,s1,s2,s3,s4,s5,b_61*h,b_62*h,b_63*h,b_64*h,b_65*h,w5);
        f(pendulum, pendulum.get_time()+h*a_6, w5,s6);
        add6(w,s1,s2,s3,s4,s5,s6,b_71*h,b_72*h,b_73*h,b_74*h,b_75*h,b_76*h,w6);
        f(pendulum, pendulum.get_time()+h*a_7, w6,s7);
        sum(s1,s2,s3,s4,s5,s6,s7,w7);
        add1(w,w7,h,w);
        pendulum.set_time(pendulum.get_time()+h);
        output_y_1[i - 1] = w->x[0];
        output_y_2[i - 1] = w->x[1];
        output_y_3[i - 1] = w->x[2];
        output_y_4[i - 1] = w->x[3];
        output_t[i - 1]= pendulum.get_time();
    }
}

