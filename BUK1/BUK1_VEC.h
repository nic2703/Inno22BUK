#ifndef BUK1_VEC_
#define BUK1_VEC_
#pragma once
//this code is mainly copied from plt_maths.h

#include <Arduino.h>

class BUKvec{
    private:
        float x;
        float y;
    public:
        BUKvec(float init_x, float init_y);
        ~BUKvec();
        BUKvec& operator=(const BUKvec&);
        float& operator[](int i);
        friend bool operator==(const BUKvec vector1, const BUKvec vector2);
        friend bool operator<=(const BUKvec vector1, const BUKvec vector2);
        friend bool operator<(const BUKvec vector1, const BUKvec vector2);
        friend bool operator>=(const BUKvec vector1, const BUKvec vector2);
        friend bool operator>(const BUKvec vector1, const BUKvec vector2);

        friend float& operator*(const BUKvec vector1, const BUKvec vector2);
        friend BUKvec& operator*(const BUKvec vector, const int scalar);
        friend BUKvec& operator*(const BUKvec scalar, const int vector);

        friend BUKvec& operator/(const BUKvec vector, const int divisor);
        friend BUKvec& operator/(const int numerator, const BUKvec vector);

        BUKvec& operator+(const BUKvec vector);
        BUKvec& operator+=(const BUKvec vector);
        BUKvec& operator-(const BUKvec vector);
        BUKvec& operator-=(const BUKvec vector);

        double norm();
};
#endif