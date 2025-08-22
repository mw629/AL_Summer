#include "Goal.h"


void Goal::Initialize(Vector3 pos) {
	ModelData modelData = LoadObjFile("resources/Player", "Player.obj");
	Texture* texture = new Texture();
	int index = texture->CreateTexture(modelData.material.textureDilePath);
	goalModel = new Model();
	goalModel->Initialize(modelData, texture->TextureData(index));
	goalModel->CreateModel();
	transform.translate = pos;
}

void Goal::Update(Matrix4x4 viewMatrix) {
	goalModel->SetTransform(transform);
	goalModel->SettingWvp(viewMatrix);
}

void Goal::Draw() {}