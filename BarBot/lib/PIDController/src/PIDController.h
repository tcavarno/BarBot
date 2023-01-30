#include <Arduino.h>
#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H
/**
 * @file PIDController.h
 * @author Tristan Cavarno
 * @date 1/29/23
 * 
 * @version 0.5
 * 
 * @brief The Header file for all things PID Control Related.
 * This includes constants and logging
 */

#define Kp .5
#define Kd .3
#define Ki 0

/**
 * @brief PIDController is an Object designed to 
 * handle the control for one single input single
 * output control. 
 * 
 */
class PIDController{
    public:
        /**
         * @brief Construct a new PIDController object
         * If log_data is true the MCU will attempt to 
         * establish connection with a host machine for
         * data logging. It will sit in this state until
         * "CONNECT_ACK\n" is sent over 'Serial'.
         * 
         * @param log_data Type: Bool, Whether or not data 
         * should be logged by the controller and sent 
         * to an external device over Serial.
         */
        PIDController(bool log_data);

        /**
         * @brief Update the internal error states and 
         * calculate the output given by Kp*e+Kd*d_error+Ki*i_error.
         * This value will be clamped between -100 and 100.
         * 
         * **NOTE** This seems like it might be overkill so 
         * some functionality by be unused and untested. 
         * 
         * @param target The target value the controller will
         * attempt to reach
         * 
         * @param actual The current value of the system
         * 
         * @return int: The output to send to an actuator 
         */
        int update(double target,double actual);

        /**
         * @brief Get the current error of the system
         * 
         * @return int A typecast of the internal error
         * double
         */
        int get_error();

        /**
         * @brief Reset the interal error members to zero.
         * 
         */
        void reset();

    private:

        /**
         * @brief The Desired state of the system.
         * 
         */
        double target;

        /**
         * @brief The current state of the system
         * 
         */
        double acutal;

        /**
         * @brief The current difference between
         * the target and actual values.
         * 
         */
        double error;

        /**
         * @brief The differnce between the previous
         * error and the current error.
         * 
         */
        double d_error;

        /**
         * @brief The summation of all previous errors
         * Probably broken. Seems to overflow frequently
         * if left for a long time.
         */
        double i_error;

        /**
         * @brief Is this instance of the controller
         * logging data
         * 
         */
        int log_data;

        /**
         * @brief Take the internal error members and 
         * generate a string to send to a recipent over
         * Serial. This String can then be parsed to see 
         * the state and response of the controller as 
         * data is sample.
         * 
         */
        void format_and_log_data();

        /**
         * @brief Handle begining a serial connection
         * This is called by the constructor to insure
         * that there is a destination for logged data.
         * 
         */
        void start_serial();

};


#endif