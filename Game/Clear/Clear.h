#pragma once
#include <Engine.h>
#include "../Fede.h"
#include "../SkyDome.h"

class Clear
{
private:

	Fede* fede_;
	SkyDome* skyDome_;

	Sprite* backScreen;
	Transform uvTransform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	Model* text;
	Transform transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	Transform camera;

	bool isFinish;

public:

	void Initialize();

	void Update();

	void Draw();


	bool IsFinished() { return isFinish; }

};

