#pragma once
#include <Engine.h>

class Enemy;
class Goal;


class Player
{
private:


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


	bool IsHitBlock(Vector3 pos, const std::vector<std::vector<int>>& map);
	void OnCollision(const Enemy* enemy);


	void Draw();

	AABB GetAABB();

	Vector3 GetPos() { return transform.translate; }
};
