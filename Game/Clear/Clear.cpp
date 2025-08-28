#include "Clear.h"


void Clear::Initialize() {

	fede_ = new Fede();
	fede_->Initalize();
	fede_->fedestate = Fede::FedeOut;

	skyDome_ = new SkyDome();
	skyDome_->Initialize();
	skyDome_->SetColor({ 0.3f,0.9f,0.9f,1.0f });

	backScreen = new Sprite();
	Texture* texture = new Texture();
	int backImage = texture->CreateTexture("resources/Clear/BackScreen.png");
	backScreen->Initialize(texture->TextureData(backImage));
	backScreen->CreateSprite();
	Vector2 spritePos[2] = { {0.0f,0.0f}, {1280.0f,720.0f} };
	backScreen->SetSize(spritePos[0], spritePos[1]);
	backScreen->SettingWvp();

	ModelData modelData = LoadObjFile("resources/Clear/ClearText","ClearText.obj");

	int index = texture->CreateTexture(modelData.material.textureDilePath);
	text = new Model();
	text->Initialize(modelData, texture->TextureData(index));
	text->CreateModel();
	transform.rotate.y = 3.2;
	camera.translate.z = -6.3f;
}

void Clear::Update() {

	fede_->Update();

	uvTransform.translate.x += 1.0f / (60.0f * 3.0f);
	backScreen->SetUVTransfotm(uvTransform);

	Matrix4x4 viewMatrix = Inverse(MakeAffineMatrix(camera));

	skyDome_->Update(viewMatrix);

	backScreen->SettingWvp();

	text->SetTransform(transform);
	text->SettingWvp(viewMatrix);

	if (Input::PushKey(DIK_SPACE)) {
		isFinish = true;
	}

}

void Clear::Draw() {
	Draw::DrawObj(text);
	skyDome_->Draw();
	fede_->Draw();
}