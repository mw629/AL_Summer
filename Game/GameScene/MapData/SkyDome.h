#pragma once
#include <Engine.h>

class SkyDome
{
private:

	Model* skydomeModel;
	Transform objTransform = { {1.0f, 1.0f, 1.0f}, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f } };


public:

	void Initialize();

	void Update(Matrix4x4 viewMatrix);

	void Draw();


};

