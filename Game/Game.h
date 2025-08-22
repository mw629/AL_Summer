#pragma once
#include "GameScene/GameScene.h"
#include "Title/TitleScene.h"

class Game
{
private:

    enum Scene
    {
        kUnknown,
        kTitle,
        kGame,
    };
    Scene scene = Scene::kGame;


    TitleScene* titleScene;
	GameScene* gameScene;

public:

    Game();
    ~Game();

    void Initialize();
    void Update();
    void Draw();

    void ChangeScene();

    void UpdateScene();

    void DrawScene();


};

