#include "TitleScene.h"
#include <imgui.h>

void TitleScene::ImGui() {
#ifdef _DEBUG
	ImGui::DragFloat3("camraTranslate", &camera.translate.x, 0.1f);
	ImGui::DragFloat3("camraRotate", &camera.rotate.x, 0.1f);
	ImGui::DragFloat3("camraScale", &camera.scale.x, 0.1f);
	ImGui::DragFloat3("Translate", &transform.translate.x, 0.1f);
	ImGui::DragFloat3("Rotate", &transform.rotate.x, 0.1f);
	ImGui::DragFloat3("Scale", &transform.scale.x, 0.1f);
#endif 
}

void TitleScene::Initialize() {

	fede_ = new Fede();
	fede_->Initalize();
	fede_->fedestate = Fede::FedeOut;

	std::unique_ptr<Texture> texture = std::make_unique<Texture>();

	ModelData modelData = LoadObjFile("resources/Title/TitleText", "TitleText.obj");
	int index = texture->CreateTexture(modelData.material.textureDilePath);
	text = new Model();
	text->Initialize(modelData, texture->TextureData(index));
	text->CreateModel();
	transform.rotate.y = 3.2;
	transform.translate.z = 0.1f;
	camera.translate.z = -6.3f;
}

void TitleScene::Update() {

	ImGui();

	fede_->Update();

	Matrix4x4 viewMatrix = Inverse(MakeAffineMatrix(camera));


	text->SetTransform(transform);
	text->SettingWvp(viewMatrix);

	if (Input::PushKey(DIK_SPACE)) {
		fede_->fedestate = Fede::FedeIn;
	}
	if (fede_->IsFinished()) {
		isFinish = true;
	}

}

void TitleScene::Draw() {
	Draw::DrawObj(text);

	fede_->Draw();
}