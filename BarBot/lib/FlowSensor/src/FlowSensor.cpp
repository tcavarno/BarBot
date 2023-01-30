#include "FlowSensor.h"
#include <Arduino.h>
/**
 * @file FlowSensor.cpp
 * @author Tristan Cavarno
 * @date 1/29/23
 * 
 * @version 0.5
 * 
 * @brief Implmentation of the FlowSensor
 */

/**
 * @brief Initialization of static member for 
 * INTER_CHANNEL_0
 * 
 */
volatile uint16_t FlowSensor::flow_ticks_0 = 0;

/**
 * @brief Initialization of static member for 
 * INTER_CHANNEL_1
 * 
 */
volatile uint16_t FlowSensor::flow_ticks_1 = 0;

/**
 * @brief Initialization of static member for 
 * INTER_CHANNEL_2
 * 
 */
volatile uint16_t FlowSensor::flow_ticks_2 = 0;

/**
 * @brief Initialization of static member for 
 * INTER_CHANNEL_3
 * 
 */
volatile uint16_t FlowSensor::flow_ticks_3 = 0;

/**
 * @brief Initialization of static member for 
 * INTER_CHANNEL_4
 * 
 */
volatile uint16_t FlowSensor::flow_ticks_4 = 0;

/**
 * @brief Initialization of static member for 
 * INTER_CHANNEL_5
 * 
 */
volatile uint16_t FlowSensor::flow_ticks_5 = 0;

/**
 * @brief isr handler for INTER_CHANNEL_0
 * 
 */
void flow_isr_ch0(){FlowSensor::flow_ticks_0++;}

/**
 * @brief isr handler for INTER_CHANNEL_1
 * 
 */
void flow_isr_ch1(){FlowSensor::flow_ticks_1++;}

/**
 * @brief isr handler for INTER_CHANNEL_2
 * 
 */
void flow_isr_ch2(){FlowSensor::flow_ticks_2++;}

/**
 * @brief isr handler for INTER_CHANNEL_3
 * 
 */
void flow_isr_ch3(){FlowSensor::flow_ticks_3++;}

/**
 * @brief isr handler for INTER_CHANNEL_4
 * 
 */
void flow_isr_ch4(){FlowSensor::flow_ticks_4++;}

/**
 * @brief isr handler for INTER_CHANNEL_5
 * 
 */
void flow_isr_ch5(){FlowSensor::flow_ticks_5++;}



FlowSensor::FlowSensor(EXT_INTR channel){
    switch (channel){
    case INTR_CHANNEL_0:
        FlowSensor::flow_ticks_0 = 0;
        pinMode(INTR_CHANNEL_0, INPUT);               // initializes digital pin 2 as an input
        attachInterrupt(INT0, flow_isr_ch0, RISING);          // and the interrupt is attached
        break;
    case INTR_CHANNEL_1:
        FlowSensor::flow_ticks_1 = 0;
        pinMode(INTR_CHANNEL_1, INPUT);               // initializes digital pin 3 as an input
        attachInterrupt(INT1, flow_isr_ch1, RISING);          // and the interrupt is attached
        break;
    case INTR_CHANNEL_2:
        FlowSensor::flow_ticks_2 = 0;
        pinMode(INTR_CHANNEL_2, INPUT);               // initializes digital pin 21 as an input
        attachInterrupt(INT2, flow_isr_ch1, RISING);          // and the interrupt is attached
        break;
    case INTR_CHANNEL_3:
        FlowSensor::flow_ticks_3 = 0;
        pinMode(INTR_CHANNEL_3, INPUT);               // initializes digital pin 20 as an input
        attachInterrupt(INT3, flow_isr_ch3, RISING);          // and the interrupt is attached
        break;
    case INTR_CHANNEL_4:
        FlowSensor::flow_ticks_4 = 0;
        pinMode(INTR_CHANNEL_4, INPUT);               // initializes digital pin 19 as an input
        attachInterrupt(INT4, flow_isr_ch4, RISING);          // and the interrupt is attached
        break;
    case INTR_CHANNEL_5:
        FlowSensor::flow_ticks_5 = 0;
        pinMode(INTR_CHANNEL_5, INPUT);               // initializes digital pin 18 as an input
        attachInterrupt(INT5, flow_isr_ch5, RISING);          // and the interrupt is attached
        break;
    
    default:
        break;
    };
    this->channel = channel;
    this->volume = 0;
}

void FlowSensor::reset_flow(){
    this->volume = 0;
    switch (this->channel){
        case INTR_CHANNEL_0:
            FlowSensor::flow_ticks_0 = 0;
            break;
        case INTR_CHANNEL_1:
            FlowSensor::flow_ticks_1 = 0;
            break;
        case INTR_CHANNEL_2:
            FlowSensor::flow_ticks_2 = 0;
            break;
        case INTR_CHANNEL_3:
            FlowSensor::flow_ticks_3 = 0;
            break;
        case INTR_CHANNEL_4:
            FlowSensor::flow_ticks_4 = 0;
            break;
        case INTR_CHANNEL_5:
            FlowSensor::flow_ticks_5 = 0;
            break;
        default:
            break;
    }
}

double FlowSensor::get_volume(){
    switch (this->channel){
    case INTR_CHANNEL_0:
        this->volume += FlowSensor::flow_ticks_0/TICKSPERML;
        FlowSensor::flow_ticks_0 = 0;
        return this->volume;
        break;
    case INTR_CHANNEL_1:
        this->volume= FlowSensor::flow_ticks_1/TICKSPERML;
        FlowSensor::flow_ticks_1 = 0;
        return this->volume;
        break;
    case INTR_CHANNEL_2:
        this->volume= FlowSensor::flow_ticks_2/TICKSPERML;
        FlowSensor::flow_ticks_2 = 0;
        return this->volume;
        break;
    case INTR_CHANNEL_3:
        this->volume= FlowSensor::flow_ticks_3/TICKSPERML;
        FlowSensor::flow_ticks_3 = 0;
        return this->volume;
        break;
    case INTR_CHANNEL_4:
        this->volume= FlowSensor::flow_ticks_4/TICKSPERML;
        FlowSensor::flow_ticks_4 = 0;
        return this->volume;
        break;
    case INTR_CHANNEL_5:
        this->volume= FlowSensor::flow_ticks_5/TICKSPERML;
        FlowSensor::flow_ticks_5 = 0;
        return this->volume;
        break;
    
    default:
        return this->volume;
        break;
    }
    return -1.0;       
}

