#include <Arduino.h>
#ifndef FLOW_SENSOR_H
#define FLOW_SENSOR_H

#define TICKSPERML 4.38
//TODO: ASYNC STEPPER DRIVER USING TIMER INTERRUPTS

typedef enum {
    INTR_CHANNEL_0 = 2,
    INTR_CHANNEL_1 = 3,
    INTR_CHANNEL_2 = 21,
    INTR_CHANNEL_3 = 20,
    INTR_CHANNEL_4 = 19,
    INTR_CHANNEL_5 = 18,
} EXT_INTR;


/**
 * @brief 
 * 
 */

class FlowSensor{
    public:
        
        FlowSensor(EXT_INTR channel);

        float get_volume();

        void reset_flow();

        static volatile uint16_t flow_ticks_0;
        static volatile uint16_t flow_ticks_1;
        static volatile uint16_t flow_ticks_2;
        static volatile uint16_t flow_ticks_3;
        static volatile uint16_t flow_ticks_4;
        static volatile uint16_t flow_ticks_5;

    
    private:
        EXT_INTR channel;
        float volume;
};
#endif