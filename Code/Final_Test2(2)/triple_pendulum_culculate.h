#ifndef TRIPLE_PENDULUM_CULCULATE_H
#define TRIPLE_PENDULUM_CULCULATE_H
typedef struct _Vector_6d_for_Triple
    {
      double x[6];
    }tVector, *TVector;


class Triple_Pendulum_Culculate
{
public:
    Triple_Pendulum_Culculate();
        void func(int);
        double ShowY_1();
        double ShowY_2();
        double ShowY_3();
        double ShowY_4();
        double ShowY_5();
        double ShowY_6();
        double get_time(){return t;}
        double get_y_1(){return y_1;}
        double get_y_2(){return y_2;}
        double get_y_3(){return y_3;}
        double get_y_4(){return y_4;}
        double get_y_5(){return y_5;}
        double get_y_6(){return y_6;}
        double get_n(){return n;}
        double get_m_1(){return m_1;}
        double get_m_2(){return m_2;}
        double get_l_1(){return l_1;}
        double get_l_2(){return l_2;}
        void set_begin_time(double input_begin_time=0);
        void set_last_time(double input_last_time);
        void set_time(double input_time){t=input_time;}
        void set_y_1_initial(double y_1_initial);
        void set_y_2_initial(double y_2_initial);
        void set_y_3_initial(double y_3_initial);
        void set_y_4_initial(double y_4_initial);
        void set_y_5_initial(double y_5_initial);
        void set_y_6_initial(double y_6_initial);
        void set_m_1(double mass){m_1=mass;}
        void set_m_2(double mass){m_2=mass;}
        void set_l_1(double length){l_1=length;}
        void set_l_2(double length){l_2=length;}
        void calculate_n();
        //void f(Triple_Pendulum_Culculate pendulum, double t, TVector y, TVector output);
        void RK4_solve_triple(Triple_Pendulum_Culculate pendulum, double y_1_initial, double y_2_initial, double y_3_initial, double y_4_initial,
                            double y_5_initial, double y_6_initial, TVector w, double *&output_y_1, double *&output_y_2,
                            double *&output_y_3, double *&output_y_4, double *&output_y_5, double *&output_y_6, double *&output_t);



    private:
    double begin_time,last_time,y_1,y_2,y_3,y_4,y_5,y_6;
    double t=begin_time;
    int n;
    double m_1,m_2,l_1,l_2;
};

#endif // TRIPLE_PENDULUM_CULCULATE_H

