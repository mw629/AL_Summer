#pragma once
#include <Engine.h>

class Player
{
private:

	Input input;

	std::vector<std::vector<int>> mapData_;
	float blockSize = 2.0f;

	Model* playerModel;
	Transform transform = { {1.0f, 1.0f, 1.0f}, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,0.0f } };
	Vector3 velocity = { 0.0f,0.0f,0.0f };
	float playerSize = 2.0f;

	bool isOnGround=false;


public:
	~Player();

	void Initialize(Vector3 pos, std::vector<std::vector<int>> mapData);

	void Update(Matrix4x4 viewMatrix);

	void Move();

	void CheckCollision();
	void CheckCollisionUp();
	void CheckCollisionDown();
	void CheckCollisionLeft();
	void CheckCollisionRight();

	bool IsHitBlock(Vector3 pos, const std::vector<std::vector<int>>& map);


	void Draw();

	Vector3 GetPos() { return transform.translate; }
};
