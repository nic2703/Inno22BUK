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

void BUKPlt::flipmotors(){
    pin brktemp = _BRAKE_A;
    pin spdtemp = _SPEED_A;
    pin dirtemp = _DIR_A;
    _BRAKE_A = _BRAKE_B;
    _SPEED_A = _SPEED_B;
    _DIR_A = _DIR_B;
    _BRAKE_B = brktemp;
    _SPEED_B = spdtemp;
    _DIR_B = dirtemp;
}

void BUKPlt::flipdirection(int forward, int backward){
    if (forward == HIGH){
        forward = LOW;
        backward = HIGH;
    } else {
        forward = HIGH;
        backward = LOW;
    }
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
    Serial.print("SETUP || Do motors need to be switched?");
    int instance = this->iscorrectmotor(bitspeed);
    switch(instance){
        case -1: {Serial.println("SETUP || ERROR A1: Time limit passed"); return false}
        case 0: {
            Serial.println("SETUP || Motors need to be switched");
            flipmotors();
            break;
        }
        case 1: {Serial.println("SETUP || Motors do not need to be flipped"); break;}
        default: {Serial.println("SETUP || ERROR C1"); return false}
    }

    Serial.print("SETUP || Motor A: Does direction need to be changed?");
    instance = this->iscorrectdirectionA(bitspeed);
    switch(instance){
        case -1: {Serial.println("SETUP || ERROR A1: Time limit passed"); return false}
        case 0: {
            Serial.println("SETUP || Motor A direction needs to be flipped");
            flipdirection(xforward, xback);
            break;
        }
        case 1: {Serial.println("SETUP || Motor A direction do not need to be flipped"); break;}
        default: {Serial.println("SETUP || ERROR C2"); return false}
    }

    Serial.print("SETUP || Motor B: Does direction need to be changed?");
    instance = this->iscorrectdirectionB(bitspeed);
    switch(instance){
        case -1: {Serial.println("SETUP || ERROR A1: Time limit passed"); return false}
        case 0: {
            Serial.println("SETUP || Motor B direction needs to be flipped");
            flipdirection(yforward, yback);
            break;
        }
        case 1: {Serial.println("SETUP || Motor B direction do not need to be flipped"); break;}
        default: {Serial.println("SETUP || ERROR C3"); return false}
    }

    Serial.print("SETUP || Motor Setup Complete, moving to corner");
    instance = this->calibratecorner(bitspeed);
    switch(instance){
        case -2: {Serial.println("SETUP || ERROR A1: Time limit passed on y direction (Motor B)"); return false}
        case -1: {Serial.println("SETUP || ERROR A1: Time limit passed on x direction (Motor A)"); return false}
        case 1: {
            Serial.println("SETUP || Corner successfully reached. Preparing coordinates"); 
            servo_down();
            delay(500);
            servo_up();
            xpos = 0.1f;
            ypos = 0.1f;
            return true
        }
        default: {Serial.println("SETUP || ERROR C4"); return false}
    }

}

int BUKPlt::iscorrectmotor(bit bitspeed){
    set_brakes(_BRAKE_A, HIGH);
    set_brakes(_BRAKE_B, HIGH);

    set_direction(_DIR_A, xback);
    set_speed(_SPEED_A, bitspeed);
    set_brakes(_BRAKE_A, LOW);
    unsigned long int sandclock = micros();
    while (digitalRead(_BUTTON_XBTM) == LOW && digitalRead(_BUTTON_XTOP) == LOW 
    && digitalRead(_BUTTON_YBTM) == LOW && digitalRead(_BUTTON_YTOP) == LOW 
    && micros()<=sandclock+TIME_MAX){
        //welcome to the waiting queue
    }
    set_brakes(_BRAKE_A, HIGH);

    int instance = -2;
    if (micros()>=sandclock+TIME_MAX){
        instance = -1;
    }
    if (digitalRead(_BUTTON_XTOP) == HIGH){
        instance = 1;
    }
    if (digitalRead(_BUTTON_YBTM) == HIGH){
        instance = 0;
    }
    if (digitalRead(_BUTTON_XBTM) == HIGH){
        instance = 1;
    }
    if (digitalRead(_BUTTON_YTOP) == HIGH){
        instance = 0;
    }
    set_direction(_DIR_A, xforward);
    set_brakes(_BRAKE_A, LOW);
    delay(500);
    set_brakes(_BRAKE_A, HIGH);
    return instance;
}

