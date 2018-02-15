#include <math.h>
#include "vec2.h"

Vec2::Vec2()
    : x(0.0f), y(0.0f)
{}


Vec2::Vec2(float pX, float pY)
    : x(pX), y(pY)
{}


Vec2::Vec2(const Vec2& vec)
    : x(vec.x), y(vec.y)
{}


Vec2& Vec2::operator=(const Vec2& vec)
{
    x = vec.x;
    y = vec.y;
    return *this;
}


float Vec2::length() const
{
    return sqrtf(x * x + y * y);
}


Vec2& Vec2::normalize()
{
    float l = length();
    if (l != 0.0f)
    {
        x /= l;
        y /= l;
    }
    return *this;
}


bool Vec2::operator==(const Vec2& vec) const
{
    return x == vec.x && y == vec.y;
}


bool Vec2::operator!=(const Vec2& vec) const
{
    return !(*this == vec);
}


Vec2 Vec2::operator+(float n) const
{
    return Vec2(x + n, y + n);
}


Vec2 Vec2::operator*(float n) const
{
    return Vec2(x * n, y * n);
}


void Vec2::operator+=(float n)
{
    x += n;
    y += n;
}


Vec2 Vec2::operator+(const Vec2& vec) const
{
    return Vec2(x + vec.x, y + vec.y);
}


Vec2 Vec2::operator-(const Vec2& vec) const
{
    return Vec2(x - vec.x, y - vec.y);
}


void Vec2::operator+=(const Vec2& vec)
{
    x += vec.x;
    y += vec.y;
}


float Vec2::length(const Vec2& vec)
{
    return vec.length();
}


Vec2& Vec2::normalize(Vec2&& vec)
{
    return vec.normalize();
}


int Vec2::toCardinalDirection8(const Vec2& vec)
{
    return (static_cast<int>(
        std::round(atan2(vec.x, vec.y) / (2.0f * M_PI / 8.0f))) + 8) % 8;
}


Vec2& Vec2::clamp(Vec2&& vec, float mag)
{
    if (vec.length() > mag)
        vec = vec.normalize() * mag;
    return vec;
}