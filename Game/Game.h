#pragma once
#include "GameScene/GameScene.h"

class Game
{
private:

	GameScene* gameScene;

public:

    Game();
    ~Game();

    void Initialize();
    void Update();
    void Draw();

};

