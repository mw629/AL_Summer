#include "Timer.h"
#include <Engine.h>

void Timer::Initialize() {

	texture = std::make_unique<Texture>();

	num[0] = texture.get()->CreateTexture("resources/Num/0.png");
	num[1] = texture.get()->CreateTexture("resources/Num/1.png");
	num[2] = texture.get()->CreateTexture("resources/Num/2.png");
	num[3] = texture.get()->CreateTexture("resources/Num/3.png");
	num[4] = texture.get()->CreateTexture("resources/Num/4.png");
	num[5] = texture.get()->CreateTexture("resources/Num/5.png");
	num[6] = texture.get()->CreateTexture("resources/Num/6.png");
	num[7] = texture.get()->CreateTexture("resources/Num/7.png");
	num[8] = texture.get()->CreateTexture("resources/Num/8.png");
	num[9] = texture.get()->CreateTexture("resources/Num/9.png");

	hundredsPlace = new Sprite();
	hundredsPlace->Initialize(texture->TextureData(num[0]));
	hundredsPlace->CreateSprite();
	hundredsPlace->SetSize({ 0.0f + farstPos.x,0.0f + farstPos.y }, { timeSize + farstPos.x,timeSize + farstPos.y });
	hundredsPlace->SettingWvp();

	tensPlace = new Sprite();
	tensPlace->Initialize(texture->TextureData(num[0]));
	tensPlace->CreateSprite();
	tensPlace->SetSize({ timeSize + farstPos.x,0.0f + farstPos.y }, { timeSize * 2 + farstPos.x,timeSize + farstPos.y });
	tensPlace->SettingWvp();

	onesPlace = new Sprite();
	onesPlace->Initialize(texture->TextureData(num[0]));
	onesPlace->CreateSprite();
	onesPlace->SetSize({ timeSize * 2 + farstPos.x,0.0f + farstPos.y }, { timeSize * 3 + farstPos.x,timeSize + farstPos.y });
	onesPlace->SettingWvp();

}

void Timer::Update() {

	timer++;
	time = (timer / 60);

	hundredsPlace->SetTexture(texture->TextureData(num[(time / 100)]));
	tensPlace->SetTexture(texture->TextureData(num[(time / 10)]));
	onesPlace->SetTexture(texture->TextureData(num[(time % 10)]));

}

void Timer::Draw() {
	Draw::DrawSprite(hundredsPlace);
	Draw::DrawSprite(tensPlace);
	Draw::DrawSprite(onesPlace);
}