int BUKPlt::iscorrectdirectionA(bit bitspeed){
    set_brakes(_BRAKE_A, HIGH);
    set_brakes(_BRAKE_B, HIGH);

    set_direction(_DIR_A, xback);
    set_speed(_SPEED_A, bitspeed);
    set_brakes(_BRAKE_A, LOW);
    unsigned long int sandclock = micros();
    while (digitalRead(_BUTTON_XBTM) == LOW && digitalRead(_BUTTON_XTOP) == LOW && micros()<=sandclock+TIME_MAX){
        //welcome to the waiting queue
    }
    set_brakes(_BRAKE_A, HIGH);
    
    int instance = -2;
    if (micros()>=sandclock+TIME_MAX){
        instance = -1;
    }
    if (digitalRead(_BUTTON_XTOP) == HIGH){
        instance = 0;
    }
    if (digitalRead(_BUTTON_XBTM) == HIGH){
        instance = 1;
    }
    set_direction(_DIR_A, xforward);
    set_brakes(_BRAKE_A, LOW);
    delay(500);
    set_brakes(_BRAKE_A, HIGH);
    return instance;
}

int BUKPlt::iscorrectdirectionB(bit bitspeed){
    set_brakes(_BRAKE_A, HIGH);
    set_brakes(_BRAKE_B, HIGH);

    set_direction(_DIR_B, yback);
    set_speed(_SPEED_B, bitspeed);
    set_brakes(_BRAKE_B, LOW);
    unsigned long int sandclock = micros();
    while (digitalRead(_BUTTON_YBTM) == LOW && digitalRead(_BUTTON_YTOP) == LOW && micros()<=sandclock+TIME_MAX){
        //welcome to the waiting queue
    }
    set_brakes(_BRAKE_B, HIGH);
    
    int instance = -2;
    if (micros()>=sandclock+TIME_MAX){
        instance = -1;
    }
    if (digitalRead(_BUTTON_YTOP) == HIGH){
        instance = 0;
    }
    if (digitalRead(_BUTTON_YBTM) == HIGH){
        instance = 1;
    }
    set_direction(_DIR_B, yforward);
    set_brakes(_BRAKE_B, LOW);
    delay(500);
    set_brakes(_BRAKE_B, HIGH);
    return instance;
}

int BUKPlt::calibratecorner(bit bitspeed){
    set_brakes(_BRAKE_A, HIGH);
    set_brakes(_BRAKE_B, HIGH);

    set_direction(_DIR_A, xback);
    set_speed(_SPEED_A, bitspeed);
    set_brakes(_BRAKE_A, LOW);
    unsigned long int sandclock = micros();
    while (digitalRead(_BUTTON_XBTM) == LOW && micros()<=sandclock+TIME_MAX){
        //welcome to the waiting queue
    }
    set_brakes(_BRAKE_A, HIGH);

    if (micros()>=sandclock+TIME_MAX){
        return -1
    }
    if (digitalRead(_BUTTON_XBTM) == HIGH){
        set_direction(_DIR_B, yback);
        set_speed(_SPEED_B, bitspeed);
        set_brakes(_BRAKE_B, LOW);
        sandclock = micros();
        while (digitalRead(_BUTTON_YBTM) == LOW && micros()<=sandclock+TIME_MAX){
        //welcome to the waiting queue
        }
        set_brakes(_BRAKE_B, HIGH);

        if (micros()>=sandclock+TIME_MAX){
            return -2;
        }
        if (digitalRead(_BUTTON_YBTM) == HIGH){
            return 1;
        }
        return -3;
    }
    return 0;
}

bool BUKPlt::drawlineto(){
    servo_up();
}


