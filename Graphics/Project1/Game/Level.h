#pragma once
#include <string>
#include <vector>
#include <Bengine\Errors.h>
#include <Bengine\SpriteBatch.h>



const int TILE_WIDTH = 64;

class Level
{
public:
	//load level
	Level(const std::string& fileName);
	~Level();

	void draw();

	int getWidth() const { return _levelData[0].size(); }
	int getHeight() const { return _levelData.size(); }
	int getNumHumans() const { return _numHumans; }

	const std::vector<std::string>& getLevelData() { return _levelData; };
	
	glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
	const std::vector<glm::vec2>& getZombieStartPositions() const { return _zombieStartPositions; }

private:

	Bengine::SpriteBatch _spriteBatch;
	std::vector<std::string> _levelData;
	int _numHumans;

	glm::vec2 _startPlayerPos;
	std::vector<glm::vec2> _zombieStartPositions;
};

