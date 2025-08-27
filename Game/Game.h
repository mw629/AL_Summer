#pragma once
#include "GameScene/GameScene.h"
#include "Title/TitleScene.h"
#include "Clear/Clear.h"

class Game
{
private:

    enum Scene
    {
        kUnknown,
        kTitle,
        kGame,
        kClear,
        kGameOver,
    };
    Scene scene = Scene::kTitle;


    TitleScene* titleScene;
	GameScene* gameScene;
    Clear* clearScene;

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

