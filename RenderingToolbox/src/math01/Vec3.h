#pragma once
#include <cmath>
#include <iostream>

class Mat4;

class Vec3 {

public:

	float x, y, z;

	Vec3();
	Vec3(float x, float y, float z);
	Vec3(const Vec3& a);
	
	float Magnitude() const;
	float MagnitudeSquared() const;
	void  Normalize();
	Vec3  Normalized() const;

	float Dot(const Vec3& a);
	Vec3  Cross(const Vec3& a);
	float Distance(const Vec3& a);

	const Vec3& operator+() const;
	Vec3 operator-() const;

	friend Vec3 operator+(const Vec3 & a, const Vec3 & b);
	friend Vec3 operator-(const Vec3 & a, const Vec3 & b);

	friend Vec3 operator*(const Vec3 & a, const float & b);
	friend Vec3 operator*(const float& a, const Vec3 & b);

	Vec3& operator+=(const Vec3 &a);
	Vec3& operator-=(const Vec3 &a);

	Vec3& operator=(const Vec3 &a);

	bool operator==(const Vec3 &a);
	bool operator!=(const Vec3 &a);

};


