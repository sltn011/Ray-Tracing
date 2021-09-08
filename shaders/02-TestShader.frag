#version 330 core

in vec3 Pos;

uniform int UImageWidth;
uniform int UImageHeight;

out vec4 FragColor;

void main() {

	if (gl_FragCoord.x < UImageWidth / 2 && gl_FragCoord.y < UImageHeight / 2) {
		FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (gl_FragCoord.x >= UImageWidth / 2 && gl_FragCoord.y < UImageHeight / 2) {
		FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else if (gl_FragCoord.x < UImageWidth / 2 && gl_FragCoord.y >= UImageHeight / 2) {
		FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	else {
		FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	}
}