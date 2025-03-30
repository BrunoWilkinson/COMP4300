#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <cassert>
#include <SFML/Graphics/CircleShape.hpp>
#include "engine/Vector.h"
#include "engine/utils.h"

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

class CShape
{
public:
    std::shared_ptr<sf::CircleShape> shape;

    CShape(const int radius, 
	   const float fill_color[3],
	   const float outline_color[3],
	   const float outline_thickness,
	   const int vertices)
    {
	shape = std::make_shared<sf::CircleShape>(radius, vertices);

	assert(shape);

	shape->setFillColor(utils::floats_to_sfcolor(fill_color));
	shape->setOutlineColor(utils::floats_to_sfcolor(outline_color));
	shape->setOutlineThickness(outline_thickness);
    }
};

#endif
