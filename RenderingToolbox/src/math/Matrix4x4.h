#pragma once
#include <memory>
#include <GL\glew.h>

class mat4 {

public:
	
	GLfloat data[4 * 4];

	mat4() {
	
		data[0] = 1.0f;
		data[1] = 0.0f;
		data[2] = 0.0f;
		data[3] = 0.0f;

		data[4] = 0.0f;
		data[5] = 1.0f;
		data[6] = 0.0f;
		data[7] = 0.0f;

		data[8] = 0.0f;
		data[9] = 0.0f;
		data[10] = 1.0f;
		data[11] = 0.0f;

		data[12] = 0.0f;
		data[13] = 0.0f;
		data[14] = 0.0f;
		data[15] = 1.0f;
	
	}
	
	void scaleMatrix(float scale) {

		data[0] *= scale;
		data[5] *= scale;
		data[10] *= scale;

	}

	void translateMatrix(float x, float y, float z) {
		
		data[3] += x;
		data[7] += y;
		data[11] += z;


	}

	void rotateMatrix(float xAngle, float yAngle, float zAngle) {

		zAngle = zAngle * 0.01745329251f;
		yAngle = yAngle * 0.01745329251f;
		xAngle = xAngle * 0.01745329251f;

		data[0] = std::cos(yAngle) * std::cos(zAngle);
		data[4] = -std::cos(yAngle) * std::sin(zAngle);
		data[8] = std::sin(yAngle);
		
		
		data[1] = std::cos(xAngle) * std::sin(zAngle) + std::sin(xAngle) * std::sin(yAngle)* std::cos(zAngle);
		data[5] = std::cos(xAngle) * std::cos(zAngle) - std::sin(xAngle) * std::sin(yAngle)* std::sin(zAngle);
		data[9] = -std::sin(xAngle) * std::cos(yAngle);
		
		data[2] = std::sin(xAngle) * std::sin(zAngle) - std::cos(xAngle) * std::sin(yAngle)* std::cos(zAngle);
		data[6] = std::sin(xAngle) * std::cos(zAngle) + std::cos(xAngle) * std::sin(yAngle)* std::sin(zAngle);
		data[10] = std::cos(xAngle) * std::cos(yAngle);

		data[15] = 1.0f;
	}

	void rotateMatrixAngleAxis(float x, float y, float z, float angle) {

		angle = angle * 0.01745329251f;

		float norm = std::sqrt(x*x + y * y + z * z);

		x /= norm;
		y /= norm;
		z /= norm;

		data[0] = x * x * (1 - std::cos(angle)) + std::cos(angle);
		data[4] = x * y * (1 - std::cos(angle)) + z * std::sin(angle);
		data[8] = x * z * (1 - std::cos(angle)) - y * std::sin(angle);

		data[1] = x * y * (1 - std::cos(angle)) -  z * std::sin(angle);
		data[5] = y * y * (1 - std::cos(angle)) + std::cos(angle);
		data[9] = y * z * (1 - std::cos(angle)) + x * std::sin(angle);

		data[2] = z * x * (1 - std::cos(angle)) + y * std::sin(angle);
		data[6] = z * y * (1 - std::cos(angle)) - x * std::sin(angle);
		data[10] = z * z * (1 - std::cos(angle)) + std::cos(angle);

		data[15] = 1.0f;

	}

	void perspectiveProjection(float far, float near, float fov, float aspectRatio) {

		data[0] = 1 / (aspectRatio * std::tan(fov / 2));
		data[5] = 1 / (std::tan(fov / 2));
		data[10] = -((near + far) / (far - near));
		data[11] = -((2 * far * near) / (far - near));
		data[14] = -1;
		data[15] = 0;
	}

	void orthoProj(float left, float right, float top, float bottom, float near, float far) {


		data[0] = 2.0f / (right-left);
		data[5] = 2.0f / (top - bottom);
		data[10] = -2.0f / (far - near);
		data[15] = 1.0f;


		data[3] = -((right + left) / (right - left));
		data[7] = -((top + bottom) / (top - bottom));
		data[11] = -((far + near) / (far - near));
	}

	float  getElement(int i, int j) const { return data[(4 * j) + i]; }
	float* getElementPointer(int i, int j) { return &data[(4 * j) + i]; }
	GLfloat* dataPointer() { return data; }

	float  setElement(int i, int j, float value) { data[(4 * j) + i] = value; }

	mat4& operator*= (const mat4& other) {
		

		GLfloat temp[4 * 4];

		memcpy(temp, data, sizeof(float) * 16);
		
		temp[0] = data[0] * other.data[0] + data[1] * other.data[4] + data[2] * other.data[8 ] +  data[3] * other.data[12];
		temp[1] = data[0] * other.data[1] + data[1] * other.data[5] + data[2] * other.data[9 ] +  data[3] * other.data[13];
		temp[2] = data[0] * other.data[2] + data[1] * other.data[6] + data[2] * other.data[10] +  data[3] * other.data[14];
		temp[3] = data[0] * other.data[3] + data[1] * other.data[7] + data[2] * other.data[11] +  data[3] * other.data[15];


		temp[4] = data[4] * other.data[0] + data[5] * other.data[4] + data[6] * other.data[8] +  data[7] * other.data[12];
		temp[5] = data[4] * other.data[1] + data[5] * other.data[5] + data[6] * other.data[9] +  data[7] * other.data[13];
		temp[6] = data[4] * other.data[2] + data[5] * other.data[6] + data[6] * other.data[10] + data[7] * other.data[14];
		temp[7] = data[4] * other.data[3] + data[5] * other.data[7] + data[6] * other.data[11] + data[7] * other.data[15];

		temp[8] = data[8] * other.data[0] + data[9] * other.data[4] + data[10] * other.data[8] +  data[11] * other.data[12];
		temp[9] = data[8] * other.data[1] + data[9] * other.data[5] + data[10] * other.data[9] +  data[11] * other.data[13];
		temp[10] = data[8] * other.data[2] + data[9] * other.data[6] + data[10] * other.data[10] + data[11] * other.data[14];
		temp[11] = data[8] * other.data[3] + data[9] * other.data[7] + data[10] * other.data[11] + data[11] * other.data[15];

		temp[12] = data[12] * other.data[0] + data[13] * other.data[4] + data[14] * other.data[8] +  data[15] * other.data[12];
		temp[13] = data[12] * other.data[1] + data[13] * other.data[5] + data[14] * other.data[9] +  data[15] * other.data[13];
		temp[14] = data[12] * other.data[2] + data[13] * other.data[6] + data[14] * other.data[10] + data[15] * other.data[14];
		temp[15] = data[12] * other.data[3] + data[13] * other.data[7] + data[14] * other.data[11] + data[15] * other.data[15];
	
		memcpy(data,temp, sizeof(float) * 16);

		return *this;
	}
	mat4 operator*  (const mat4& other) {
		
		mat4 newMatrix = *this;
		newMatrix *= other;
		return newMatrix;
	}
};

