#include "BUK1_H.h"
#include "Arduino.h";
#include "Servo.h";
#include "string"

//Motor functions here
inline void set_speed(pin motorPin, bit bitspeed){
    analogWrite(motorPin, bitspeed);
}

inline void set_brakes(pin motorPin, int state){
    digitalWrite(motorPin, state);
}

//Servo functions here
Servo PenServo;

inline void servo_goto(bit angle){
    PenServ
}


//Math functions here


BUKPlt::BUKPlt(){
    xpos = ypos = -1.0f;
    Serial.println("Initializing Plotter");
    pinMode(_SPEED_A, OUTPUT);
    pinMode(_DIR_A, OUTPUT);
    pinMode(_BRAKE_A, OUTPUT);
    pinMode(_SPEED_B, OUTPUT);
    pinMode(_DIR_B, OUTPUT);
    pinMode(_BRAKE_B, OUTPUT);

    set_brakes(_BRAKE_B, HIGH);
    set_brakes(_BRAKE_A, HIGH);
    
    PenServo.attach(_SERVO_LATCH);
}

BUKPlt::~BUKPlt(){
    Serial.println("Plotter object destroyed");
}

BUKPlt::coordset()



