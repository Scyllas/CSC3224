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
	file >> tmp >> m_numHumans;

	std::getline(file, tmp);//throw away first line
	while (std::getline(file, tmp)) {
		m_levelData.push_back(tmp);
	}

	m_spriteBatch.init();
	m_spriteBatch.begin();

	glm::vec4 uvRect(0.f, 0.f, 1.f, 1.f);

	for (int y = 0; y < m_levelData.size(); y++) {
		for (int x = 0; x < m_levelData[y].size(); x++) {

			char tile = m_levelData[y][x];
			glm::vec4 destRect(x*TILE_WIDTH, y*TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			switch (tile) {
			case 'R':
			case 'B':
				m_spriteBatch.draw(destRect,
					uvRect,
					Bengine::ResourceManager::getTexture("Textures/red_bricks.png").id,
					0.f,
					Bengine::ColorRGBA8(255, 255, 255, 255));
				break;
			case 'G':
				m_spriteBatch.draw(destRect,
					uvRect,
					Bengine::ResourceManager::getTexture("Textures/glass.png").id,
					0.f,
					Bengine::ColorRGBA8(255, 255, 255, 255));
				break;
			case 'L':
				m_spriteBatch.draw(destRect,
					uvRect,
					Bengine::ResourceManager::getTexture("Textures/light_bricks.png").id,
					0.f,
					Bengine::ColorRGBA8(255, 255, 255, 255));
				break;
			case '@':
				m_levelData[y][x] = '.';
				m_startPlayerPos.x = x* TILE_WIDTH;
				m_startPlayerPos.y = y* TILE_WIDTH;
				break;
			case 'Z':
				m_levelData[y][x] = '.';
				m_zombieStartPositions.emplace_back(x* TILE_WIDTH, y* TILE_WIDTH);
				break;
			case '.':
				break;
			default:
				std::printf("Unexpected symbol %c at:  (%d,%d)", tile, x, y);
				break;
			}
		}
	}
	m_spriteBatch.end();
}

Level::~Level()
{
}

void Level::draw() {

	m_spriteBatch.renderBatch();

}
