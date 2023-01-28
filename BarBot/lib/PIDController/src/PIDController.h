#include <Arduino.h>
#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#define Kp .4
#define Kd 0
#define Ki 0

class PIDController{
    public:
        PIDController(bool log_data);

        int update(float target,float actual);

        int get_error();

    private:
        float target;
        float acutal;
        float error;
        float d_error;
        float i_error;
        int log_data;

        void format_and_log_data();

        void start_serial();

};


#endif