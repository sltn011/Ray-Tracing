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



float HitPoint(Sphere S, vec3 Ray, float t, vec3 Origin) {
	float a = dot(Ray, Ray);
	float half_b = dot(Ray, Origin - S.Position);
	float c = dot(Origin - S.Position, Origin - S.Position) - S.Radius * S.Radius;

	float discriminant = half_b * half_b - a * c;

	if (discriminant < 0.0) {
		return -1.0;
	}
	else {
		return (-half_b - sqrt(discriminant) / a);
	}
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

		float HitPoint = HitPoint(USphere, Ray, t, UCamera.Position);
		if (HitPoint >= 0.0) {
			bHit = true;

			vec3 ImpactNormal = normalize(UCamera.Position + Ray * HitPoint - USphere.Position); // [-1; +1]
			vec3 ImpactNormalRGB = normalize((ImpactNormal + 1.0) / 2.0); // [0; +1]
			FragColor = vec4(ImpactNormalRGB, 1.0);

			break;
		}

	}

	if (!bHit) {
		FragColor = vec4(0.53, 0.80, 0.92, 1.0);
	}
}