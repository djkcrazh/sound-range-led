// 1 LIBRARIES, INITIAL SETTINGS AND DEFINITIONS
#include "math.h"
#include <Particle.h>

//--------------------------------------------------
// 1.1 DEVICE VARIABLES AND FUNCTIONS DECLARATIONS

int sample_rate = .01 * 1000; //milliseconds (10 ms between checks)
int hold_time = 1 * 1000;     //milliseconds the LED stays on after the signal goes off (1 second)

//1.2 USER VARIABLES TO SET
int s1pin = A0;  //sound sensor 1 OUT pin (pot set to the LOWER sound level)
int s2pin = A1;  //sound sensor 2 OUT pin (pot set to the HIGHER sound level)
int LEDpin = A2; //LED pin (LEDpin->~100-200ohm resistor->Ground)

int s1reading = 0;
int s2reading = 0;
int ledstate = 0;
int holdcount = 0;                      //loops left to keep the LED on
int holdloops = hold_time / sample_rate; //how many loops make up the hold time (100)

int inRange(int, int);
void lightControl(int, int);

//--------------------------------------------------
// 2 SETUP - RUNS ONLY ONCE
void setup() 
{
    // 2.1 WHICH PINS ARE INPUT, WHICH ARE OUTPUT
    pinMode(s1pin, INPUT);   // input from sound sensor 1
    pinMode(s2pin, INPUT);   // input from sound sensor 2
    pinMode(LEDpin, OUTPUT); // output to the LED

    // 2.2 THE STATUS FOR THE VARIABLES THAT YOU WANT REPORTED IN THE PARTICLE CONSOLE / PHONE APP
    Particle.variable("s1_reading", s1reading);
    Particle.variable("s2_reading", s2reading);
    Particle.variable("LED_state", ledstate);
    // 2.3 FUNCTIONS THAT YOU CAN ACTUATE OR EDIT DIRECTLY IN PARTICLE CONSOLE / PHONE APP 
}

//--------------------------------------------------
// 3 LOOP 
void loop() 
{
    s1reading = digitalRead(s1pin);  // LOW = sound detected, HIGH = quiet
    s2reading = digitalRead(s2pin);

    int shouldBeOn = inRange(s1reading, s2reading);  // 1 = sound is in range right now
    lightControl(shouldBeOn, LEDpin);                // runs every loop, handles the hold

    delay(sample_rate);
}

//--------------------------------------------------
// 4 FUNCTIONS
// 4.1 Check whether the light should be on (does NOT touch the LED)
// Returns 1 when sensor 1 hears sound (LOW) and sensor 2 does not (HIGH), otherwise 0
int inRange(int firstReading, int secondReading) 
{
    if (firstReading == LOW && secondReading == HIGH) {
        return 1;
    }
    else {
        return 0;
    }
}

// 4.2 Control the light, keeping it on for the hold time after the signal goes off
void lightControl(int shouldBeOn, int lightPin) 
{
    if (shouldBeOn == 1) {
        holdcount = holdloops;      // signal is on: restart the hold timer
    }
    else if (holdcount > 0) {
        holdcount = holdcount - 1;  // signal is off: count down the extra second
    }

    if (holdcount > 0) {
        digitalWrite(lightPin, HIGH);
        ledstate = 1;
    }
    else {
        digitalWrite(lightPin, LOW);
        ledstate = 0;
    }
}
