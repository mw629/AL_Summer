#include "GameScene.h"
#include <Engine.h>
#include <imgui.h>

GameScene::GameScene()
{
	Initialize();
}

GameScene::~GameScene()
{
	delete map_;
	delete skyDome_;
	delete player_;
	delete camera_;
}

void GameScene::ImGui()
{
#ifdef _DEBUG
	camera_->ImGui();
#endif
}

void GameScene::Initialize() {
	
	fede_ = new Fede();
	fede_->Initalize();
	fede_->fedestate = Fede::FedeOut;

	timer_ = new Timer();
	timer_->Initialize();

	map_ = new MapChip();
	map_->Initialize();
	skyDome_ = new SkyDome();
	skyDome_->Initialize();

	player_ = new Player;
	Vector3 playerPos = map_->MapPostion(3, 1);
	player_->Initialize(playerPos,map_->GetMapData());

	EnemyList(map_->GetMapData());

	goal_ = new Goal;
	Vector3 goalPos= map_->MapPostion(29,15);
	goal_->Initialize(goalPos);

	camera_ = new Camera();
	camera_->Initialize();

}

void GameScene::Update() {
	
	ImGui();

	fede_->Update();
	timer_->Update();

	for (Enemy* enemy : enemies_) {
		if (enemy) {
			enemy->Update(camera_->GetViewMatrix());
		}
	}
	/*enemies_.remove_if([](Enemy* enemy) {
		if (enemy) {
			delete enemy;
			return true;
		}
		return false;
		});*/

	camera_->Update(player_);
	
	map_->Update(camera_->GetViewMatrix());
	skyDome_->Update(camera_->GetViewMatrix());
	goal_->Update(camera_->GetViewMatrix());
	player_->Update(camera_->GetViewMatrix());

	CheckAllCollisions();

	if (fede_->IsFinished()) {
		isClear_ = true;
	}

}

void GameScene::Draw() {

	map_->Draw();
	skyDome_->Draw();

	for (Enemy* enemy : enemies_) {
		if (enemy) {
			enemy->Draw();
		}
	}

	player_->Draw();
	goal_->Draw();

	timer_->Draw();

	fede_->Draw();

}

void GameScene::CheckAllCollisions() {
#pragma region 自キャラと敵キャラの当たる判定自キャラと敵キャラの当たり判定
	AABB aabb1, aabb2;

	// 自キャラの座標
	aabb1 = player_->GetAABB();

	/*for (Enemy* enemy : enemies_) {
		if (enemy->GetIsCollisionDisabled()) {
			continue;
		}

		aabb2 = enemy->GetAABB();
		if (IsCollision(aabb1, aabb2)) {
			player_->OnCollision(enemy);
			enemy->OnCollision(player_);
		}
	}*/
	aabb2 = goal_->GetAABB();
	if (IsCollision(aabb1, aabb2)) {
		fede_->fedestate = Fede::FedeIn;
	}

#pragma endregion
}

void GameScene::EnemyList(std::vector<std::vector<int>> mapData)
{
	for (int i = 0; i < mapData.size(); i++) {
		for (int j = 0; j < mapData[0].size(); j++) {
			if (mapData[i][j] == 2) {
				Enemy* newEnemy;
				newEnemy = new Enemy();
				Vector3 Pos = map_->MapPostion(j, i);
				newEnemy->Initialize(Pos);
				enemies_.push_back(newEnemy);
			}
		}
	}
	

}



