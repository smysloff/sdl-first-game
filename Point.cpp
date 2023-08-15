#include "Point.h"

void Point::set(double x, double y)
{
    this->x = x;
    this->y = y;
}

std::string Point::log()
{
    std::stringstream ss;
    ss << "{ " << x << ", " << y << " }";
    return ss.str();
}
