#pragma once
#include "GameScene/GameScene.h"
#include "Title/TitleScene.h"

class Game
{
private:

    TitleScene* titleScene;
	GameScene* gameScene;

public:

    Game();
    ~Game();

    void Initialize();
    void Update();
    void Draw();

};

