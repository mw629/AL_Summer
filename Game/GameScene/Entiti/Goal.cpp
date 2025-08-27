#include "Goal.h"


void Goal::Initialize(Vector3 pos) {
	std::unique_ptr<Texture> texture = std::make_unique<Texture>();

	ModelData modelData = LoadObjFile("resources/Goal", "Goal.obj");
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

void Goal::Draw() {
	Draw::DrawObj(goalModel);
}

AABB Goal::GetAABB() {
	Vector3 worldPos = transform.translate;
	AABB aabb;
	aabb.min = { worldPos.x - size / 2.0f, worldPos.y - size / 2.0f, worldPos.z - size / 2.0f };
	aabb.max = { worldPos.x + size / 2.0f, worldPos.y + size / 2.0f, worldPos.z + size / 2.0f };

	return aabb;
}