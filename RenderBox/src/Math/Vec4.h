#pragma once
#include "Application/Core.h"
#include <cmath>
#include <iostream>
#include "Vec3.h"

namespace Rb {

	class RB_API Vec4 {

	public:

		float x, y, z, w;

		Vec4();
		Vec4(float x, float y, float z, float w);
		Vec4(const Vec3& a);
		Vec4(const Vec4& a);

		float Magnitude() const;
		float MagnitudeSquared() const;
		void  Normalize();
		float Dot(const Vec4& a);

		Vec4 Multiply(const class Mat4& transform);


		const Vec4& operator+() const;
		Vec4 operator-() const;

		friend Vec4 operator+(const Vec4 &a, const Vec4 &b);
		friend Vec4 operator-(const Vec4 &a, const Vec4 &b);

		Vec4& operator+=(const Vec4 &a);
		Vec4& operator-=(const Vec4 &a);
		Vec4& operator*=(const class Mat4 &a);

		Vec4& operator=(const Vec4 &a);

		bool operator==(const Vec4 &a);
		bool operator!=(const Vec4 &a);

	};

}
