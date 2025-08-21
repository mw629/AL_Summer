#pragma once
#include <Engine.h>

class MapChip
{
private:

	std::vector<std::vector<int>> map_;
	std::vector<std::vector<Model*>> models_;

	const int blockSize = 2.0f;

public:

	void Initialize();

	void Update(Matrix4x4 viewMatrix);

	void Draw();

	std::vector<std::vector<int>> LoadMapFromCSV(const std::string& filePath);

	Vector3 MapPostion(int x, int y);

	std::vector<std::vector<int>> GetMapData() { return map_; }
};

