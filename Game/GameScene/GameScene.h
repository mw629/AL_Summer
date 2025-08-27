#pragma once  
#include "MapData/SkyDome.h"

#include "Entiti/Player.h"
#include "MapData/MapChip.h"
#include "Camera.h"
#include "Entiti/Goal.h"
#include "../Fede.h"
#include "../Timer.h"



class GameScene {
private:

    
    Fede* fede_;
    Timer* timer_;

    Camera* camera_;

    SkyDome* skyDome_;
    MapChip* map_;

    Player* player_;

    Goal* goal_;

    bool isClear_ =false;
    bool isFinish_ = false;

public:  
    GameScene();
    ~GameScene();  

    void ImGui();

    void Initialize();  
    void Update();  
    void Draw();  

    void CheckAllCollisions();



    bool IsFinished() { return isFinish_; }

    bool IsClear() { return isClear_; }

};
