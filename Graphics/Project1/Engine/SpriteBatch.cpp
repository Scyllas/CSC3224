#include "SpriteBatch.h"

#include <algorithm>

namespace Engine {

	Glyph::Glyph(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint Texture, float Depth, const ColorRGBA8 & color) :
		texture(Texture),
		depth(Depth)
	{


		topLeft.color = color;
		topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(destRect.x, destRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;
		bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	}

	Glyph::Glyph(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint Texture, float Depth, const ColorRGBA8 & color, float angle) :
		texture(Texture),
		depth(Depth)
	{
		glm::vec2 halfDims(destRect.z / 2.f, destRect.w / 2.f);
		glm::vec2 tl(-halfDims.x, halfDims.y);
		glm::vec2 bl(-halfDims.x, -halfDims.y);
		glm::vec2 br(halfDims.x, -halfDims.y);
		glm::vec2 tr(halfDims.x, halfDims.y);

		tl = (rotatePoint(tl, angle)) + halfDims;
		bl = (rotatePoint(bl, angle)) + halfDims;
		br = (rotatePoint(br, angle)) + halfDims;
		tr = (rotatePoint(tr, angle)) + halfDims;

		topLeft.color = color;
		topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = color;
		bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = color;
		topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	}

	glm::vec2 Glyph::rotatePoint(glm::vec2 pos, float angle)
	{
		glm::vec2 newv;
		newv.x = pos.x * cos(angle) - pos.y * sin(angle);
		newv.y = pos.x * sin(angle) + pos.y * cos(angle);

		return newv;
	}

	SpriteBatch::SpriteBatch() {

	}


	SpriteBatch::~SpriteBatch() {

	}
	void SpriteBatch::init() {

		createVertexArray();

	}

	void SpriteBatch::dispose() {
		if (m_vao != 0) {
			glDeleteVertexArrays(1, &m_vao);
			m_vao = 0;

		}
		if (m_vbo != 0) {
			glDeleteBuffers(1, &m_vbo);
			m_vbo = 0;

		}

	}


	void SpriteBatch::begin(GlyphSortType sortType /*GlyphSortType::TEXTURE*/) {

		m_sortType = sortType;
		m_renderBatches.clear();

		m_glyphs.clear();

	}

	void SpriteBatch::end() {

		m_glyphPointers.resize(m_glyphs.size());
		for (size_t i = 0; i < m_glyphs.size(); i++) {
			m_glyphPointers[i] = &m_glyphs[i];
		}
		sortGlyphs();
		createRenderBatches();

	}

	void SpriteBatch::draw(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint texture, float depth, const ColorRGBA8 & color) {

		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color);

	}

	void SpriteBatch::draw(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint texture, float depth, const ColorRGBA8 & color, float angle) {

		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);

	}

	void SpriteBatch::draw(const glm::vec4 & destRect, const glm::vec4 & uvRect, GLuint texture, float depth, const ColorRGBA8 & color, const glm::vec2& dir) {

		const glm::vec2 right(1.f, 0.f);
		float angle = acos(glm::dot(right, dir));
		if (dir.y < 0.f) angle = -angle;
		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);

	}

	void SpriteBatch::renderBatch() {

		glBindVertexArray(m_vao);

		for (size_t i = 0; i < m_renderBatches.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches() {

		std::vector<Vertex> vertices;
		vertices.resize(m_glyphPointers.size() * 6);

		if (m_glyphPointers.empty()) { return; }

		int offset = 0;

		int cv = 0; //current vertex

		m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture);

		vertices[cv++] = m_glyphPointers[0]->topLeft;
		vertices[cv++] = m_glyphPointers[0]->bottomLeft;
		vertices[cv++] = m_glyphPointers[0]->bottomRight;

		vertices[cv++] = m_glyphPointers[0]->bottomRight;
		vertices[cv++] = m_glyphPointers[0]->topRight;
		vertices[cv++] = m_glyphPointers[0]->topLeft;

		offset += 6;

		for (size_t cg = 1; cg < m_glyphPointers.size(); cg++) {

			if (m_glyphPointers[cg]->texture != m_glyphPointers[cg - 1]->texture) {
				m_renderBatches.emplace_back(offset, 6, m_glyphPointers[cg]->texture);
			}
			else {
				m_renderBatches.back().numVertices += 6;
			}

			vertices[cv++] = m_glyphPointers[cg]->topLeft;
			vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
			vertices[cv++] = m_glyphPointers[cg]->bottomRight;

			vertices[cv++] = m_glyphPointers[cg]->bottomRight;
			vertices[cv++] = m_glyphPointers[cg]->topRight;
			vertices[cv++] = m_glyphPointers[cg]->topLeft;
			offset += 6;

		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		//orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::createVertexArray() {

		if (m_vao == 0) {
			glGenVertexArrays(1, &m_vao);
		}
		glBindVertexArray(m_vao);

		if (m_vbo == 0) {
			glGenBuffers(1, &m_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//colour attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}
	void SpriteBatch::sortGlyphs() {

		switch (m_sortType) {
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBackToFront);
			break;

		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);
			break;

		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
			break;
		}


	}

	bool SpriteBatch::compareFrontToBack(Glyph * a, Glyph * b) {
		return(a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph * a, Glyph * b) {
		return(a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph * a, Glyph * b) {
		return(a->texture < b->texture);
	}

}