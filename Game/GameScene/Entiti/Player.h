#pragma once
#include <Engine.h>

class Enemy;
class Goal;


class Player
{
private:

	enum class LRDirection {
		kRight,
		kLeft,
	};
	LRDirection lrDirection_ = LRDirection::kRight;

	std::vector<std::vector<int>> mapData_;
	float blockSize = 2.0f;

	Model* playerModel;
	Transform transform = { {1.0f, 1.0f, 1.0f}, { 0.0f,0.0f,0.0f }, { 1.0f,1.0f,0.0f } };
	Vector3 velocity = { 0.0f,0.0f,0.0f };
	float playerSize = 2.0f;

	enum AttackPhase {
		Charge,     // 溜め
		Rush,       // 突進
		echoEffect, // 余韻
	};
	AttackPhase attackPhase;
	Vector3 attackVelocity = { 0.8f, 0.0f, 0.0f };
	bool attackFlag_;
	float attackCount_;
	float attackMaxFrame = 0.8f;
	float chargeTime = 0.05f;
	float rushTime = 0.1f;
	float echoEffectTime = 0.05f;


	bool isOnGround=false;
	bool isAttack = false;

public:
	~Player();

	void Initialize(Vector3 pos, std::vector<std::vector<int>> mapData);

	void Update(Matrix4x4 viewMatrix);

	void Move();

	void Attack();

	void Turning();

	bool IsHitBlock(Vector3 pos, const std::vector<std::vector<int>>& map);
	void OnCollision(const Enemy* enemy);


	void Draw();

	AABB GetAABB();

	Vector3 GetPos() { return transform.translate; }
};
