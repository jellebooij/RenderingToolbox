#pragma once
#include "Application/Core.h"
#include <cmath>
#include <iostream>

namespace Rb {

	class RB_API Vec2 {

	public:

		float x, y;

		Vec2();
		Vec2(float x, float y);
		Vec2(const Vec2& a);

		float Magnitude() const;
		float MagnitudeSquared() const;
		void  Normalize();
		Vec2  Normalized() const;

		float Dot(const Vec2& a);
		float Distance(const Vec2& a);

		const Vec2& operator+() const;
		Vec2 operator-() const;

		friend Vec2 operator+(const Vec2 & a, const Vec2 & b);
		friend Vec2 operator-(const Vec2 & a, const Vec2 & b);

		friend Vec2 operator*(const Vec2 & a, const float & b);
		friend Vec2 operator*(const float& a, const Vec2 & b);

		Vec2& operator+=(const Vec2 &a);
		Vec2& operator-=(const Vec2 &a);

		Vec2& operator=(const Vec2 &a);

		bool operator==(const Vec2 &a);
		bool operator!=(const Vec2 &a);

	};

}