#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <cassert>
#include <SFML/Graphics/CircleShape.hpp>
#include "engine/Vector.h"
#include "engine/utils.h"
#include "engine/Component.h"

class CTransform : public Component
{
public:
    Vector2D position;
    Vector2D velocity;
    float angle = 0.0f;

    CTransform() = default;
    CTransform(const Vector2D& in_position, const Vector2D& in_velocity, const float in_angle)
	: position(in_position), velocity(in_velocity), angle(in_angle)
    {
    }
};

class CShape : public Component
{
public:
    sf::CircleShape shape;

    CShape() = default;
    CShape(const int radius, 
	   const float fill_color[3],
	   const float outline_color[3],
	   const float outline_thickness,
	   const int vertices)
    {
	shape.setRadius(static_cast<float>(radius));
	shape.setPointCount(vertices);
	shape.setFillColor(utils::floats_to_sfcolor(fill_color));
	shape.setOutlineColor(utils::floats_to_sfcolor(outline_color));
	shape.setOutlineThickness(outline_thickness);

	assert(shape.getRadius() == radius);
    }
};

#endif
