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


// Check if Ray sent from Origin point intersects with Sphere S
// Impact point can be calculated as Origin + Ray * t
//
// if such t value exists and it lies in range [tMin; tMax] then 
// first value in returned pair is 1 and second value is equal to t
// otherwise both values are 0
vec2 ImpactPoint(Sphere S, vec3 Ray, float tMin, float tMax, vec3 Origin);



void main() {

	float UViewportHeight = UCamera.ViewportWidth * (float(UImageHeight) / float(UImageWidth));

	vec3 WorldUp = vec3(0.0, 1.0, 0.0);
	vec3 Right = cross(UCamera.Direction, WorldUp);
	vec3 Up = cross(Right, UCamera.Direction);

	vec3 WidthVec = Right * UCamera.ViewportWidth;
	vec3 HeightVec = Up * UViewportHeight;

	vec3 BottomLeftVec = UCamera.Direction - vec3(WidthVec / 2.0) - vec3(HeightVec / 2.0);

	vec3 Ray = BottomLeftVec + (WidthVec * gl_FragCoord.x / (UImageWidth - 1)) + (HeightVec * gl_FragCoord.y / (UImageHeight - 1));

	vec2 ImpactResult = ImpactPoint(USphere, Ray, 0.0, float(MAX_LENGTH), UCamera.Position);
	if (bool(ImpactResult.x)) {
		vec3 ImpactNormal = normalize(UCamera.Position + Ray * ImpactResult.y - USphere.Position); // [-1; +1]
		vec3 ImpactNormalRGB = normalize((ImpactNormal + 1.0) / 2.0); // [0; +1]
		FragColor = vec4(ImpactNormalRGB, 1.0);
	}
	else {
		FragColor = vec4(0.53, 0.80, 0.92, 1.0);
	}
}



vec2 ImpactPoint(Sphere S, vec3 Ray, float tMin, float tMax, vec3 Origin) {
	float a = dot(Ray, Ray);
	float half_b = dot(Ray, Origin - S.Position);
	float c = dot(Origin - S.Position, Origin - S.Position) - S.Radius * S.Radius;

	float discriminant = half_b * half_b - a * c;

	if (discriminant < 0.0) {
		return vec2(0.0, 0.0); // no impact
	}
	else {
		float t = (-half_b - sqrt(discriminant)) / a; // First root
		if (t < tMin || t > tMax) { // If first root not in [tMin; tMax] try second one
			t = (-half_b + sqrt(discriminant)) / a;
			if (t < tMin || t > tMax) {
				return vec2(0.0, 0.0); // If second root not in [tMin; tMax] - no impact
			}
		}
		return vec2(1.0, t);
	}
}