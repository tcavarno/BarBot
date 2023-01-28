#include "StepperDriver.h"
#include <Arduino.h>

stepper_timer_t StepperDriver::timer3;

stepper_timer_t StepperDriver::timer4;

stepper_timer_t StepperDriver::timer5;

StepperDriver::StepperDriver(int STEP,int DIR,STEPPER_TIMER_CHANNEL timer_channel,int EN){
    //Set PinModes
    pinMode(STEP, OUTPUT); 
    pinMode(DIR, OUTPUT); 
    if(EN != -1)
        pinMode(EN,OUTPUT);

    stepper_timer_t timer;
    //Init Timers Dependent on Input.
    switch(timer_channel){
        case TIMER3:
            init_timer3();
            timer.pin_num = STEP;
            timer.steps = 0;
            timer.pin_state = 0;
            StepperDriver::timer3 = timer;
            break;
        case TIMER4:
            init_timer4();
            timer.pin_num = STEP;
            timer.steps = 0;
            timer.pin_state = 0;
            StepperDriver::timer4=timer;
            break;
        default:
            init_timer5();
            timer.pin_num = STEP;
            timer.steps = 0;
            timer.pin_state = 0;
            StepperDriver::timer5 = timer;
            break;
    }

    timer_num = timer_channel;
}

void StepperDriver::step_motor(int steps, uint16_t speed){


}


/*
 * This section contains all the helper functions that are required 
 * to use timers for stepper driving.
 */
ISR(TIMER3_COMPA_vect){

}
ISR(TIMER4_COMPA_vect){
    
}
ISR(TIMER5_COMPA_vect){
    
}

void StepperDriver::init_timer3(){
    //Make sure no interrupts occur while setting the timer control registers.
    cli();
    //Reset Timer Control Registers
    TCCR3A = 0;
    TCCR3B = 0;
    
    //Zero Timer Counter
    TCNT3 = 0;
    //Set Timer Channel A for Interrupts
    TIMSK3 = TIMSKX_CHA_INTR;

    //Tigger Interrupts Every 1000 ticks (500us) by Default
    OCR3A = 1000;

    sei();
}
void StepperDriver::init_timer4(){
    //Make sure no interrupts occur while setting the timer control registers.
    cli();
    //Reset Timer Control Registers
    TCCR4A = 0;
    TCCR4B = 0;
    
    //Zero Timer Counter
    TCNT4 = 0;
    //Set Timer Channel A for Interrupts
    TIMSK4 = TIMSKX_CHA_INTR;

    //Tigger Interrupts Every 1000 ticks (500us) by Default
    OCR4A = 1000;

    sei();

}

void StepperDriver::init_timer5(){
    //Make sure no interrupts occur while setting the timer control registers.
    cli();
    //Reset Timer Control Registers
    TCCR4A = 0;
    TCCR4B = 0;
    
    //Zero Timer Counter
    TCNT4 = 0;
    //Set Timer Channel A for Interrupts
    TIMSK4 = TIMSKX_CHA_INTR;

    //Tigger Interrupts Every 1000 ticks (500us) by Default
    OCR4A = 1000;

    sei();

}

void StepperDriver::start_timer(){
    cli();
    switch (this->timer_num){
        case TIMER3:
            TCCR3B = TCCRXB_PRESCALE_8;
            TCNT3 = 0;
            break;
        case TIMER4:
            TCCR4B = TCCRXB_PRESCALE_8;
            TCNT4 = 0;
            break;
        default:
            TCCR5B = TCCRXB_PRESCALE_8;
            TCNT5 = 0;
            break;
    }
    
    sei();
}

void StepperDriver::stop_timer(){
    cli();
    switch (this->timer_num){
        case TIMER3:
            TCCR3B = TCCRXB_TIMER_STOP;
            break;
        case TIMER4:
            TCCR4B = TCCRXB_TIMER_STOP;
            break;
        default:
            TCCR5B = TCCRXB_TIMER_STOP;
            break;
    }
    
    sei();

}

