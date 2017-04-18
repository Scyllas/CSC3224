#pragma once

#include "Box.h"
#include "Capsule.h"
#include <Bengine\SpriteBatch.h>
#include <Bengine\TileSheet.h>
#include <Bengine\ResourceManager.h>
#include <Bengine\InputManager.h>
#include <SDL/SDL.h>
#include <iostream>

enum class PlayerMoveState { STANDING, RUNNING, PUNCHING, IN_AIR };

class PlayerChar
{
public:

	void init(b2World* world,
		const glm::vec2& position,
		const glm::vec2& drawDims,
		glm::vec2& collisionDims,
		Bengine::ColorRGBA8 color);

	void destroy(b2World* world);

	void draw(Bengine::SpriteBatch& spriteBatch);
	void drawDebug(Bengine::DebugRenderer& debugRenderer);

	void update(Bengine::InputManager& inputManager);

	const Capsule& getCapsule() const { return m_capsule; }

	glm::vec2 getPosition() const {
		glm::vec2 rv;
		rv.x = m_capsule.getBody()->GetPosition().x;
		rv.y = m_capsule.getBody()->GetPosition().y;
		return rv;
	}

private:
	glm::vec2 m_drawDims;
	Bengine::ColorRGBA8 m_color;
	Bengine::TileSheet m_texture;
	Capsule m_capsule;
	PlayerMoveState m_moveState = PlayerMoveState::STANDING;
	float m_animTime = 0.f;
	int m_direction = 1; // 1 or -1
	bool m_onGround = false;
	bool m_isPunching = false;
};


