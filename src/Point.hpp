#pragma once

#include <iostream>
#include <sstream>

class Point
{
public:
    double x = 0;
    double y = 0;

    Point() = default;
    Point(double x, double y): x(x), y(y) {}

    void set(double x, double y);
    std::string log();
};
