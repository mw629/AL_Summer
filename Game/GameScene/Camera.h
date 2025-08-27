#pragma once
#include <Engine.h>

class Player;

class Camera
{
private:

    bool debugcameraFrag;
    Transform debugcameraTransform;
    
    Transform cameraTransform;
    Matrix4x4 cameraMatrix;
    Matrix4x4 viewMatrix;



public:

    void ImGui();

    void Initialize();

    void Update(Player* player);


    Matrix4x4 GetViewMatrix() { return viewMatrix; }

};

