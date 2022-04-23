#if !defined(__cplusplus)
    #error
#endif

#ifndef BUK1_H_
#define BUK1_H_

#include "Arduino.h";
#include "Servo.h";

typedef byte pin;
typedef unsigned int bit;

//Various angles and such
#define _SERVO_TOP      180
#define _SERVO_BOTTOM   0

//in mm
const double R_GEAR = 27;
const double R_PULLEY = 10;

#define SPEED_TO_BITS(s) ((28.97 + 3.402 * (s)-0.1736 * sq(s) + 0.003101 * cube(s)) * 67.7)
#define BITS_TO_SPEED(s) (1.012e-5 * cube(s) - 6.19e-3 * sq(s) + 1.332 * s - 37.24)

//Motor functions here
inline void set_speed(pin spdPin, bit bitspeed);
inline void set_brakes(pin brkPin, int state);
inline void set_direction(pin dirPin, int state);

//Servo functions here
inline void servo_goto(bit angle);
inline void servo_up();
inline void servo_down();
inline bit servo_angle();

//Math functions here

class BUKPlt{
    private:
        float xpos = 0.0f, ypos = 0.0f;
        int xforward, xback, yforward, yback;
        unsigned long int TIME_MAX;
        pin _BRAKE_A, _BRAKE_B, _SPEED_A, _SPEED_B, _DIR_A, _DIR_B, _SERVO_LATCH, _BUTTON_XTOP, _BUTTON_XBTM, _BUTTON_YTOP, _BUTTON_YBTM;

        void flipmotors();
        void flipdirection();
    public:
        BUKPlt();
        BUKPlt(BUKPlt &&) = default;
        BUKPlt(const BUKPlt &) = default;
        BUKPlt &operator=(BUKPlt &&) = default;
        BUKPlt &operator=(const BUKPlt &) = default;
        ~BUKPlt();

        void servosetup();
        bool calibrate(bit bitspeed);
        int iscorrectmotor(bit bitspeed);
        int iscorrectdirectionA(bit bitspeed);
        int iscorrectdirectionB(bit bitspeed);
        int calibratecorner(bit bitspeed);
        bool readinstructions(const filename& nameoffile);

        bool drawlineto(float x, float y);
};

#endif