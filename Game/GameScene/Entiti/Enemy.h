#pragma once
#include <Engine.h>

class Enemy
{
private:
	std::unique_ptr<Texture> texture;

	Model* enemy_;
	Transform transform = { {1.0f, 1.0f, 1.0f}, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,0.0f } };


public:
	
	void Initialize(Vector3 pos);

	void Update(Matrix4x4 viewMatrix);

	void Draw();

};

