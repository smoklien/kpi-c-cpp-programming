#pragma once

#include "..\header\utils.hpp"

class Triangle
{
private:
    float side_a_;
    float side_b_;
    float side_c_;

    void AreSidesValid();
    void DoSidesFormTriangle();
    void AreSidesWithinLimits();

public:
    Triangle(float, float, float);
    Triangle(const Triangle &);
    Triangle(float, float);

    void ValidateTriangle();

    float CalculateAreaHeron() const;
    float CalculateAreaEqual() const;

    float GetSideA() const;
    float GetSideB() const;
    float GetSideC() const;

    Triangle operator++();
    Triangle operator++(int);
    Triangle operator+=(float);
    Triangle operator--();
    Triangle operator--(int);
    Triangle operator-=(float);
};