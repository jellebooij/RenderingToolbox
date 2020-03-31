#include "VirtualCamera.h"

namespace Rb {

	VirtualCamera::VirtualCamera()
	{
		fov = 70;
		aspectRatio = 1.5f;
		nearPlane = 0.01f;
		farPlane = 100.0f;

		position = Vec3(.0f, .0f, .0f);
		rotation = Quaternion::Identity();

		projectionMatrix = Mat4::Perspective(fov, aspectRatio, nearPlane, farPlane);
		viewMatrix = Mat4::Translate(-position) * Mat4::Rotate(rotation);

	}

	Mat4 VirtualCamera::GetProjectionMatrix()
	{
		return projectionMatrix;
	}

	Mat4 VirtualCamera::GetViewMatrix()
	{
		viewMatrix = Mat4::Translate(-position) * Mat4::Rotate(rotation);
		return viewMatrix;
	}

	void VirtualCamera::SetPosition(const Vec3 & position)
	{
		this->position = position;
	}

	void VirtualCamera::SetRotation(const Quaternion & rotation)
	{
		this->rotation = rotation;
	}

	void VirtualCamera::Translate(const Vec3 & translation)
	{

		Vec4 trans(translation);

		trans = trans.Multiply(Mat4::Rotate(rotation));

		this->position += Vec3(trans.x, trans.y, trans.z);
	}

	void VirtualCamera::Rotate(const Quaternion & rotation)
	{
		this->rotation *= rotation;
	}

}
