#include "Enemy.h"

#include "Player.h"

void Enemy::Initialize(Vector3 pos) {
	texture = std::make_unique<Texture>();

	ModelData modelData = LoadObjFile("resources/Enemy", "Enemy.obj");
	int index = texture->CreateTexture(modelData.material.textureDilePath);
	enemy_ = new Model();
	enemy_->Initialize(modelData, texture->TextureData(index));
	enemy_->CreateModel();
	transform.translate = pos;
}

void Enemy::Update(Matrix4x4 viewMatrix) {
	enemy_->SetTransform(transform);
	enemy_->SettingWvp(viewMatrix);
}

void Enemy::Draw() {
	Draw::DrawObj(enemy_);
}

AABB Enemy::GetAABB() {
	Vector3 worldPos = transform.translate;
	AABB aabb;
	aabb.min = { worldPos.x - size / 2.0f, worldPos.y - size / 2.0f, worldPos.z - size / 2.0f };
	aabb.max = { worldPos.x + size / 2.0f, worldPos.y + size / 2.0f, worldPos.z + size / 2.0f };

	return aabb;
}

void Enemy::OnCollision(Player* player)
{
	(void)player;
	if (player->IsAttack()) {
		isDead = true;
	}
}
