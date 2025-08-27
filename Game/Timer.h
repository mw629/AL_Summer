#pragma once
#include <Engine.h>

class Timer
{
private:

	std::unique_ptr<Texture> texture;

	Sprite* hundredsPlace;
	Sprite* tensPlace;
	Sprite* onesPlace;

	Vector2 farstPos = { 1088,0 };
	float timeSize = 64.0f;

	int num[10];


	float timer = 0;
	int time = 0;

public:

	void Initialize();

	void Update();

	void Draw();


};

