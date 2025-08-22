#pragma once  
#include "MapData/SkyDome.h"

#include "Entiti/Player.h"
#include "MapData/MapChip.h"
#include "Camera.h"

class GameScene {
private:
    Camera* camera;

    SkyDome* skyDome;
    MapChip* map;

    Player* player;

    bool isFinish = false;

public:  
    GameScene();
    ~GameScene();  

    void ImGui();

    void Initialize();  
    void Update();  
    void Draw();  

    bool IsFinished() { return isFinish; }
};
