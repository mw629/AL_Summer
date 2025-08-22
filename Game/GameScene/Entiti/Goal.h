#pragma once
#include <Engine.h>

class Goal
{
private:

	Model* goalModel;
	Transform transform = { {1.0f, 1.0f, 1.0f}, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,0.0f } };

public:

	void Initialize(Vector3 pos);

	void Update(Matrix4x4 viewMatrix);

	void Draw();

};

