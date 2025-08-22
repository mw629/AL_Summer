#pragma once
#include <Engine.h>

class TitleScene
{
private:
	Sprite* backScreen;
	Transform uvTransform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	Input input;

	bool isFinish ;

public:

	void Initialize();

	void Update();

	void Draw();


	bool IsFinished() { return isFinish; }

};

