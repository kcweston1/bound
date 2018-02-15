#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include "constants.h"

class Vec2
{
public:
    Vec2();
    Vec2(float pX, float pY);
    Vec2(const Vec2& vec);
    Vec2& operator=(const Vec2& vec);
    float length() const;
    Vec2& normalize();

    // Operators
    bool operator==(const Vec2& vec) const;
    bool operator!=(const Vec2& vec) const;
    Vec2 operator+(float n) const;
    Vec2 operator*(float n) const;
    void operator+=(float n);
    Vec2 operator+(const Vec2& vec) const;
    Vec2 operator-(const Vec2& vec) const;
    void operator+=(const Vec2& vec);

    // Static conveniency methods.
    static float length(const Vec2& vec);
    static Vec2& normalize(Vec2&& vec);
    static int toCardinalDirection8(const Vec2& vec);
    static Vec2& clamp(Vec2&& vec, float mag);

    // Public members.
    float x;
    float y;
};

#endif