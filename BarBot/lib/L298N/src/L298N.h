#include <Arduino.h>
#ifndef L298N_H
#define L298N_H

/**
 * @file L298N.h
 * @author Tristan Cavarno
 * @date 1/29/23
 * 
 * @version 1.0
 * 
 * @brief The header file to define the use of an l298n 
 * motor driver from elegoo. Note that this is an H-bridge
 * motor driver and will not swing Vm all the way to the rail (Vin)
 */

/**
 * @brief A macro to allow for the change of polarity
 * #TODO: Make this a parameter of each motor in each instance
 * 
 */
#define MOTOR_POLARITY 0

/**
 * @brief Named macro to make the use of
 * set_motor_speed more readable for the 
 * zeroth motor channel
 * 
 */
#define L298N_MOTOR_0 0

/**
 * @brief Named macro to make the use of
 * set_motor_speed more readable for the 
 * first motor channel
 * 
 */
#define L298N_MOTOR_1 1

/**
 * @brief A class that corrisponds to exactly
 * one l298n motor driver.
 * 
 */
class L298N{
    public:
        
        /**
         * @brief Construct a new L298N object
         * Assigns internal pin locations
         * 
         * @param pwm_pin_0 The pin location used to set the speed of
         * Motor_0 
         * @param in1_pin The first direction pin for Motor_0
         * @param in2_pin The second direction pin for Motor_0
         * @param pwm_pin_1 The pin location used to set the speed of
         * Motor_1
         * @param in3_pin The first direction pin for Motor_1
         * @param in4_pin The second direction pin for Motor_1
         */
        L298N(uint8_t pwm_pin_0,uint8_t in1_pin,uint8_t in2_pin,uint8_t pwm_pin_1=-1,uint8_t in3_pin=-1,uint8_t in4_pin =-1);

        /**
         * @brief Set the motor speed
         * 
         * @param speed a integer netween -100 to 100 corrisponding to motor speed
         * @param motor_number 0 or 1 depening on which of the two motors 
         * you want to set the speed of **SEE THE MACROS DEFINED ABOVE**
         */
        void set_motor_speed(int speed,uint8_t motor_number);
    
    private:
        /**
         * @brief The pin location used to set the speed of
         * Motor_0 
         * 
         */
        uint8_t pwm_pin_0;

        /**
         * @brief The first direction pin for Motor_0
         * 
         */
        uint8_t in1_pin;

        /**
         * @brief The second direction pin for Motor_0
         * 
         */
        uint8_t in2_pin;

        /**
         * @brief The pin location used to set the speed of
         * Motor_1
         * 
         */
        uint8_t pwm_pin_1;

        /**
         * @brief The first direction pin for Motor_1
         * 
         */
        uint8_t in3_pin;

        /**
         * @brief The second direction pin for Motor_1
         * 
         */
        uint8_t in4_pin;

};
#endif