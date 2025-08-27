#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
	delete titleScene;
	delete gameScene;
	delete clearScene;
}

void Game::Initialize() {
	titleScene = new TitleScene();
	titleScene->Initialize();
	gameScene = new GameScene();
	gameScene->Initialize();
	clearScene = new Clear();
	clearScene->Initialize();
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
			/*delete titleScene;
			titleScene = nullptr;
			gameScene = new GameScene;
			gameScene->Initialize();*/
		}
		break;
	case Scene::kGame:
		// シーンの更新
		if (gameScene->IsClear()) {
			scene = Scene::kClear;
			/*delete gameScene;
			gameScene = nullptr;
			clearScene = new Clear;
			clearScene->Initialize();*/
		}
		break;
	case Scene::kClear:
		// シーンの更新
		if (clearScene->IsFinished()) {
			scene = Scene::kTitle;
			/*delete clearScene;
			clearScene = nullptr;
			titleScene = new TitleScene;
			titleScene->Initialize();*/
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
	case Scene::kClear:
		clearScene->Update();
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
	case Scene::kClear:
		clearScene->Draw();
		break;
	default:
		break;
	}
}