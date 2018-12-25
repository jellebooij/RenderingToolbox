#pragma once

#include "Vec3.h"
#include "Vec4.h"
#include "Quaternion.h"
#include <string>

class Mat4 {

public:
	
	float data[4 * 4];

	Mat4();
	Mat4(float diagonal);
	Mat4(float* data);

	void SetColumn(unsigned int index, const Vec4& column);
	Vec4 GetColumn(unsigned int index) const;

	Mat4& Multiply(const Mat4& a);

	float* DataPointer() { return data; }

	static Mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);
	static Mat4 Perspective(float fov, float aspectRatio, float near, float far);
	static Mat4 LookAt(const Vec3& camera, const Vec3& object, const Vec3& up);
	
	static Mat4 Translate(const Vec3& translation);
	static Mat4 Rotate(float angle, const Vec3& axis) ;
	static Mat4 Rotate(const Quaternion& quat);
	static Mat4 Scale(const Vec3& scale);

	Mat4& operator*= (const Mat4& a);

	friend Mat4 operator*  (const Mat4& a, const Mat4& b);
	friend Vec4 operator*  (const Mat4& a, const Vec4& b);
	
};