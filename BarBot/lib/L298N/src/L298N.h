#include <Arduino.h>
#ifndef L298N_H
#define L298N_H
//TODO: ASYNC STEPPER DRIVER USING TIMER INTERRUPTS

#define MOTOR_POLARITY 0
#define L298N_MOTOR_0 0
#define L298N_MOTOR_1 1
/**
 * @brief 
 * 
 */
class L298N{
    public:
        
        L298N(uint8_t pwm_pin_0,uint8_t in1_pin,uint8_t in2_pin,uint8_t pwm_pin_1=-1,uint8_t in3_pin=-1,uint8_t in4_pin =-1);

        void set_motor_speed(int speed,uint8_t motor_number);
    
    private:
        uint8_t pwm_pin_0;
        uint8_t in1_pin;
        uint8_t in2_pin;
        uint8_t pwm_pin_1;
        uint8_t in3_pin;
        uint8_t in4_pin;

};
#endif