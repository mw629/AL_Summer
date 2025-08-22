#include "Player.h"

Player::~Player()
{
	delete playerModel;
}

void Player::Initialize(Vector3 pos, std::vector<std::vector<int>> mapData) {

	mapData_ = mapData;

	ModelData modelData = LoadObjFile("resources/Player", "Player.obj");
	Texture* texture = new Texture();
	int index = texture->CreateTexture(modelData.material.textureDilePath);
	playerModel = new Model();
	playerModel->Initialize(modelData, texture->TextureData(index));
	playerModel->CreateModel();
	transform.translate = pos;
}

void Player::Update(Matrix4x4 viewMatrix) {

	Move();
	
	// 重力
	velocity.y -= 0.02f;
	velocity.x *= 0.95f;
	// トンネリング対策のため細かく分割移動
	int steps = 10;
	Vector3 move = velocity;

	for (int i = 0; i < steps; ++i) {
		Vector3 stepMove = {
			move.x / steps,
			move.y / steps,
			0.0f
		};

		// X方向（左右判定）
		transform.translate.x += stepMove.x;
		if (stepMove.x > 0) {
			if (IsHitBlock({ transform.translate.x + playerSize/2.0f, transform.translate.y }, mapData_)) {
				transform.translate.x -= stepMove.x;
				velocity.x = 0;
			}
		}
		else if (stepMove.x < 0) {
			if (IsHitBlock({ transform.translate.x - playerSize / 2.0f, transform.translate.y }, mapData_)) {
				transform.translate.x -= stepMove.x;
				velocity.x = 0;
			}
		}

		// Y方向（上下判定＆着地時の位置補正）
		transform.translate.y += stepMove.y;

		// 足の位置
		float footY = transform.translate.y - playerSize / 2.0f;
		int mapY = static_cast<int>(footY / blockSize);
		int mapX = static_cast<int>(transform.translate.x / blockSize);

		// マップ範囲内チェック
		if (mapY >= 0 && mapY < (int)mapData_.size() &&
			mapX >= 0 && mapX < (int)mapData_[0].size())
		{
			if (mapData_[mapY][mapX] == 1 && velocity.y < 0.0f) {
				// プレイヤーをブロックの上にピタッと乗せる
				transform.translate.y = mapY * blockSize + blockSize + playerSize / 2.0f;

				// 微小な速度もリセット
				velocity.y = 0.0f;
				isOnGround = true;
			}
		}

		float headY = transform.translate.y + playerSize / 2.0f;
		mapY = static_cast<int>(headY / blockSize);
		mapX = static_cast<int>(transform.translate.x / blockSize);

		if (mapY >= 0 && mapY < (int)mapData_.size() &&
			mapX >= 0 && mapX < (int)mapData_[0].size())
		{
			if (mapData_[mapY][mapX] == 1 && velocity.y > 0.0f) {
				// 上に当たった（頭ぶつけ）
				transform.translate.y = mapY * blockSize - playerSize / 2.0f;
				velocity.y = 0.0f;
			}
		}
	}
	
	playerModel->SetTransform(transform);
	playerModel->SettingWvp(viewMatrix);
}

void Player::Move()
{
	// 入力処理
	if (input.PressKey(DIK_A)) {
		velocity.x -= 1.0f / 60.0f;
	}
	if (input.PressKey(DIK_D)) {
		velocity.x += 1.0f / 60.0f;
	}
	if (input.PushKey(DIK_SPACE) && isOnGround) {
		velocity.y = 0.5f;
		isOnGround = false;
	}

}


bool Player::IsHitBlock(Vector3 pos, const std::vector<std::vector<int>>& map) {
	int mapX = static_cast<int>((pos.x ) / 2.0f);
	int mapY = static_cast<int>((pos.y ) / 2.0f);

	if (mapY < 0 || mapY >= map.size() || mapX < 0 || mapX >= map[0].size()) {
		return false;
	}
	return map[mapY][mapX]; // true = ブロックあり
}



void Player::Draw() {
	Draw::DrawObj(playerModel);
}

