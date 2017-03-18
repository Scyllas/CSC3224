#version 130

in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec4 fragmentColor;
out vec2 fragmentPosition;
out vec2 fragmentUV;

uniform mat4 P;

void main(){

	GL_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
	GL_Position.z = 0.0;
	GL_Position.w = 1.0;
	
	fragmentPosition = vertexPosition;
	fragmentColor = vertexColor;
	fragmentUV  = vec2(vertexUV.x, 1.0 - vertexUV.y);
}