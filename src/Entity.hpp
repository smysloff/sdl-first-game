#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>

#include "Point.hpp"

class Entity
{
public:
    Point position;
    Point waypoint;
    double speed;
    Point velocity = Point(0, 0);
    double angle = 0;

    Entity(double x, double y, double speed);

    void setPosition(double x, double y);
    void setWaypoint(double x, double y);
    void update(double deltatime);
    void move(double deltatime);
    bool isMoving();
    std::string logPosition();
    std::string logWaypoint();

protected:
    void UpdateAngle();
};
