#pragma once
#include "Vec3.h"

class Quaternion {

public:

	float x, y, z, w;

	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Quaternion& a);

	float Length();
	Quaternion& Normalize();
	Quaternion Conjugate();

	Quaternion Multiply(const Quaternion& a);

	

	static Quaternion AngleAxis(float angle, const Vec3& axis);
	static Quaternion Slerp(Quaternion a, Quaternion b, float t);

	Quaternion& operator=(const Quaternion &a);

};