#version 330 core

#define MAX_LENGTH 16



struct Camera {
	vec3 Position;
	vec3 Direction;
	float ViewportWidth;
};

struct Sphere {
	vec3 Position;
	float Radius;
	vec4 Color;
};



in vec3 Pos;

uniform int UImageWidth;
uniform int UImageHeight;
uniform Camera UCamera;
uniform Sphere USphere;

out vec4 FragColor;



bool HasCollided(Sphere S, vec3 Ray, float t, vec3 Origin) {
	float a = dot(Ray, Ray);
	float b = 2 * dot(Ray, Origin - S.Position);
	float c = dot(Origin - S.Position, Origin - S.Position) - S.Radius * S.Radius;

	float discriminant = b * b - 4 * a * c;

	return discriminant > 0;
}

void main() {

	float UViewportHeight = UCamera.ViewportWidth * (float(UImageHeight) / float(UImageWidth));

	vec3 WorldUp = vec3(0.0, 1.0, 0.0);
	vec3 Right = cross(UCamera.Direction, WorldUp);
	vec3 Up = cross(Right, UCamera.Direction);

	vec3 WidthVec = Right * UCamera.ViewportWidth;
	vec3 HeightVec = Up * UViewportHeight;

	vec3 BottomLeftVec = UCamera.Direction - vec3(WidthVec / 2.0) - vec3(HeightVec / 2.0);

	vec3 Ray = BottomLeftVec + (WidthVec * gl_FragCoord.x / (UImageWidth - 1)) + (HeightVec * gl_FragCoord.y / (UImageHeight - 1));

	float t = 0.0;
	bool bHit = false;
	while (length(Ray * t) < MAX_LENGTH) {

		t += 0.01;

		if (HasCollided(USphere, Ray, t, UCamera.Position)) {
			bHit = true;
			FragColor = USphere.Color;
			break;
		}

	}

	if (!bHit) {
		FragColor = vec4(0.53, 0.80, 0.92, 1.0);
	}
}