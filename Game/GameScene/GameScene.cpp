#include "GameScene.h"
#include <Engine.h>
#include <imgui.h>

GameScene::GameScene()
{
	Initialize();
}

GameScene::~GameScene()
{
	delete map;
	delete skyDome;
	delete player;
	delete camera;
}

void GameScene::ImGui()
{
	camera->ImGui();
}

void GameScene::Initialize() {
	

	map = new MapChip();
	map->Initialize();
	skyDome = new SkyDome();
	skyDome->Initialize();

	player = new Player;
	Vector3 playerPos = map->MapPostion(3, 5);
	player->Initialize(playerPos,map->GetMapData());

	camera = new Camera();
	camera->Initialize();

}

void GameScene::Update() {
	
	ImGui();

	camera->Update(player);
	
	map->Update(camera->GetViewMatrix());
	skyDome->Update(camera->GetViewMatrix());

	player->Update(camera->GetViewMatrix());

}

void GameScene::Draw() {
	
	map->Draw();
	skyDome->Draw();

	player->Draw();


}

