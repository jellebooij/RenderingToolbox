#include "Quaternion.h"
#include <cmath>

namespace Rb {

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
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion Quaternion::Multiply(const Quaternion & a)
	{
		Quaternion newQuat;

		newQuat.x = x * a.w + y * a.z - z * a.y + w * a.x;
		newQuat.y = -x * a.z + y * a.w + z * a.x + w * a.y;
		newQuat.z = x * a.y - y * a.x + z * a.w + w * a.z;
		newQuat.w = -x * a.x - y * a.y - z * a.z + w * a.w;

		newQuat.Normalize();


		return newQuat;
	}

	Quaternion Quaternion::AngleAxis(float angle, const Vec3 & axis)
	{
		Quaternion result;

		angle = angle * 0.01745329251f;

		Vec3 copy = axis.Normalized();

		float s = std::sin(angle / 2);

		result.x = copy.x * s;
		result.y = copy.y * s;
		result.z = copy.z * s;
		result.w = std::cos(angle / 2);

		return result;
	}

	Quaternion Quaternion::EurlerAngles(Vec3 angles)
	{

		angles = angles * 0.01745329251f;

		float heading = angles.y;
		float attitude = angles.x;
		float bank = angles.z;

		float c1 = std::cos(heading / 2);
		float s1 = std::sin(heading / 2);
		float c2 = std::cos(attitude / 2);
		float s2 = std::sin(attitude / 2);
		float c3 = std::cos(bank / 2);
		float s3 = std::sin(bank / 2);


		float c1c2 = c1 * c2;
		float s1s2 = s1 * s2;
		float w = c1c2 * c3 - s1s2 * s3;
		float x = c1c2 * s3 + s1s2 * c3;
		float y = s1 * c2*c3 + c1 * s2*s3;
		float z = c1 * s2*c3 - s1 * c2*s3;

		return Quaternion(x, y, z, w);
	}

	Quaternion & Quaternion::operator*=(const Quaternion & a)
	{
		Multiply(a);

		return *this;
	}

	Quaternion & Quaternion::operator=(const Quaternion & a)
	{
		x = a.x;
		y = a.y;
		z = a.z;
		w = a.w;

		return *this;
	}

}
