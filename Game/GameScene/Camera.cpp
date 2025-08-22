#include "Camera.h"
#include <imgui.h>
#include "Entiti/Player.h"


void Camera::ImGui()
{
	ImGui::Checkbox("DebugCamera", &debugcameraFrag);
	ImGui::DragFloat3("camraTranslate", &cameraTransform.translate.x, 0.1f);
	ImGui::DragFloat3("camraRotate", &cameraTransform.rotate.x, 0.1f);
	ImGui::DragFloat3("camraScale", &cameraTransform.scale.x, 0.1f);
}

void Camera::Initialize() {
	cameraTransform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-50.0f} };
	debugcameraTransform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-50.0f} };
}

void Camera::Update(Player *player)
{
	if (!debugcameraFrag) {
		cameraTransform.translate.x = player->GetPos().x;
		cameraTransform.translate.y = player->GetPos().y;
		cameraMatrix = MakeAffineMatrix(cameraTransform.translate, cameraTransform.scale, cameraTransform.rotate);;
		viewMatrix = Inverse(cameraMatrix);
	}
	else {
		
		if (input.PressKey(DIK_LEFT)) {
			debugcameraTransform.translate.x -= 0.5f;
		}
		if (input.PressKey(DIK_RIGHT)) {
			debugcameraTransform.translate.x += 0.5f;
		}
		if (input.PressKey(DIK_UP)) {
			debugcameraTransform.translate.y += 0.5f;
		}
		if (input.PressKey(DIK_DOWN)) {
			debugcameraTransform.translate.y -= 0.5f;
		}
		if (input.PressKey(DIK_R)) {
			 debugcameraTransform = cameraTransform;
		}
		
		cameraMatrix = MakeAffineMatrix(debugcameraTransform.translate, debugcameraTransform.scale, debugcameraTransform.rotate);;
		viewMatrix = Inverse(cameraMatrix);
	}
}
