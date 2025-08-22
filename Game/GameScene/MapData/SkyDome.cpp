#include "SkyDome.h"

SkyDome::~SkyDome()
{
	delete skydomeModel;
}

void SkyDome::Initialize() {
	ModelData modelData = LoadObjFile("resources/skydome", "skydome.obj");
	Texture* texture = new Texture();
	int index = texture->CreateTexture(modelData.material.textureDilePath);
	skydomeModel = new Model();
	skydomeModel->Initialize(modelData, texture->TextureData(index));
	skydomeModel->CreateModel();
}

void SkyDome::Update(Matrix4x4 viewMatrix){
	skydomeModel->SetTransform(objTransform);
	skydomeModel->SettingWvp(viewMatrix);
}

void SkyDome::Draw(){
	Draw::DrawObj(skydomeModel);
}