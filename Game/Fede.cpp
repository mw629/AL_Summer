#include "Fede.h"

void Fede::Initalize()
{
	Texture* texture = new Texture();
	sprite_ = new Sprite();
	int image = texture->CreateTexture("resources/white64x64.png");
	sprite_->Initialize(texture->TextureData(image));
	sprite_->CreateSprite();
	Vector2 spritePos[2] = { {0.0f,0.0f}, {1280.0f,720.0f} };
	sprite_->SetSize(spritePos[0], spritePos[1]);
	sprite_->SettingWvp();
	color_ = Vector4{ 0.0f,0.0f,0.0f,1.0f };
	sprite_->SetColor(color_);
}

void Fede::Update() {

	switch (fedestate)
	{
	case FedeIn:
		color_.w += 1.0f / (fedeTime * 60.0f);
		if (color_.w > 1.0f) {
			color_.w = 1.0f;
			isFinish = true;
		}
		break;
	case None:

		break;
	case FedeOut:
		color_.w -= 1.0f / (fedeTime * 60.0f);
		if (color_.w < 0) {
			color_.w = 0.0f;
			fedestate = FedeState::None;
		}
		break;
	default:
		break;
	}

	sprite_->SetColor(color_);
	sprite_->SettingWvp();
}

void Fede::Draw() {
	Draw::DrawSprite(sprite_);
}