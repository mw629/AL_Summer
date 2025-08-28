#pragma once  
#include "Entiti/Player.h"
#include "Entiti/Enemy.h"
#include "MapData/MapChip.h"
#include "Camera.h"
#include "Entiti/Goal.h"
#include "../Fede.h"
#include "../Timer.h"
#include "Entiti/DeathParticles.h"
#include "../SkyDome.h"



class GameScene {
private:


   
    
    Fede* fede_;
    Timer* timer_;

    Camera* camera_;

    SkyDome* skyDome_;
    MapChip* map_;

    Player* player_;
    DeathParticles* dethPa;

    std::list<Enemy*> enemies_;

    Goal* goal_;
  
    bool isClear_ =false;
    bool isDead_ = false;
    bool isFinish_ = false;

public:  
    GameScene();
    ~GameScene();  

    void ImGui();

    void Initialize();  
    void Update();  
    void Draw();  

    void Reset();

    void CheckAllCollisions();

    void EnemyList(std::vector<std::vector<int>> mapData);

    bool IsFinished() { return isFinish_; }
    bool IsDeaded() { return isDead_; }
    bool IsClear() { return isClear_; }

};
