#include "Box.h"



Box::Box()
{
}


Box::~Box()
{
}

void Box::init(
	b2World* world, 
	const glm::vec2& position, 
	const glm::vec2& dimensions, 
	Engine::GLTexture texture, 
	Engine::ColorRGBA8 color, 
	bool fixedRotation, 
	bool isDynamic,
	float angle, /* = 0.0f */
	glm::vec4 uvRect /*= glm::vec4(0.f,0.f,1.f,1.f)*/) {

	m_uvRect = uvRect;
	m_dimensions = dimensions;
	m_color = color;
	m_texture = texture;
	m_fixedRotation = fixedRotation;
	m_isDynamic = isDynamic;

	//make body
	b2BodyDef bodyDef;
	
	if (isDynamic) {
		bodyDef.type = b2_dynamicBody;
	}
	else {
		bodyDef.type = b2_staticBody;
	}

	bodyDef.position.Set(position.x, position.y);
	bodyDef.fixedRotation = fixedRotation;
	bodyDef.angle = angle;
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.f, dimensions.y / 2.f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.3f;
	m_fixture = m_body->CreateFixture(&fixtureDef);
}

void Box::destroy(b2World* world) {
	world->DestroyBody(m_body);
}

void Box::draw(Engine::SpriteBatch& spriteBatch)
{
	glm::vec4 destRect;
	destRect.x = m_body->GetPosition().x - m_dimensions.x / 2.f;
	destRect.y = m_body->GetPosition().y - m_dimensions.y / 2.f;
	destRect.z = m_dimensions.x;
	destRect.w = m_dimensions.y;
	spriteBatch.draw(destRect, m_uvRect, m_texture.id, 0.f, m_color, m_body->GetAngle());
}
