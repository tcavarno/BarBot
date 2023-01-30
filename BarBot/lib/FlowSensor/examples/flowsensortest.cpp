#include <Arduino.h>
#include <FlowSensor.h>
/**
 * @file flowsensortest.cpp
 * @author Tristan Cavarno
 * @date 1/29/23
 * 
 * @version 1.0
 * 
 * @brief A simple test to verify 
 * that the FlowSensor propery 
 * records data.
 */

FlowSensor* flow_sens;


bool run = true;
void setup() {
    flow_sens = new FlowSensor(EXT_INTR::INTR_CHANNEL_0);
    Serial.begin(115200);
}

void loop() {
    if(!run)
        return;
    double flow = flow_sens->get_volume();
    char buff[100];
    snprintf(buff,sizeof(buff),"Volume Pumped %d ml",(int)flow);
    Serial.println(buff);

}