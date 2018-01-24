#ifndef DOUBLE_PENDULUM_CULCULATE_H
#define DOUBLE_PENDULUM_CULCULATE_H


typedef struct _Vector_4d_for_double
    {
      double x[4];
    }Vector, *PVector;


class Double_Pendulum_Culculate
{
public:
    Double_Pendulum_Culculate();
    void func(int);
    double ShowY_1();
    double ShowY_2();
    double ShowY_3();
    double ShowY_4();
    double get_time(){return t;}
    double get_y_1(){return y_1;}
    double get_y_2(){return y_2;}
    double get_y_3(){return y_3;}
    double get_y_4(){return y_4;}
    int get_n(){return n;}
    double get_m(){return m;}
    double get_l(){return l;}
    void set_begin_time(double input_begin_time=0);
    void set_last_time(double input_last_time);
    void set_time(double input_time){t=input_time;}
    void set_y_1_initial(double y_1_initial);
    void set_y_2_initial(double y_2_initial);
    void set_y_3_initial(double y_3_initial);
    void set_y_4_initial(double y_4_initial);
    void set_m(double mass){m=mass;}
    void set_l(double length){l=length;}
    void calculate_n();
    void f(Double_Pendulum_Culculate pendulum, double t, PVector y, PVector output);
    void RKCK4_solve(Double_Pendulum_Culculate pendulum, double y_1_initial, double y_2_initial, double y_3_initial, double y_4_initial,
                             PVector w, double* output_y_1, double* output_y_2, double* output_y_3, double* output_y_4, double* output_t);

private:
    double begin_time,last_time,y_1,y_2,y_3,y_4;
    double t=begin_time;
    int n;
    double m,l;
};


#endif // DOUBLE_PENDULUM_CULCULATE_H
