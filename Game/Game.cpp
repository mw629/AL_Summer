#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
	delete gameScene;
}

void Game::Initialize() {
	gameScene = new GameScene();
	gameScene->Initialize();
}

void Game::Update() {
	gameScene->Update();
}

void Game::Draw() {
	gameScene->Draw();
}