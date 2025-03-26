#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "../../engine/Vector.h"

class CTransform
{
public:
    Vector2D position;
    Vector2D velocity;
    float angle = 0.0f;

    CTransform(const Vector2D& in_position, const Vector2D& in_velocity, const float in_angle)
	: position(in_position), velocity(in_velocity), angle(in_angle)
    {}
};

#endif
