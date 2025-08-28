#pragma once
#include <Engine.h>

class Player;

class Enemy
{
private:
	std::unique_ptr<Texture> texture;

	Model* enemy_;
	Transform transform = { {1.0f, 1.0f, 1.0f}, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,0.0f } };
	float size = 2.0f;

	bool isDead;

public:
	
	void Initialize(Vector3 pos);

	void Update(Matrix4x4 viewMatrix);

	void Draw();

	bool IsDeaded() { return isDead; }

	void OnCollision(Player* player);
	AABB GetAABB();
};

