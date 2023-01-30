#include <Arduino.h>
#include <PIDController.h>

/**
 * @file pid_output_test.cpp
 * @author Tristan Cavarno
 * @date 1/29/23
 * 
 * @version 1.0
 * 
 * @brief A simple test to verify 
 * that the pid controller is properly 
 * assigning internal members and logging data
 * to an external Serial device. Used to develop
 * python boken plotting. 
 */

PIDController* pid;
float value=0;

bool run = true;
void setup() {
    pid = new PIDController(true);
}

void loop() {
    for(int i = 0;i<=50;i++){
        pid->update(50,i);
        delay(500);
    }
    pid->reset();
    
}