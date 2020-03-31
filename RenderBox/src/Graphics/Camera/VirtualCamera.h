#pragma once
#include "Math/Mat4.h"

namespace Rb {

	class VirtualCamera {
	public:
		VirtualCamera();

		Mat4 GetProjectionMatrix();
		Mat4 GetViewMatrix();

		void SetPosition(const Vec3& position);
		void SetRotation(const Quaternion& rotation);

		void Translate(const Vec3& translation);
		void Rotate(const Quaternion& rotation);
		
		Vec3 position;

	private:

		float fov;
		float aspectRatio;
		float nearPlane;
		float farPlane;

		
		Quaternion rotation;

		Mat4 projectionMatrix;
		Mat4 viewMatrix;


	};

}

