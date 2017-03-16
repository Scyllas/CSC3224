#include "Level.h"
#include <fstream>
#include <iostream>

#include <Bengine\ResourceManager.h>

Level::Level(const std::string & fileName)
{

	std::ifstream file;
	file.open(fileName);

	if (file.fail()) {
		Bengine::fatalError("failed to open file" + fileName);
	}

	//ignore first string, get number
	std::string tmp;
	file >> tmp >> _numHumans;

	std::getline(file, tmp);//throw away first line
	while (std::getline(file, tmp)) {
		_levelData.push_back(tmp);
	}

	_spriteBatch.init();
	_spriteBatch.begin();

	glm::vec4 uvRect(0.f, 0.f, 1.f, 1.f);

	for (int y = 0; y < _levelData.size(); y++) {
		for (int x = 0; x < _levelData[y].size(); x++) {

			char tile = _levelData[y][x];
			glm::vec4 destRect(x*TILE_WIDTH, y*TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			switch (tile) {
			case 'R':
			case 'B':
				_spriteBatch.draw(destRect,
					uvRect,
					Bengine::ResourceManager::getTexture("Textures/red_bricks.png").id,
					0.f,
					Bengine::ColorRGBA8(255, 255, 255, 255));
				break;
			case 'G':
				_spriteBatch.draw(destRect,
					uvRect,
					Bengine::ResourceManager::getTexture("Textures/glass.png").id,
					0.f,
					Bengine::ColorRGBA8(255, 255, 255, 255));
				break;
			case 'L':
				_spriteBatch.draw(destRect,
					uvRect,
					Bengine::ResourceManager::getTexture("Textures/light_bricks.png").id,
					0.f,
					Bengine::ColorRGBA8(255, 255, 255, 255));
				break;
			case '@':
				_levelData[y][x] = '.';
				_startPlayerPos.x = x* TILE_WIDTH;
				_startPlayerPos.y = y* TILE_WIDTH;
				break;
			case 'Z':
				_levelData[y][x] = '.';
				_zombieStartPositions.emplace_back(x* TILE_WIDTH, y* TILE_WIDTH);
				break;
			case '.':
				break;
			default:
				std::printf("Unexpected symbol %c at:  (%d,%d)", tile, x, y);
				break;
			}
		}
	}
	_spriteBatch.end();
}

Level::~Level()
{
}

void Level::draw() {

	_spriteBatch.renderBatch();

}
