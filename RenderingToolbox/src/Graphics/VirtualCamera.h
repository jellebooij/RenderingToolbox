#pragma once
#include "Math/Mat4.h"

class VirtualCamera {
public:
	VirtualCamera();

	Mat4 GetProjectionMatrix();
	Mat4 GetViewMatrix();

	void SetPosition(const Vec3& position);
	void SetRotation(const Quaternion& rotation);

	void Translate(const Vec3& translation);
	void Rotate(const Quaternion& rotation);

private:

	float fov;
	float aspectRatio;
	float nearPlane;
	float farPlane;

	Vec3 position;
	Quaternion rotation;

	Mat4 projectionMatrix;
	Mat4 viewMatrix;


};