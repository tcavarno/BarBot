#include <Arduino.h>
#include <L298N.h>

/**
 * @file ln298ntest.cpp
 * @author Tristan Cavarno
 * @date 1/29/23
 * 
 * @version 1.0
 * 
 * @brief A simple test to verify 
 * that the L298N class functions 
 * as intended. 
 */

#define OUT 12
#define DIR1 11
#define DIR2 10

L298N* motor_driver;

bool run = true;
void setup() {
    motor_driver = new L298N(OUT,DIR1,DIR2);
}

void loop() {
    if(!run)
        return;
    for(int i = 70;i <=100;i+=2){
        motor_driver->set_motor_speed(i,L298N_MOTOR_0);
        delay(500);
    }
    delay(2000);
    for(int i = 100;i >=70;i-=2){
        motor_driver->set_motor_speed(i,L298N_MOTOR_0);
        delay(500);
    }

    for(int i = -70;i >=-100;i-=2){
        motor_driver->set_motor_speed(i,L298N_MOTOR_0);
        delay(500);
    }
    delay(2000);

    run = false;

}