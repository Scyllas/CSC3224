#pragma once

#include <GL\glew.h>	
namespace Bengine {
	struct Position {
		Position() :x(0), y(0) {}
		Position(float X, float Y) :x(X), y(Y) {}
		float x;
		float y;
	};


	struct ColorRGBA8 {
		ColorRGBA8() : r(0), g(0), b(0), a(0) {	}
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
			r(R), g(G), b(B), a(A) {}
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};

	struct UV {
		UV() : u(0), v(0) {	}
		UV(float U, float V) : u(U), v(V) {	}
		float u;
		float v;
	};

	struct Vertex {

		Position position;

		ColorRGBA8 color;

		UV uv;

		void setPosition(float x, float y) {
			position = Bengine::Position(x, y);
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color = Bengine::ColorRGBA8(r, g, b, a);
		}
		void setUV(float u, float v) {
			uv = Bengine::UV(u, v);
		}
	};
}