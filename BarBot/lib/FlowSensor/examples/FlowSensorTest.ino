/**
 * @file FlowSensorTest.ino
 * @author Tristan Cavarno
 * @date 1/29/23
 * 
 * @version 1.0
 * 
 * @brief Code ripped of a wiki for the GREDIA 1/4" flow sensor.
 * This is an arduino sketch used to generate the logic for the FlowSensor
 * class.
 */

// reading liquid flow rate using Seeeduino and Water Flow Sensor from hotmcu.com
// Code adapted by Charles Gantt from PC Fan RPM code written by Crenn @thebestcasescenario.com
// http:/themakersworkbench.com http://thebestcasescenario.com http://hotmcu.com
 
volatile int NbTopsFan;                       // measuring the rising edges of the signal
int Calc;
int hallsensor = 2;                           // The pin location of the sensor

#define DIR_PIN 3
#define MAG_PIN 4

 
void rpm ()                                   // This is the function that the interupt calls
{
    NbTopsFan++;                              // This function measures the rising and falling edge of the hall effect sensors signal
}
 
 
void setup()
{
    pinMode(MAG_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    NbTopsFan=0;
    pinMode(hallsensor, INPUT);               // initializes digital pin 2 as an input
    Serial.begin(9600);                       // This is the setup function where the serial port is initialised,
    attachInterrupt(0, rpm, RISING);          // and the interrupt is attached
}
 
 
void loop ()
{
    digitalWrite(DIR_PIN,LOW);
    digitalWrite(MAG_PIN,LOW);
    //NbTopsFan = 0;                            // Set NbTops to 0 ready for calculations
 
    sei();                                    // Enables interrupts
    delay (200);                             // Wait 1 second
    cli();                                    // Disable interrupts
  
    Serial.print (NbTopsFan);                 // Prints the number calculated above
 
    Serial.print (" Ticks\n");             // Prints "L/hour" and returns a  new line
}
