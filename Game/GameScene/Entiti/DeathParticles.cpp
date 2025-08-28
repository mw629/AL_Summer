#include "DeathParticles.h"

#include "Player.h"

void DeathParticles::Initialize() {
	texture = std::make_unique<Texture>();
	for (int i = 0; i < 10; i++) {
		ModelData modelData = LoadObjFile("resources/Player", "Player.obj");
		int index = texture->CreateTexture(modelData.material.textureDilePath);
		deathParticlesModel[i] = new Model();
		deathParticlesModel[i]->Initialize(modelData, texture->TextureData(index));
		deathParticlesModel[i]->CreateModel();
	}
	color = { 1.0f,1.0f,1.0f,1.0f };
}

void DeathParticles::Update(Player* player, Matrix4x4 viewMatrix) {
	if (player->IsDeaded() && !isStart) {
		isStart = true;
		for (int i = 0; i < 10; i++) {
			transform[i].translate = player->GetPos();
		}
	}
	if (isStart) {
		for (int i = 0; i < 10; i++) {
			Vector3 velocity = { kSpeed, 0, 0 };
			float angle = kAngleUnit * i;
			Matrix4x4 matrixRotation = RotationZ(angle);
			velocity = TransformMatrix(velocity, matrixRotation);
			transform[i].translate += velocity;
		}
		color.w -= 1.0f / (60.0f * 0.5f);
	}
	if (color.w <= 0) {
		color.w = 0;
		isFinish = true;
		isStart = false;
	}

	for (int i = 0; i < 10; i++) {
		deathParticlesModel[i]->SetColor(color);
		deathParticlesModel[i]->SetTransform(transform[i]);
		deathParticlesModel[i]->SettingWvp(viewMatrix);
	}
}

void DeathParticles::Draw() {
	if (isStart) {
		for (int i = 0; i < 10; i++) {
			Draw::DrawObj(deathParticlesModel[i]);
		}
	}
}