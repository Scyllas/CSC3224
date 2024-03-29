#include "Agent.h"



Agent::Agent()
{
}


Agent::~Agent()
{
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData) {

	std::vector <glm::vec2> collideTilePositions;

	//check corners
	//corner 1
	checkTilePosition(
		levelData,
		collideTilePositions,
		m_position.x,
		m_position.y);
	//corner 2
	checkTilePosition(
		levelData,
		collideTilePositions,
		m_position.x + AGENT_WIDTH,
		m_position.y);
	//corner 3
	checkTilePosition(
		levelData,
		collideTilePositions,
		m_position.x,
		m_position.y + AGENT_WIDTH);
	//corner 4
	checkTilePosition(
		levelData,
		collideTilePositions,
		m_position.x + AGENT_WIDTH,
		m_position.y + AGENT_WIDTH);
	
	if (collideTilePositions.size() == 0) return false;

	for (int i = 0; i < collideTilePositions.size(); i++) {
		collideWithTile(collideTilePositions[i]);
	}
	return true;
}

bool Agent::collideWithAgent(Agent * agent){

	const float MIN_DISTANCE = AGENT_RADIUS *2.f;

	glm::vec2 centerPosA = m_position + glm::vec2(AGENT_RADIUS);

	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;

	float distance = glm::length(distVec);

	float collisionDepth = MIN_DISTANCE - distance;
	if (collisionDepth > 0) {

		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;
		m_position += collisionDepthVec / 2.f;
		agent->m_position -= collisionDepthVec / 2.f;
		return true;
	}
	return false;
}


void Agent::draw(Engine::SpriteBatch & m_spriteBatch) {

	glm::vec4 uvRect(0.f, 0.f, 1.f, 1.f);
	glm::vec4 destRect;
	destRect.x = m_position.x;
	destRect.y = m_position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;
	m_spriteBatch.draw(destRect, uvRect, m_textureID, 0.f, m_color, m_direction);

}

bool Agent::applyDamage(float damage)
{
	m_health -= damage;
	if (m_health <= 0) {
		return true;
	}
	
	return false;

}

void Agent::checkTilePosition(
	const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePositions, float x, float y) {

	glm::vec2 cornerPos = glm::vec2(
		floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));
	
	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].size() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size()) {
		return;
	}
	if (levelData[cornerPos.y][cornerPos.x] != '.') {

		collideTilePositions.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2(TILE_WIDTH / 2.f));

	}

}

void Agent::collideWithTile(glm::vec2 tilePos) {

	const float TILE_RADIUS = (float)TILE_WIDTH / 2.f;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;


	glm::vec2 centerPlayerPos = m_position + glm::vec2(AGENT_RADIUS);
	

	glm::vec2 distVec = centerPlayerPos - tilePos;

	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);


	if (xDepth > 0 && yDepth > 0) {

		if (std::max(xDepth, 0.f) < std::max(yDepth, 0.f)) {
			if (distVec.x < 0) {
				m_position.x -= xDepth;
			}else{
				m_position.x += xDepth;
			}
		}
		else {
			if (distVec.y < 0) {
				m_position.y -= yDepth;
			}
			else {
				m_position.y += yDepth;
			}
		}
	}

}
