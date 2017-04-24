#pragma once

#include <string>

#include "PlayerChar.h"
#include "Box.h"
#include "Light.h"

#include <Engine/ResourceManager.h>
#include <fstream>

class LevelReaderWriter {
public:
	static bool saveAsText(const std::string& filePath, const PlayerChar& player, const std::vector<Box>& boxes, const std::vector<Light>& lights);
	static bool saveAsBinary(const std::string& filePath, const PlayerChar& player, const std::vector<Box>& boxes, const std::vector<Light>& lights);
	static bool loadAsText(const std::string& filePath, b2World* world, PlayerChar& player, std::vector<Box>& boxes, std::vector<Light>& lights);
	static bool loadAsBinary(const std::string& filePath, b2World* world, PlayerChar& player, std::vector<Box>& boxes, std::vector<Light>& lights);
private:
	static bool saveAsTextV0(const std::string& filePath, const PlayerChar& player, const std::vector<Box>& boxes, const std::vector<Light>& lights);
	static bool loadAsTextV0(std::ifstream& file, b2World* world, PlayerChar& player, std::vector<Box>& boxes, std::vector<Light>& lights);
};
