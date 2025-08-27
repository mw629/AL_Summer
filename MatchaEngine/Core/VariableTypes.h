#pragma once
#include <cstdint>
#include <vector>
#include <string>


//
// Vector structs
//

struct Vector2 {
	float x;
	float y;
};

struct Vector2i {
	int x;
	int y;
};

struct Vector3 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vector3 operator+(const Vector3& other) const { return { x + other.x, y + other.y, z + other.z }; }
	Vector3 operator-(const Vector3& other) const { return { x - other.x, y - other.y, z - other.z }; }
	Vector3 operator-() const { return { -x, -y, -z }; }
	Vector3 operator*(const Vector3& other) const { return { x * other.x, y * other.y, z * other.z }; }
	Vector3 operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar }; }
	Vector3 operator/(const Vector3& other) const { return { x / other.x, y / other.y, z / other.z }; }
	Vector3 operator/(float other) const { return { x / other, y / other, z / other }; }

	Vector3& operator=(const Vector3& other) { x = other.x; y = other.y; z = other.z; return *this; }
	Vector3& operator+=(const Vector3& other) { x += other.x; y += other.y; z += other.z; return *this; }
	Vector3& operator-=(const Vector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	Vector3& operator*=(const Vector3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
	Vector3& operator/=(const Vector3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
};

struct Vector4 {
	float x;
	float y;
	float z;
	float w;
};

//
// Matrix structs
//

struct Matrix4x4 {
	float m[4][4] = {
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
	};

	Matrix4x4 operator+(const Matrix4x4& other) const {
		Matrix4x4 result;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result.m[i][j] = m[i][j] + other.m[i][j];
		return result;
	}

	Matrix4x4 operator-(const Matrix4x4& other) const {
		Matrix4x4 result;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result.m[i][j] = m[i][j] - other.m[i][j];
		return result;
	}

	Matrix4x4 operator*(float scalar) const {
		Matrix4x4 result;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				result.m[i][j] = m[i][j] * scalar;
		return result;
	}

	Matrix4x4 operator*(const Matrix4x4& other) const {
		Matrix4x4 result = {};
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				for (int k = 0; k < 4; ++k)
					result.m[i][j] += m[i][k] * other.m[k][j];
		return result;
	}

	Matrix4x4& operator=(const Matrix4x4& other) {
		if (this != &other) {
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 4; ++j)
					m[i][j] = other.m[i][j];
		}
		return *this;
	}

	Matrix4x4& operator+=(const Matrix4x4& other) {
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] += other.m[i][j];
		return *this;
	}

	Matrix4x4& operator-=(const Matrix4x4& other) {
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] -= other.m[i][j];
		return *this;
	}

	Matrix4x4& operator*=(float scalar) {
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] *= scalar;
		return *this;
	}

	Matrix4x4& operator*=(const Matrix4x4& other) {
		*this = *this * other;
		return *this;
	}
};

//
// Object and Camera structs
//

struct Transform {
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 translate = { 0.0f,0.0f,0.0f };
};

struct sCamera {
	Vector3 pos;
	Vector3 scale;
	Vector3 rotate;
};

struct Object {
	Vector3 pos;
	Vector3 scale;
	Vector3 rotate;
};

//
// Shape and Geometry structs
//

struct sSphere {
	Vector3 center;
	float radius;
};

struct Plane {
	Vector3 normal;
	float distance;
};

struct sLine {
	Vector3 origin;
	Vector3 diff;
};

struct Ray {
	Vector3 origin;
	Vector3 diff;
};

struct Segment {
	Vector3 origin;
	Vector3 diff;
};

struct sTriangle {
	Vector3 vertices[3];
};

struct AABB {
	Vector3 min;
	Vector3 max;
};

struct BezierCurve {
	Vector3 start;
	Vector3 controlPoint;
	Vector3 end;
};

struct PolarCoordinates {
	Vector3 offset;
	float radius;
	float theta;
	float phi;
};

//
// Physics structs
//

struct Spring {
	Vector3 anchor;
	float naturalLength;
	float stiffness;
};

struct Ball {
	sSphere shape;
	Vector3 velosity;
	Vector3 acceleration;
	float mass;
	unsigned int color;
};

struct Pundulm {
	Vector3 anchor;
	float lengrh;
	float angle;
	float angularVelocity;
	float angularAcceleration;
};

struct ConicalPendulum {
	Vector3 anchor;
	float lengrh;
	float halfApexAngle;
	float angle;
	float angularVelocity;
};

//
// Rendering structs
//

struct TransformationMatrix {
	Matrix4x4 WVP;
	Matrix4x4 World;
};

struct LineTransformationMatrix {
	Matrix4x4 WVP;
};

struct VertexData {
	Vector4 position;
	Vector2 texcoord;
	Vector3 normal;
};

struct LineVertexData {
	Vector3 position;
	Vector4 color;
};

struct Material {
	Vector4 color;
	int32_t endbleLighting;
	float paddinmg[3];
	Matrix4x4 uvTransform;
};

struct DirectionalLight {
	Vector4 color;
	Vector3 direction;
	float intensity;
};

struct MaterialData {
	std::string textureDilePath;
};

struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
};