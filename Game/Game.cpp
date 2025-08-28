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
	audio = std::make_unique<Audio>();
	
	audio->Initialize();
	BGMHandle[0] = audio->Load("resources/Audio/BGM/sweet_pop.mp3");
	BGMHandle[1] = audio->Load("resources/Audio/BGM/pop.mp3");
	BGMHandle[2] = audio->Load("resources/Audio/BGM/Havefun.mp3");
	BGMHandle[3] = audio->Load("resources/Audio/BGM/gameover.mp3");
	audio->Play(BGMHandle[0], true, 1.0f);
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
			audio.get()->Stop(BGMHandle[0]);
			audio->Play(BGMHandle[1], true, 1.0f);
		}
		break;
	case Scene::kGame:
		// シーンの更新
		if (gameScene->IsClear()) {
			scene = Scene::kClear;
			delete gameScene;
			clearScene = new Clear();
			clearScene->Initialize();
			audio.get()->Stop(BGMHandle[1]);
			audio->Play(BGMHandle[2], true, 1.0f);
		}
		else if(gameScene->IsDeaded()) {
			scene = Scene::kGameOver;
			delete gameScene;
			gameOver = new GameOver();
			gameOver->Initialize();
			audio.get()->Stop(BGMHandle[1]);
			audio->Play(BGMHandle[3], true, 1.0f);
		}
		break;
	case Scene::kClear:
		// シーンの更新
		if (clearScene->IsFinished()) {
			scene = Scene::kTitle;
			delete clearScene;
			titleScene = new TitleScene();
			titleScene->Initialize();
			audio.get()->Stop(BGMHandle[2]);
			audio->Play(BGMHandle[0], true, 1.0f);
		}
		break;
	case Scene::kGameOver:
		if (gameOver->IsFinished()) {
			scene = Scene::kTitle;
			delete gameOver;
			titleScene = new TitleScene();
			titleScene->Initialize();
			audio.get()->Stop(BGMHandle[3]);
			audio->Play(BGMHandle[0], true, 1.0f);
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