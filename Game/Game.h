#pragma once
#include "GameScene/GameScene.h"
#include "Title/TitleScene.h"
#include "Clear/Clear.h"
#include "GameOver/GameOver.h"

class Game
{
private:

    std::unique_ptr<Audio> audio;
    int BGMHandle[4];

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
    GameOver* gameOver;

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

