#pragma once
#include <Engine.h>
#include "../Fede.h"

class GameOver
{
private:

	Fede* fede_;

	Model* text;
	Transform transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };

	Transform camera;
	bool isFinish;

public:
	void ImGui();

	void Initialize();

	void Update();

	void Draw();


	bool IsFinished() { return isFinish; }

};
