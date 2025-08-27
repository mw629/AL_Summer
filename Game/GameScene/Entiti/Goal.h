#pragma once
#include <Engine.h>

class Goal
{
private:

	Model* goalModel;
	Transform transform = { {1.0f, 1.0f, 0.8f}, { 0.0f,-0.5f*3.14f,0.0f }, { 1.0f,1.0f,0.0f } };

	float size = 2.0f;

public:

	void Initialize(Vector3 pos);

	void Update(Matrix4x4 viewMatrix);

	void Draw();

	AABB GetAABB();
};

