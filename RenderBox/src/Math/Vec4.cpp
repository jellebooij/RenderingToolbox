#include "Vec4.h"
#include "Mat4.h"


namespace Rb {


	Vec4::Vec4() : x(.0f), y(.0f), z(.0f), w(.0f) {}

	Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	Vec4::Vec4(const Vec3 & a) : x(a.x), y(a.y), z(a.z), w(1.0f) {}

	Vec4::Vec4(const Vec4& a) : x(a.x), y(a.y), z(a.z), w(a.w) {}

	float Vec4::Magnitude() const
	{
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	float Vec4::MagnitudeSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	void Vec4::Normalize()
	{
		float m = Magnitude();

		x /= m;
		y /= m;
		z /= m;
		w /= m;
	}

	float Vec4::Dot(const Vec4 & a)
	{
		return x * a.x + y * a.y + z * a.z + w * a.w;
	}

	Vec4 Vec4::Multiply(const Mat4 & transform)
	{
		Vec4 input = *this;
		Vec4 result;

		result.x = input.x * transform.data[0] + input.y * transform.data[1] + input.z * transform.data[2] + input.w * transform.data[3];
		result.y = input.x * transform.data[4] + input.y * transform.data[5] + input.z * transform.data[6] + input.w * transform.data[7];
		result.z = input.x * transform.data[8] + input.y * transform.data[9] + input.z * transform.data[10] + input.w * transform.data[11];
		result.w = input.x * transform.data[12] + input.y * transform.data[13] + input.z * transform.data[14] + input.w * transform.data[15];

		return result;
	}

	const Vec4 & Vec4::operator+() const
	{
		return *this;
	}

	Vec4 Vec4::operator-() const
	{
		return Vec4(-x, -y, -z, -w);
	}

	Vec4 & Vec4::operator+=(const Vec4 & a)
	{

		x += a.x;
		y += a.y;
		z += a.z;
		w += a.w;

		return *this;
	}

	Vec4 & Vec4::operator-=(const Vec4 & a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		w -= a.w;

		return *this;
	}

	Vec4 & Vec4::operator*=(const Mat4 & a)
	{
		return *this = Multiply(a);
	}

	Vec4 & Vec4::operator=(const Vec4 & a)
	{

		x = a.x;
		y = a.y;
		z = a.z;
		w = a.w;


		return *this;
	}

	bool Vec4::operator==(const Vec4 & a)
	{
		return (x == a.x && y == a.y && z == a.z && w == a.w);
	}

	bool Vec4::operator!=(const Vec4 & a)
	{
		return !((*this) == a);
	}


	Vec4 operator+(const Vec4 & a, const Vec4 &b)
	{
		return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	Vec4 operator-(const Vec4 & a, const Vec4 &b)
	{
		return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

}