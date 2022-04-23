#include "BUK1_H.h"
#include "Arduino.h";
#include "Servo.h";
#include "string"

//Motor functions here
inline void set_speed(pin spdPin, bit bitspeed){
    analogWrite(spdPin, bitspeed);
}

inline void set_brakes(pin brkPin, int state){
    digitalWrite(brkPin, state);
}

inline void set_direction(pin dirPin, int state){
    digitalWrite(dirPin, state)
}

//Servo functions here
Servo PenServo;

inline void servo_goto(bit angle){
    PenServo.write(angle);
    delay(15);
}

inline void servo_up(){
    servo_goto(_SERVO_TOP);
}

inline void servo_down(){
    servo_goto(_SERVO_BOTTOM);
}

inline bit servo_angle(){
    return PenServo.read();
}

//Math functions here


BUKPlt::BUKPlt(){
    xpos = ypos = -1.0f;
    
    TIME_MAX = 10000000;
    _BRAKE_A = 9;
    _BRAKE_B = 8;
    _SPEED_A = 3;
    _SPEED_B = 11;
    _DIR_A = 12;
    _DIR_B = 13;
    _SERVO_LATCH = 4;
    _BUTTON_XTOP = 0;
    _BUTTON_XBTM = 0;
    _BUTTON_YTOP = 0;
    _BUTTON_YBTM = 0;

    xforward = HIGH;
    xback = LOW;
    yforward = HIGH;
    yback = LOW;
    Serial.println("Initializing Plotter");
    pinMode(_SPEED_A, OUTPUT);
    pinMode(_DIR_A, OUTPUT);
    pinMode(_BRAKE_A, OUTPUT);
    pinMode(_SPEED_B, OUTPUT);
    pinMode(_DIR_B, OUTPUT);
    pinMode(_BRAKE_B, OUTPUT);

    set_brakes(_BRAKE_A, HIGH);
    set_brakes(_BRAKE_B, HIGH);
    
    PenServo.attach(_SERVO_LATCH);

    pinMode(_BUTTON_XTOP, INPUT);
    pinMode(_BUTTON_XBTM, INPUT);
    pinMode(_BUTTON_YTOP, INPUT);
    pinMode(_BUTTON_YBTM, INPUT);
}

BUKPlt::~BUKPlt(){
    Serial.println("Plotter object destroyed");
}

void BUKPlt::servosetup(){
    Serial.println("SETUP || Please make sure the servo horn is detached!");
    delay(1000);
    servo_goto(0);
    for (int i = 0; i < 19; i++){
        //welcome to the waiting queue
        servo_goto(i*10);
        Serial.print("SETUP || Current angle: ")
        Serial.println(i*10);
        delay(500);
    }
    Serial.println("SETUP || Please modify _SERVO_TOP and _SERVO_BOTTOM in BUK1_H.h accordingly");
}

bool BUKPlt::calibrate(bit bitspeed){
    Serial.println("SETUP || General Calibration commenced");
    servo_up();
    int instance = testmotorA(bitspeed);
}

int BUKPlt::testmotorA(bit bitspeed){
    set_brakes(_BRAKE_A, HIGH);
    set_brakes(_BRAKE_B, HIGH);

    set_direction(_DIR_A)
}



