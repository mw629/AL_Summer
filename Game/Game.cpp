#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
	//delete titleScene;
	delete gameScene;
}

void Game::Initialize() {
	//titleScene = new TitleScene();
	//titleScene->Initialize();
	gameScene = new GameScene();
	gameScene->Initialize();
}

void Game::Update() {
	//titleScene->Update();
	gameScene->Update();
}

void Game::Draw() {
	//titleScene->Draw();
	gameScene->Draw();
}