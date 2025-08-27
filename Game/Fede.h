#pragma once
#include <Engine.h>



class Fede
{
private:

	Sprite* sprite_;
	Vector4 color_;

	int fedeTime = 1.0f;
	bool isFinish;

public:

	enum FedeState
	{
		FedeIn,
		None,
		FedeOut,
	};
	FedeState fedestate;

	void Initalize();

	void Update();

	void Draw();

	bool IsFinished() { return isFinish; }
};

