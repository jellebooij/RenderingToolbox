#include "Quaternion.h"
#include <cmath>

Quaternion::Quaternion() : x(.0f), y(.0f), z(.0f), w(.0f) {}

Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Quaternion::Quaternion(const Quaternion & a) : x(a.x), y(a.y), z(a.z), w(a.w) {}

float Quaternion::Length()
{
	return std::sqrt(x * x + y * y + z * z + w * w);
}

Quaternion & Quaternion::Normalize()
{
	float length = Length();

	x /= length;
	y /= length;
	z /= length;
	w /= length;

	return *this;

}

Quaternion Quaternion::Conjugate()
{
	return Quaternion(-x,-y,-z,w);
}

Quaternion Quaternion::Multiply(const Quaternion & a)
{
	Quaternion newQuat;
	
	newQuat.x = x  * a.w + y * a.z - z * a.y + w * a.x;
	newQuat.y = -x * a.z + y * a.w + z * a.x + w * a.y;
	newQuat.z = x  * a.y - y * a.x + z * a.w + w * a.z;
	newQuat.w = -x * a.x - y * a.y - z * a.z + w * a.w;

	newQuat.Normalize();
	

	return newQuat;
}

Quaternion Quaternion::AngleAxis(float angle, const Vec3 & axis)
{
	Quaternion result;

	angle = angle * 0.01745329251f;

	Vec3 copy = axis.Normalized();

	double s = std::sin(angle / 2);

	result.x = copy.x * s;
	result.y = copy.y * s;
	result.z = copy.z * s;
	result.w = std::cos(angle / 2);

	return result;
}

Quaternion & Quaternion::operator=(const Quaternion & a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	w = a.w;

	return *this;
}
