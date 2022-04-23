#if !defined(__cplusplus)
    #error
#endif

#ifndef BUK1_H_
#define BUK1_H_

#include "Arduino.h";
#include "Servo.h";
#include "string"

typedef byte pin;
typedef unsigned int bit;
typedef string filename;

#define TIME_MAX        10000000
#define _BRAKE_A        9
#define _BRAKE_B        8
#define _SPEED_A        3 
#define _SPEED_B        11
#define _DIR_A          12
#define _DIR_B          13
#define _SERVO_LATCH    4
#define _SERVO_POTPIN   0       //tbd

//Various angles and such
#define _SERVO_TOP      180
#define _SERVO_BOTTOM   0

//in mm
const double R_GEAR = 27;
const double R_PULLEY = 10;

#define SPEED_TO_BITS(s) ((28.97 + 3.402 * (s)-0.1736 * sq(s) + 0.003101 * cube(s)) * 67.7)
#define BITS_TO_SPEED(s) (1.012e-5 * cube(s) - 6.19e-3 * sq(s) + 1.332 * s - 37.24)

//Motor functions here
inline void set_speed(pin motorPin, bit bitspeed);
inline void set_brakes(pin motorPin, int state);

//Servo functions here
inline void servo_goto(bit angle);
inline bool servo_up();
inline bool servo_down();
inline bit servo_angle();

//Math functions here

class BUKPlt{
    private:
        float xpos = 0.0f, float ypos = 0.0f;
        bool islifted = false;
    public:
        BUKPlt();
        BUKPlt(BUKPlt &&) = default;
        BUKPlt(const BUKPlt &) = default;
        BUKPlt &operator=(BUKPlt &&) = default;
        BUKPlt &operator=(const BUKPlt &) = default;
        ~BUKPlt();

        bool coordset();
        bool readinstructions(const filename& nameoffile);
};

#endif