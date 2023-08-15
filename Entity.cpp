#include "Entity.h"

Entity::Entity(double x, double y, double speed = 0)
    : position(x, y), waypoint(x, y), speed(speed)
{
    UpdateAngle();
}

void Entity::setPosition(double x, double y)
{
    position.set(x, y);
}

void Entity::setWaypoint(double x, double y)
{
    waypoint.set(x, y);
    UpdateAngle();
}

void Entity::update(double deltatime)
{
    if (isMoving())
        move(deltatime);
    else
        UpdateAngle();
}

void Entity::move(double deltatime)
{
    double x = position.x;
    double y = position.y;

    if (position.x != waypoint.x)
        x = position.x + std::cos(angle) * speed * deltatime;

    if (position.y != waypoint.y)
        y = position.y + std::sin(angle) * speed * deltatime;

    if (
        (position.x < waypoint.x && x > waypoint.x)
        || (position.x > waypoint.x && x < waypoint.x)
    ) {
        x = waypoint.x;
    }

    if (
        (position.y < waypoint.y && y > waypoint.y)
        || (position.y > waypoint.y && y < waypoint.y)
    ) {
        y = waypoint.y;
    }

    position.set(x, y);
}

bool Entity::isMoving()
{
    return (position.x != waypoint.x || position.y != waypoint.y);
}

std::string Entity::logPosition()
{
    return position.log();
}

std::string Entity::logWaypoint()
{
    return waypoint.log();
}

void Entity::UpdateAngle()
{
    double dx = waypoint.x - position.x;
    double dy = waypoint.y - position.y;
    angle = std::atan2(dy, dx);
}
