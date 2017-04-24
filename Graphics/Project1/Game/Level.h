#pragma once
#include <string>
#include <vector>
#include <Engine/EngineErrors.h>
#include <Engine\SpriteBatch.h>



const int TILE_WIDTH = 64;

class Level
{
public:
	//load level
	Level(const std::string& fileName);
	~Level();

	void draw();

	int getWidth() const { return m_levelData[0].size(); }
	int getHeight() const { return m_levelData.size(); }
	int getNumHumans() const { return m_numHumans; }

	const std::vector<std::string>& getLevelData() { return m_levelData; };
	
	glm::vec2 getStartPlayerPos() const { return m_startPlayerPos; }
	const std::vector<glm::vec2>& getZombieStartPositions() const { return m_zombieStartPositions; }

private:

	Engine::SpriteBatch m_spriteBatch;
	std::vector<std::string> m_levelData;
	int m_numHumans;

	glm::vec2 m_startPlayerPos;
	std::vector<glm::vec2> m_zombieStartPositions;
};

