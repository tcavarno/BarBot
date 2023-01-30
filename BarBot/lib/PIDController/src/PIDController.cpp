#include "PIDController.h"
#include <Arduino.h>

PIDController::PIDController(bool log){
    this->acutal = 0;
    this->target = 0;
    this->error = 0;
    this->d_error = 0;
    this->i_error = 0;
    this->log_data = log;
    if(log){
        start_serial();
    } 
}

int PIDController::update(double target,double actual){
    double new_error = target-actual;
    this->acutal = actual;
    this->target = target;
    this->d_error = this->error - new_error;
    this->i_error += this->error;
    this->error = new_error;

    if(this->log_data)
        format_and_log_data();
    double out = (Kp*this->error + Kd*this->d_error + Ki*this->i_error)*10;
    return int(max(min(out,100.0),-100.0));
}

void PIDController::format_and_log_data(){
    char buf[200];
    int out = (Kp*this->error + Kd*this->d_error + Ki*this->i_error)*10;
    sprintf(buf,"A: %d,E: %d,D: %d,I: %d,O: %d",(int)this->acutal,(int)this->error,(int)Kd*this->d_error,(int)Ki*this->i_error,out);
    Serial.println(buf);
}

int PIDController::get_error(){
    return this->error;
}

void PIDController::start_serial(){
    bool connecting = true;
    Serial.begin(115200);
    Serial.setTimeout(1000);
    while(!Serial){;}
    while(connecting){
        Serial.println("CONNECT_MCU");
        String s = Serial.readString();
        connecting = !(s == "CONNECT_ACK\n");
    }

}

void PIDController::reset(){
    target = 0;
    acutal = 0;
    error = 0;
    d_error = 0;
    i_error = 0;
}