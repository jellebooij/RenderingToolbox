#include "Mat4.h"

namespace Rb {

	Mat4::Mat4()
	{
		memset(data, 0, 4 * 4 * sizeof(float));
	}

	Mat4::Mat4(float diagonal)
	{
		memset(data, 0, 4 * 4 * sizeof(float));

		data[0] = diagonal;
		data[5] = diagonal;
		data[10] = diagonal;
		data[15] = diagonal;
	}

	Mat4::Mat4(float* data)
	{
		memcpy(this->data, data, 16 * sizeof(float));
	}

	void Mat4::SetColumn(unsigned int index, const Vec4 & column)
	{
		data[index * 4] = column.x;
		data[index * 4 + 1] = column.y;
		data[index * 4 + 2] = column.z;
		data[index * 4 + 3] = column.w;
	}

	Vec4 Mat4::GetColumn(unsigned int index) const
	{
		return Vec4(data[index * 4], data[index * 4 + 1], data[index * 4 + 2], data[index * 4 + 3]);
	}

	Mat4 & Mat4::Multiply(const Mat4 & a)
	{
		float temp[16];

		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += a.data[row + e * 4] * data[e + col * 4];
				}
				temp[row + col * 4] = sum;
			}
		}

		memcpy(data, temp, 4 * 4 * sizeof(float));

		return *this;
	}

	float* Mat4::DataPointer() const
	{
		return (float*)data;
	}

	Mat4 Mat4::Orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		Mat4 orthoMat;

		orthoMat.data[0] = 2.0f / (right - left);
		orthoMat.data[5] = 2.0f / (top - bottom);
		orthoMat.data[10] = -2.0f / (far - near);
		orthoMat.data[15] = 1.0f;

		orthoMat.data[12] = -((right + left) / (right - left));
		orthoMat.data[13] = -((top + bottom) / (top - bottom));
		orthoMat.data[14] = -((far + near) / (far - near));

		return orthoMat;
	}

	Mat4 Mat4::Perspective(float fov, float aspectRatio, float near, float far)
	{
		Mat4 perspectiveMat;

		perspectiveMat.data[0] = 1.0f / (aspectRatio * std::tan(fov / 2));
		perspectiveMat.data[5] = 1.0f / (std::tan(fov / 2));
		perspectiveMat.data[10] = -((near + far) / (far - near));
		perspectiveMat.data[11] = -1.0f;
		perspectiveMat.data[14] = -((2 * far * near) / (far - near));

		return perspectiveMat;
	}

	Mat4 Mat4::LookAt(const Vec3 & camera, const Vec3 & object, const Vec3 & up)
	{
		Mat4 result(1.0f);

		Vec3 f = (object - camera).Normalized();
		Vec3 s = f.Cross(up.Normalized());
		Vec3 u = s.Cross(f);

		result.data[0] = s.x;
		result.data[1] = s.y;
		result.data[2] = s.z;

		result.data[4] = u.x;
		result.data[5] = u.y;
		result.data[6] = u.z;

		result.data[8] = -f.x;
		result.data[9] = -f.y;
		result.data[10] = -f.z;

		return result * Translate(Vec3(-camera.x, -camera.y, -camera.z));
	}

	Mat4 Mat4::Translate(const Vec3 & translation)
	{
		Mat4 transMat(1.0f);

		transMat.data[12] = translation.x;
		transMat.data[13] = translation.y;
		transMat.data[14] = translation.z;

		return transMat;
	}

	Mat4 Mat4::Rotate(float angle, const Vec3 & axis)
	{

		Mat4 rotMat;

		angle = angle * 0.01745329251f;

		Vec3 a = axis.Normalized();
		float co = std::cos(angle);
		float si = std::sin(angle);


		rotMat.data[0] = a.x * a.x * (1 - co) + co;
		rotMat.data[1] = a.x * a.y * (1 - co) + a.z * si;
		rotMat.data[2] = a.x * a.z * (1 - co) - a.y * si;

		rotMat.data[4] = a.x * a.y * (1 - co) - a.z * si;
		rotMat.data[5] = a.y * a.y * (1 - co) + co;
		rotMat.data[6] = a.y * a.z * (1 - co) + a.x * si;

		rotMat.data[8] = a.z * a.x * (1 - co) + a.y * si;
		rotMat.data[9] = a.z * a.y * (1 - co) - a.x * si;
		rotMat.data[10] = a.z * a.z * (1 - co) + co;

		rotMat.data[15] = 1.0f;

		return rotMat;
	}

	Mat4 Mat4::Rotate(const Quaternion & quat)
	{
		Mat4 rotMat;

		rotMat.data[0] = 1 - 2 * quat.y * quat.y - 2 * quat.z * quat.z;
		rotMat.data[1] = 2 * quat.x * quat.y + 2 * quat.w * quat.z;
		rotMat.data[2] = 2 * quat.x * quat.z - 2 * quat.w * quat.y;

		rotMat.data[4] = 2 * quat.x * quat.y - 2 * quat.w * quat.z;
		rotMat.data[5] = 1 - 2 * quat.x * quat.x - 2 * quat.z * quat.z;
		rotMat.data[6] = 2 * quat.y * quat.z + 2 * quat.w * quat.x;

		rotMat.data[8] = 2 * quat.x * quat.z + 2 * quat.w * quat.y;
		rotMat.data[9] = 2 * quat.y * quat.z - 2 * quat.w * quat.x;
		rotMat.data[10] = 1 - 2 * quat.x * quat.x - 2 * quat.y * quat.y;

		rotMat.data[15] = 1.0f;


		return rotMat;
	}

	Mat4 Mat4::Scale(const Vec3 & scale)
	{
		Mat4 scaleMat(1.0f);

		scaleMat.data[0] = scale.x;
		scaleMat.data[5] = scale.y;
		scaleMat.data[10] = scale.z;

		return scaleMat;
	}

	Mat4 & Mat4::operator*=(const Mat4 & a)
	{
		return Multiply(a);
	}

	Mat4 operator*(const Mat4 & a, const Mat4& b)
	{
		Mat4 newMatrix = a;
		newMatrix.Multiply(b);
		return newMatrix;
	}

	Vec4 operator*(const Mat4 & a, const Vec4 & b)
	{
		Vec4 result = b;
		return result.Multiply(a);
	}

}