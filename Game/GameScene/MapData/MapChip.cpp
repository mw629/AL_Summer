#include "MapChip.h"



MapChip::~MapChip()
{
	for (const auto& row : models_) {
		for (const auto& model : row) {
			if (model) {
				delete model;
			}
		}
	}
}

void MapChip::Initialize() {

	std::unique_ptr<Texture> texture = std::make_unique<Texture>();

	map_ = LoadMapFromCSV("resources/MapData.csv");
	ModelData blockModel = LoadObjFile("resources/block", "block.obj");
	int blockTexture = texture->CreateTexture(blockModel.material.textureDilePath);

	for (int i = 0; i < map_.size(); i++) {
		std::vector<Model*> modelRow;
		for (int j = 0; j < map_[0].size(); j++) {
			Transform transform = {
				{1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{1.0f + blockSize * j,1.0f + blockSize * i,0.0f } };
			//transform.translate={ -1.0f + blockSize * j,-1.0f + blockSize * i,0.0f };
			if (map_[i][j] == 1) {
				Model* model = new Model();
				model->Initialize(blockModel, texture->TextureData(blockTexture));
				model->CreateModel();
				model->SetTransform(transform);
				modelRow.push_back(model);
			}
		}
		models_.push_back(modelRow);
	}
}

void MapChip::Update(Matrix4x4 viewMatrix) {
	for (const auto& row : models_) {
		for (const auto& model : row) {
			if (model) {
				model->SettingWvp(viewMatrix);
			}
		}
	}
}


void MapChip::Draw() {
	for (const auto& row : models_) {
		for (const auto& model : row) {
			if (model) {
				Draw::DrawObj(model);
			}
		}
	}
}

std::vector<std::vector<int>> MapChip::LoadMapFromCSV(const std::string& filePath)
{
	std::vector<std::vector<int>> mapData;
	std::ifstream file(filePath);

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open CSV file: " + filePath);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> row;
		std::stringstream ss(line);
		std::string cell;

		while (std::getline(ss, cell, ',')) {
			try {
				row.push_back(std::stoi(cell));
			}
			catch (...) {
				row.push_back(0); // 数字変換できなかったら0にする
			}
		}
		if (!row.empty()) {
			mapData.push_back(row);
		}
	}

	std::reverse(mapData.begin(), mapData.end());
	return mapData;
}

Vector3 MapChip::MapPostion(int x, int y)
{
	Vector3 transform =
	{ -1.0f + blockSize * x,-1.0f + blockSize * y,0.0f };
	return transform;
}






