#include <Arduino.h>
#ifndef STEPPERDRIVER_H
#define STEPPERDRIVER_H
//TODO: ASYNC STEPPER DRIVER USING TIMER INTERRUPTS

#define TCCRXB_TIMER_STOP B00000000
#define TCCRXB_PRESCALE_1 B00000001
#define TCCRXB_PRESCALE_8 B00000010
#define TCCRXB_PRESCALE_64 B00000011
#define TIMSKX_CHA_INTR B00000010


typedef enum{
    CLOCKWISE = 1,
    COUNTER_CLOCKWISE = 0,

} STEPPER_DIR;

typedef enum{
    TIMER3,
    TIMER4,
    TIMER5,
} STEPPER_TIMER_CHANNEL;

typedef struct{
    uint16_t steps;
    uint8_t pin_num;
    uint8_t pin_state;
} stepper_timer_t;

class StepperDriver{
    public:
        /**
         * @brief Construct a new Stepper Driver:: Stepper Driver object.
         * Sets board configuration and pin output for a single stepper motor.
         * 
         * @param STEP Arduino Pin for STEP Output  
         * @param DIR Arduino Pin for DIR Output
         * @param EN Arduino Pin for EN Output (-1 by default to indicate non-use)
         * 
         */
        StepperDriver(int STEP,int DIR,STEPPER_TIMER_CHANNEL timer_channel=TIMER3,int EN=-1);

        /**
         * @brief Step the motor steps number of ste
         * 
         * @param steps 
         * @param speed 
         */
        void step_motor(int steps, uint16_t speed);

        static stepper_timer_t timer3;

        static stepper_timer_t timer4;
        
        static stepper_timer_t timer5;

    private:
        STEPPER_TIMER_CHANNEL timer_num;

        void init_timer3();

        void init_timer4();

        void init_timer5();

        void start_timer();

        void stop_timer();
        
        
        
};
#endif