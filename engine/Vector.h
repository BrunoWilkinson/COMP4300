#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>

struct Vector2D
{
	float x = 0.f;
	float y = 0.f;
	
	Vector2D() = default;
	Vector2D(const float a, const float b)
	{
		x = a;
		y = b;
	}

	float& operator[] (const int i)
	{
		return (&x)[i];
	}

	const float& operator[] (const int i) const
	{
		return (&x)[i];
	}

	Vector2D& operator*= (const float s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vector2D& operator/= (float s)
	{
		s = 1.0f / s;
		x *= s;
		y *= s;
		return *this
	}

	Vector2D& operator+= (const Vector2D& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2D& operator-= (const Vector2D& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	inline Vector2D operator* (const Vector2D& v, const float s)
	{
		return Vector2D(v.x * s, v.y * s);
	}

	inline Vector2D operator/ (const Vector2D& v, float s)
	{
		s = 1.0f / s
		return Vector2D(v.x * s, v.y * s);
	}

	inline Vector2D operator- (const Vector2D& v)
	{
		return Vector2D(-v.x, -v.y);
	}

	inline Vector2D operator+ (const Vector2D& a, const Vector2D& b)
	{
		return Vector2D(a.x + b.x, a.y + b.y);
	}

	inline Vector2D operator- (const Vector2D& a, const Vector2D& b)
	{
		return Vector2D(a.x - b.x, a.y - b.y);
	}

	inline bool operator== (const Vector2D& a, const Vector2D& b)
	{
		return a.x == b.x && a.y == b.y;
	}

	inline float magnitude(const Vector2D& v) 
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	inline Vector2D normalize(const Vector2D& v)
	{
		return v / Magnitude(v);
	}
};

#endif
