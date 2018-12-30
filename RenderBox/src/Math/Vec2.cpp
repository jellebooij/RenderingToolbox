#include "Vec2.h"

namespace Rb {

	Vec2::Vec2() : x(.0f), y(.0f) {}

	Vec2::Vec2(float x, float y) : x(x), y(y) {}

	Vec2::Vec2(const Vec2 & a) : x(a.x), y(a.y) {}

	float Vec2::Magnitude() const
	{
		return std::sqrt(x * x + y * y);
	}

	float Vec2::MagnitudeSquared() const
	{
		return x * x + y * y;
	}

	void Vec2::Normalize()
	{
		float m = Magnitude();

		x /= m;
		y /= m;
	}

	Vec2 Vec2::Normalized() const
	{
		Vec2 copy = *this;

		copy.Normalize();

		return copy;
	}

	float Vec2::Dot(const Vec2 & a)
	{
		return x * a.x + y * a.y;
	}


	float Vec2::Distance(const Vec2 & a)
	{
		return ((*this) - a).Magnitude();
	}

	const Vec2 & Rb::Vec2::operator+() const
	{
		return *this;
	}

	Vec2 Vec2::operator-() const
	{
		return Vec2(-x, -y);
	}


	Vec2 & Vec2::operator+=(const Vec2 & a)
	{
		x += a.x;
		y += a.y;

		return *this;
	}

	Vec2 & Vec2::operator-=(const Vec2 & a)
	{
		x -= a.x;
		y -= a.y;

		return *this;
	}

	Vec2 & Vec2::operator=(const Vec2 & a)
	{

		x = a.x;
		y = a.y;

		return *this;
	}

	bool Vec2::operator==(const Vec2 & a)
	{
		return (x == a.x && y == a.y);
	}

	bool Vec2::operator!=(const Vec2 & a)
	{
		return !((*this) == a);
	}


	Vec2 operator+(const Rb::Vec2 & a, const Rb::Vec2 & b)
	{
		return Rb::Vec2(a.x + b.x, a.y + b.y);
	}

	Vec2 operator-(const Rb::Vec2 & a, const Rb::Vec2 & b)
	{
		return Rb::Vec2(a.x - b.x, a.y - b.y);
	}

	Vec2 operator*(const Rb::Vec2 & a, const float & b)
	{
		return Rb::Vec2(a.x * b, a.y * b);
	}

	Vec2 operator*(const float & a, const Rb::Vec2 & b)
	{
		return Rb::Vec2(b.x * a, b.y * a);
	}

}


