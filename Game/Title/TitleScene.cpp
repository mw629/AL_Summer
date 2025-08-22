#include "TitleScene.h"

void TitleScene::Initialize(){
	backScreen = new Sprite();
	Texture* texture = new Texture();
	int backImage = texture->CreateTexture("resources/BackScreen.png");
	backScreen->Initialize(texture->TextureData(backImage));
	backScreen->CreateSprite();
	Vector2 spritePos[2] = { {0.0f,0.0f}, {1280.0f,720.0f} };
	backScreen->SetSize(spritePos[0], spritePos[1]);
	backScreen->SettingWvp();
}

void TitleScene::Update(){
	uvTransform.translate.x += 1.0f/(60.0f*3.0f);
	backScreen->SetUVTransfotm(uvTransform);
}

void TitleScene::Draw(){
	Draw::DrawSprite(backScreen);
}