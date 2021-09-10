#version 330 core

#define MAX_LENGTH 16



struct Camera {
	vec3 Position;
	vec3 Direction;
	float ViewportWidth;
};

struct Sphere {
	int ID;
	vec3 Position;
	float Radius;
	vec4 Color;
};

struct HitResult {
	bool bHit;				// True if ray intersected some object
	vec3 ImpactPoint;		// Location of impact
	vec3 ImpactNormal;		// Normal vector at impact point - outside of object
	bool bFrontFacing;		// True if ray intersected object from outside
	float RayMultiplier;	// ImpactPoint = Origin + Ray * RayMultiplier
	int HitObjectID;		// Unique ID of intersected object
};



in vec3 Pos;

uniform int UNumSamples;
uniform int UImageWidth;
uniform int UImageHeight;
uniform Camera UCamera;
uniform Sphere USphere;

out vec4 FragColor;


// Check if Ray sent from Origin point intersects with Sphere S
// Impact point can be calculated as Origin + Ray * t, where t is RayMultiplier
//
// if such t value exists and it lies in range [tMin; tMax] then it is considered as Ray-Object intersection
HitResult ImpactPoint(Sphere Object, vec3 Ray, float tMin, float tMax, vec3 Origin);

int GetRandomInt(int x);


void main() {

	float UViewportHeight = UCamera.ViewportWidth * (float(UImageHeight) / float(UImageWidth));

	vec3 WorldUp = vec3(0.0, 1.0, 0.0);
	vec3 Right = cross(UCamera.Direction, WorldUp);
	vec3 Up = cross(Right, UCamera.Direction);

	vec3 WidthVec = Right * UCamera.ViewportWidth;
	vec3 HeightVec = Up * UViewportHeight;

	vec3 BottomLeftVec = UCamera.Direction - vec3(WidthVec / 2.0) - vec3(HeightVec / 2.0);

	int wVal = int(gl_FragCoord.x);
	int hVal = int(gl_FragCoord.y);

	for (int i = 0; i < UNumSamples; ++i) {
		float wOff = sin(wVal) / 2.0;
		float hOff = cos(hVal) / 2.0;
		vec3 Ray = BottomLeftVec + (WidthVec * (gl_FragCoord.x + wOff) / (UImageWidth - 1)) + (HeightVec * (gl_FragCoord.y + hOff) / (UImageHeight - 1));
		wVal = GetRandomInt(wVal);
		hVal = GetRandomInt(hVal);

		HitResult Result = ImpactPoint(USphere, Ray, 0.0, float(MAX_LENGTH), UCamera.Position);
		if (Result.bHit) {
			vec3 ImpactNormalRGB = normalize((Result.ImpactNormal + 1.0) / 2.0); // [0; +1]
			FragColor += vec4(ImpactNormalRGB, 1.0);
		}
		else {
			FragColor += vec4(0.53, 0.80, 0.92, 1.0);
		}
	}

	FragColor.xyz /= UNumSamples;
	
}



HitResult ImpactPoint(Sphere Object, vec3 Ray, float tMin, float tMax, vec3 Origin) {
	float a = dot(Ray, Ray);
	float half_b = dot(Ray, Origin - Object.Position);
	float c = dot(Origin - Object.Position, Origin - Object.Position) - Object.Radius * Object.Radius;

	float discriminant = half_b * half_b - a * c;
	
	HitResult Result;
	if (discriminant < 0.0) {
		Result.bHit = false;
		return Result;
	}
	else {
		float t = (-half_b - sqrt(discriminant)) / a; // First root
		if (t < tMin || t > tMax) { // If first root not in [tMin; tMax] try second one
			t = (-half_b + sqrt(discriminant)) / a;
			if (t < tMin || t > tMax) {
				Result.bHit = false; // If second root not in [tMin; tMax] - no impact
				return Result; 
			}
		}
		Result.bHit = true;
		Result.ImpactPoint = Origin + Ray * t;
		Result.ImpactNormal = normalize(Result.ImpactPoint - Object.Position);
		Result.bFrontFacing = bool(dot(Result.ImpactNormal, Ray) < 0.0);
		Result.RayMultiplier = t;
		Result.HitObjectID = Object.ID;
		return Result;
	}
}

int GetRandomInt(int x) {
	int a = 48271;
	int c = 0;
	int m = 2147483647;
	return (a * x + c) % m;
}