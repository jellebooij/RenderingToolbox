#include "Vec3.h"

Vec3::Vec3() : x(.0f), y(.0f), z(.0f) {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3::Vec3(const Vec3 & a) : x(a.x), y(a.y), z(a.z) {}

float Vec3::Magnitude() const
{
	return std::sqrt(x * x + y * y + z * z);
}

float Vec3::MagnitudeSquared() const
{
	return x * x + y * y + z * z;
}

void Vec3::Normalize()
{
	float m = Magnitude();

	x /= m;
	y /= m;
	z /= m;
}

Vec3 Vec3::Normalized() const
{
	Vec3 copy = *this;

	copy.Normalize();

	return copy;
}

float Vec3::Dot(const Vec3 & a)
{
	return x * a.x + y * a.y + z * a.z;
}

Vec3 Vec3::Cross(const Vec3 & a)
{
	return Vec3(
		y * a.z - z * a.y,
		z * a.x - x * a.z,
		x * a.y - y * a.x);
}

float Vec3::Distance(const Vec3 & a)
{
	return ((*this) - a).Magnitude();
}

const Vec3 & Vec3::operator+() const
{
	return *this;
}

Vec3 Vec3::operator-() const
{
	return Vec3(-x, -y, -z);
}


Vec3 & Vec3::operator+=(const Vec3 & a)
{
	x += a.x;
	y += a.y;
	z += a.z;

	return *this;
}

Vec3 & Vec3::operator-=(const Vec3 & a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;

	return *this;
}

Vec3 & Vec3::operator=(const Vec3 & a)
{
	
	x = a.x;
	y = a.y;
	z = a.z;


	return *this;
}

bool Vec3::operator==(const Vec3 & a)
{	
	return (x == a.x && y == a.y && z == a.z);
}

bool Vec3::operator!=(const Vec3 & a)
{
	return !((*this) == a);
}


Vec3 operator+(const Vec3 & a, const Vec3 & b)
{
	return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3 & a, const Vec3 & b)
{
	return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator*(const Vec3 & a, const float & b)
{
	return Vec3(a.x * b, a.y * b, a.z * b);
}

Vec3 operator*(const float & a, const Vec3 & b)
{
	return Vec3(b.x * a, b.y * a, b.z * a);
}


