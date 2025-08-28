#include "Player.h"

Player::~Player()
{
	delete playerModel;
}

void Player::Initialize(Vector3 pos, std::vector<std::vector<int>> mapData) {
	texture = std::make_unique<Texture>();

	mapData_ = mapData;
	ModelData modelData = LoadObjFile("resources/Player", "Player.obj");
	int index = texture->CreateTexture(modelData.material.textureDilePath);
	playerModel = new Model();
	playerModel->Initialize(modelData, texture->TextureData(index));
	playerModel->CreateModel();
	transform.translate = pos;


	attackLimitImage[0] = texture->CreateTexture("resources/Gauge/0Gauge.png");
	attackLimitImage[1] = texture->CreateTexture("resources/Gauge/1Gauge.png");
	attackLimitImage[2] = texture->CreateTexture("resources/Gauge/2Gauge.png");
	attackLimitImage[3] = texture->CreateTexture("resources/Gauge/3Gauge.png");

	attackLimitSprite = new Sprite();
	attackLimitSprite->Initialize(texture->TextureData(attackLimitImage[3]));
	attackLimitSprite->CreateSprite();
	attackLimitSprite->SetSize({ 1000.0f,480.0f }, { 1280.0f,720.0f });
	attackLimitSprite->SettingWvp();

}

void Player::Update(Matrix4x4 viewMatrix) {

	if (isAttack) {
		Attack();
	}
	else {
		Move();
	}
	// 重力
	velocity.y -= 0.02f;
	velocity.x *= 0.95f;

	Turning();

	// トンネリング対策のため細かく分割移動
	int steps = 10;
	Vector3 move = velocity;

	for (int i = 0; i < steps; ++i) {
		Vector3 stepMove = {
			move.x / steps,
			move.y / steps,
			0.0f
		};

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

		// X方向（左右判定）
		transform.translate.x += stepMove.x;
		if (stepMove.x > 0) {
			if (IsHitBlock({ transform.translate.x + playerSize / 2.0f, transform.translate.y }, mapData_)) {
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

	}
	attackLimitSprite->SetTexture(texture->TextureData(attackLimitImage[attackLimit]));
	playerModel->SetTransform(transform);
	playerModel->SettingWvp(viewMatrix);
}

void Player::Move()
{
	// 入力処理
	if (Input::PressKey(DIK_A)) {
		velocity.x -= 1.0f / 60.0f;
	}
	if (Input::PressKey(DIK_D)) {
		velocity.x += 1.0f / 60.0f;
	}
	if (Input::PushKey(DIK_W) && isOnGround) {
		velocity.y = 0.5f;
		isOnGround = false;
	}
	if (Input::PressKey(DIK_SPACE) && !isAttack && attackLimit != 0) {
		isAttack = true;
		attackLimit--;
	}

}

void Player::Attack()
{
	// 予備動作
	attackCount_ += 1.0f / 60.0f;

	switch (attackPhase) {
	case Player::Charge: {
		isAttack = true;
		float t = static_cast<float>(attackCount_) / chargeTime;
		transform.scale.z = EaseOut(1.0f, 0.3f, t);
		transform.scale.y = EaseOut(1.0f, 1.6f, t);
		if (attackCount_ >= chargeTime) {
			attackPhase = AttackPhase::Rush;
			attackCount_ = 0;
		}
	} break;
	case Player::Rush: {
		float t = static_cast<float>(attackCount_) / rushTime;
		transform.scale.z = EaseOut(0.3f, 1.3f, t);
		transform.scale.y = EaseIn(1.6f, 0.7f, t);

		if (attackCount_ >= rushTime) {
			attackPhase = AttackPhase::echoEffect;
			attackCount_ = 0;
		}

		if (lrDirection_ == LRDirection::kLeft) {
			velocity = attackVelocity;
			velocity.x *= -1.0f;
		}
		else {
			velocity = attackVelocity;
		}

	} break;
	case Player::echoEffect: {
		float t = static_cast<float>(attackCount_) / echoEffectTime;
		transform.scale.z = EaseOut(1.3f, 1.0f, t);
		transform.scale.y = EaseOut(0.7f, 1.0f, t);

		if (attackCount_ >= echoEffectTime) {
			isAttack = false;
			velocity = { 0.0f,0.0f,0.0f };
			attackCount_ = 0;
			attackPhase = Player::Charge;
		}
	}
	   break;
	}
}

void Player::Turning()
{
	// 移動方向に応じて向きを変える
	float targetRotationY = transform.rotate.y;
	if (velocity.x > 0.01f) {
		targetRotationY = 0.0f; // 右向き
		lrDirection_ = LRDirection::kRight;
	}
	else if (velocity.x < -0.01f) {
		targetRotationY = 3.14159f; // 左向き（πラジアン）
		lrDirection_ = LRDirection::kLeft;
	}

	// 線形補間（Lerp）で回転
	float rotationSpeed = 0.1f; // 調整可能
	transform.rotate.y = transform.rotate.y + (targetRotationY - transform.rotate.y) * rotationSpeed;

}


bool Player::IsHitBlock(Vector3 pos, const std::vector<std::vector<int>>& map) {
	int mapX = static_cast<int>((pos.x) / 2.0f);
	int mapY = static_cast<int>((pos.y) / 2.0f);

	if (mapY < 0 || mapY >= map.size() || mapX < 0 || mapX >= map[0].size()) {
		return false;
	}
	return (map[mapY][mapX] == 1);// true = ブロックあり
}

void Player::OnCollision(const Enemy* enemy) {
	(void)enemy;
	// velocity_ =Add(velocity_,knockback);
	if (!isAttack) {
		isDead_ = true;
	}
}




void Player::Draw() {
	Draw::DrawObj(playerModel);
	Draw::DrawSprite(attackLimitSprite);
}

AABB Player::GetAABB() {
	Vector3 worldPos = transform.translate;
	AABB aabb;
	aabb.min = { worldPos.x - playerSize / 2.0f, worldPos.y - playerSize / 2.0f, worldPos.z - playerSize / 2.0f };
	aabb.max = { worldPos.x + playerSize / 2.0f, worldPos.y + playerSize / 2.0f, worldPos.z + playerSize / 2.0f };

	return aabb;
}