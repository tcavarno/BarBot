#include "L298N.h"
#include <Arduino.h>


L298N::L298N(uint8_t pwm_pin_0,uint8_t in1_pin,uint8_t in2_pin,uint8_t pwm_pin_1,uint8_t in3_pin,uint8_t in4_pin ){
    this->pwm_pin_0 = pwm_pin_0;
    this->pwm_pin_1 = pwm_pin_1;
    this->in1_pin = in1_pin;
    this->in2_pin = in2_pin;
    this->in3_pin = in3_pin;
    this->in4_pin = in4_pin;
}


void L298N::set_motor_speed(int speed,uint8_t motor_number){
    uint8_t motor_pin = motor_number == 0? this->pwm_pin_0:this->pwm_pin_1;
    uint8_t dir_pin_1 = motor_number == 0 ? this->in1_pin: this->in2_pin;
    uint8_t dir_pin_2 = motor_number == 0 ? this->in2_pin: this-> in4_pin;
    if(speed >0){
        digitalWrite(dir_pin_1,MOTOR_POLARITY);
        digitalWrite(dir_pin_2,!MOTOR_POLARITY);
    } else if (speed < 0){
        speed *= -1;
        digitalWrite(dir_pin_1,!MOTOR_POLARITY);
        digitalWrite(dir_pin_2,MOTOR_POLARITY);
    }
    analogWrite(motor_pin,speed);

}