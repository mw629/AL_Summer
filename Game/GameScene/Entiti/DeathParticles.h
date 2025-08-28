#pragma once
#include <Engine.h>

class Player;

class DeathParticles
{
private:
	std::unique_ptr<Texture> texture;

	Model* deathParticlesModel[10];
	Transform transform[10];
	Vector4 color;

	bool isStart = false;
	bool isFinish = false;

		// 移動の速さ
	static inline const float kSpeed = 0.3f;
	// 分裂した一個の角度
	static inline const float kAngleUnit = 2.0f * 3.14f / 10;

public:

	void Initialize();

	void Update(Player* player,Matrix4x4 viewMatrix);

	void Draw();
	
	bool IsFinished() { return isFinish; }
};

