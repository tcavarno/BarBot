#include <Arduino.h>
#ifndef FLOW_SENSOR_H
#define FLOW_SENSOR_H
/**
 * @file FlowSensor.h
 * @author Tristan Cavarno
 * @date 1/29/23
 * 
 * @version 0.5
 * 
 * @brief The Header file for implementing the
 * GREDIA 1/4" flow meter. and all associated 
 * helper enums and types.
 */


#define TICKSPERML 4.38

/**
 * @brief The 6 channels that 
 * support extended interrupts on 
 * the arduino Mega. The value of 
 * each macro corrisponds to the 
 * pin on the Arduino Mega that 
 * the interrupt is generated on.
 */
typedef enum {
    INTR_CHANNEL_0 = 2,
    INTR_CHANNEL_1 = 3,
    INTR_CHANNEL_2 = 21,
    INTR_CHANNEL_3 = 20,
    INTR_CHANNEL_4 = 19,
    INTR_CHANNEL_5 = 18,
} EXT_INTR;


/**
 * @brief A class that corrisponds to exactly
 * one GREDIA 1/4" flow meter. At any time 
 * there should be at max 6 of these objects.
 * 
 * Each object is given one of the 6 extended 
 * interrupt pins to increment a flow counter.
 * 
 */

class FlowSensor{
    public:
        
        /**
         * @brief Construct a new Flow Sensor. Initializes
         * pin mode for the interrupt channel and attaches 
         * an isr to trigger on the rising edge.
         * 
         * @param channel What channel this FlowSensor instance
         * should use.
         */
        FlowSensor(EXT_INTR channel);

        /**
         * @brief Get the current volume (ml) of the flow
         * meter. This reset the tick count for this channel.
         * 
         * @return double
         */
        double get_volume();

        /**
         * @brief reset the volume and ticks for 
         * this channel.
         * 
         */
        void reset_flow();

        /**
         * @brief Static member for INTR_CHANNEL_0 so that
         * the isr have access to a global
         * tick counter.
         * 
         */
        static volatile uint16_t flow_ticks_0;

        /**
         * @brief Static member for INTR_CHANNEL_1 so that
         * the isr have access to a global
         * tick counter.
         * 
         */
        static volatile uint16_t flow_ticks_1;

        /**
         * @brief Static member for INTR_CHANNEL_2 so that
         * the isr have access to a global
         * tick counter.
         * 
         */
        static volatile uint16_t flow_ticks_2;

        /**
         * @brief Static member for INTR_CHANNEL_3 so that
         * the isr have access to a global
         * tick counter.
         * 
         */
        static volatile uint16_t flow_ticks_3;

        /**
         * @brief Static member for INTR_CHANNEL_4so that
         * the isr have access to a global
         * tick counter.
         * 
         */
        static volatile uint16_t flow_ticks_4;

        /**
         * @brief Static member for INTR_CHANNEL_5 so that
         * the isr have access to a global
         * tick counter.
         * 
         */
        static volatile uint16_t flow_ticks_5;

    
    private:
        EXT_INTR channel;
        double volume;
};
#endif