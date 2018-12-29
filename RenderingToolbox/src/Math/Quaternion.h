#pragma once
#include "Vec3.h"

class Quaternion {

public:

	float x, y, z, w;

	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Quaternion& a);

	static Quaternion Identity() { return Quaternion(1, 0, 0, 0); }

	float Length();
	Quaternion& Normalize();
	Quaternion Conjugate();

	Quaternion Multiply(const Quaternion& a);

	

	static Quaternion AngleAxis(float angle, const Vec3& axis);
	static Quaternion EurlerAngles(Vec3 angles);
	static Quaternion Slerp(Quaternion a, Quaternion b, float t);

	Quaternion& operator*=(const Quaternion &a);

	Quaternion& operator=(const Quaternion &a);
	

};