#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Initialize() {
	titleScene = new TitleScene();
	titleScene->Initialize();
	gameScene = new GameScene();
	gameScene->Initialize();
}

void Game::Update() {
	ChangeScene();
	UpdateScene();
}

void Game::Draw() {
	DrawScene();
}

void Game::ChangeScene() {
	switch (scene) {
	case Scene::kTitle:
		// シーンの更新
		if (titleScene->IsFinished()) {
			scene = Scene::kGame;
			delete titleScene;
			titleScene = nullptr;
			gameScene = new GameScene;
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		// シーンの更新
		if (gameScene->IsFinished()) {
			scene = Scene::kTitle;
			delete gameScene;
			gameScene = nullptr;
			titleScene = new TitleScene;
			titleScene->Initialize();
		}
		break;
	default:
		break;
	}
}

void Game::UpdateScene() {
	switch (scene) {
	case Scene::kTitle:
		titleScene->Update();

		break;
	case Scene::kGame:

		gameScene->Update();
		break;
	default:
		break;
	}
}

void Game::DrawScene() {
	switch (scene) {
	case Scene::kUnknown:
		break;
	case Scene::kTitle:
		titleScene->Draw();
		break;
	case Scene::kGame:
		gameScene->Draw();
		break;
	default:
		break;
	}
}