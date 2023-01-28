#include <Arduino.h>
#define stepPin 11 
#define dirPin 12 
void setup(){ 

    // Declare pins as Outputs 

    pinMode(stepPin, OUTPUT); 

    pinMode(dirPin, OUTPUT); 

} 


void loop(){ 

    // Set motor direction clockwise 

    digitalWrite(dirPin, HIGH); 

    // Spin motor slowly 

    for(int x = 0; x <1700 ; x++){ 

        digitalWrite(stepPin, HIGH); 

        delayMicroseconds(500); 

        digitalWrite(stepPin, LOW); 

        delayMicroseconds(500); 

    } 

    delay(1000); // Wait a second 

    // Set motor direction counterclockwise 

    digitalWrite(dirPin, LOW); 

    // Spin motor quickly 

    for(int x = 0; x < 1700; x++){ 

        digitalWrite(stepPin, HIGH); 

        delayMicroseconds(500); 

        digitalWrite(stepPin, LOW); 

        delayMicroseconds(500); 

    } 

    delay(1000); // Wait a second 

} 

 
