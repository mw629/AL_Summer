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
			gameScene = new GameScene();
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		// シーンの更新
		if (gameScene->IsClear()) {
			scene = Scene::kClear;
			delete gameScene;
			clearScene = new Clear();
			clearScene->Initialize();
		}
		else if(gameScene->IsDeaded()) {
			scene = Scene::kGameOver;
			delete gameScene;
			gameOver = new GameOver();
			gameOver->Initialize();
		}
		break;
	case Scene::kClear:
		// シーンの更新
		if (clearScene->IsFinished()) {
			scene = Scene::kTitle;
			delete clearScene;
			titleScene = new TitleScene();
			titleScene->Initialize();
		}
		break;
	case Scene::kGameOver:
		if (gameOver->IsFinished()) {
			scene = Scene::kTitle;
			delete gameOver;
			titleScene = new TitleScene();
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
	case Scene::kClear:
		clearScene->Update();
		break;
	case Scene::kGameOver:
		gameOver->Update();
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
	case Scene::kGameOver:
		gameOver->Draw();
		break;
	default:
		break;
	}
}