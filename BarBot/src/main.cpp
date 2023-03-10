#include <Arduino.h>
#include <StepperDriver.h>
#include <L298N.h>
#include <PIDController.h>
#include <FlowSensor.h>
/** 
 * @mainpage Bar Bot Project Documentation
 * @section intro_sec Introduction
 * This is the Bar Bot Platformio Project used to develop and maintain
 * my senior project. The Bar Bot is a Arduino Mega controlled Cocktail Mixing Robot.
 * Here lies the documention for all the of code used to control the Bar Bot ranging
 * from dc motor control, stepper motor control, and flow measurement. 
 * @section install_sec Installation
 *
 * @subsection install_dependencies Installing Dependencies
 * Do somethings ...
 * @subsection install_library Installing Library
 * Do somethings ...
 * @subsection install_example Installing Examples
 * Do somethings ...
 */


#define TOLERANCE 2
#define TICKSPER
typedef enum{
  WAIT_FOR_COMMAND,
  SET_TARGET,
  JOG,
  PID,

} FLOW_TEST_STATES;


PIDController* controller_test;
L298N* motor_driver;
FlowSensor* flow_meter;

int value = 0;
int pid_target = 0;

#define OUT 12
#define DIR1 11
#define DIR2 10

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  controller_test = new PIDController(true);
  motor_driver = new L298N(OUT,DIR1,DIR2);
  flow_meter = new FlowSensor(INTR_CHANNEL_0); 
}

FLOW_TEST_STATES state= WAIT_FOR_COMMAND;

int parse_commands(FLOW_TEST_STATES* state){
    String command;
    String param;
    String read = Serial.readStringUntil('\n');
    int delim_loc = read.indexOf('/');
    if (delim_loc != -1){
        command = read.substring(0,delim_loc);
        param = read.substring(delim_loc+1);
    }else{
        command = read;
    }
    
    if(command == "COMMAND_JOG"){
        long jog_time = param.toInt();
        char buff[200];
        snprintf(buff,sizeof(buff),"ACK_JOG/COMMAND_JOG Accepted. Pumping for %ld ms.\n",jog_time);
        Serial.println(buff);
        *state = JOG;
        return jog_time;
    }else if(command == "COMMAND_TARGET"){
        long target = param.toInt();
        char buff[200];
        snprintf(buff,sizeof(buff),"ACK_TARGET/COMMAND_TARGET Accepted. Setting target to %ld ml.\n",target);
        Serial.println(buff);
        *state = SET_TARGET;
        return target;
    }else if(command == "COMMAND_PID"){
        char buff[200];
        snprintf(buff,sizeof(buff),"ACK_PID/COMMAND_PID Accepted. Starting PID test.\n");
        Serial.println(buff);
        *state = PID;
        return -1;
    }
    return -1;
}

int wait_for_command(FLOW_TEST_STATES* state){
    long value = 0;
    while(*state == WAIT_FOR_COMMAND){
        value = parse_commands(state);
    }

    return value;
}

void jog(FLOW_TEST_STATES* state,int value){
    motor_driver->set_motor_speed(85,L298N_MOTOR_0);
    delay(value);
    motor_driver->set_motor_speed(0,L298N_MOTOR_0);
    *state = WAIT_FOR_COMMAND;
}
void pid(FLOW_TEST_STATES* state,double target){
    double volume =0;
    int motor_speed = 0;
    flow_meter->reset_flow();
    controller_test->update(target,volume);
    while(controller_test->get_error()> TOLERANCE){
        volume = flow_meter->get_volume();
        motor_speed = controller_test->update(target,volume);
        motor_driver->set_motor_speed(motor_speed,L298N_MOTOR_0);

    }
    motor_driver->set_motor_speed(0,L298N_MOTOR_0);
    
    *state = WAIT_FOR_COMMAND;
}
void set_target(FLOW_TEST_STATES* state,int value){
    *state = WAIT_FOR_COMMAND;
}
void loop() {
    
    switch (state){
        case WAIT_FOR_COMMAND:
            value = wait_for_command(&state);
            break;
        case JOG:
            jog(&state,value);
            break;
        case SET_TARGET:
            pid_target = value;
            state = WAIT_FOR_COMMAND;
            break;
        case PID:
            pid(&state,pid_target);
            break;
        default:
            value = wait_for_command(&state);
            break;
    }
}