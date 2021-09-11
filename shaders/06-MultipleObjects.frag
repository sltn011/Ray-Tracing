#version 330 core

#define MAX_LENGTH  16
#define MAX_SPHERES 16



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
	vec4 ImpactPointColor;  // Color of hit object
	bool bFrontFacing;		// True if ray intersected object from outside
	float RayMultiplier;	// ImpactPoint = Origin + Ray * RayMultiplier
	int HitObjectID;		// Unique ID of intersected object
};



in vec3 Pos;

uniform int UNumSamples;
uniform int UImageWidth;
uniform int UImageHeight;
uniform Camera UCamera;

uniform int USphereNum;
uniform Sphere USphere[MAX_SPHERES];

out vec4 FragColor;


// Check if Ray sent from Origin point intersects with Sphere S
// Impact point can be calculated as Origin + Ray * t, where t is RayMultiplier
//
// if such t value exists and it lies in range [tMin; tMax] then it is considered as Ray-Object intersection
HitResult ImpactPoint(Sphere Object, vec3 Ray, float tMin, float tMax, vec3 Origin);

// Traces closest object with Ray sent from Origin point
HitResult TraceClosestObject(vec3 Ray, float tMin, float tMax, vec3 Origin);

// RANDOM
void InitRandom();
int GetRandomInt();
float GetRandomFloatNormalized();
int RandomSeed;


void main() {

	InitRandom();

	float UViewportHeight = UCamera.ViewportWidth * (float(UImageHeight) / float(UImageWidth));

	vec3 WorldUp = vec3(0.0, 1.0, 0.0);
	vec3 Right = cross(UCamera.Direction, WorldUp);
	vec3 Up = cross(Right, UCamera.Direction);

	vec3 WidthVec = Right * UCamera.ViewportWidth;
	vec3 HeightVec = Up * UViewportHeight;

	vec3 BottomLeftVec = UCamera.Direction - vec3(WidthVec / 2.0) - vec3(HeightVec / 2.0);

	vec4 TotalColor = vec4(0.0);
	for (int Sample = 0; Sample < UNumSamples; ++Sample) {
		float wOff = GetRandomFloatNormalized() / 2.0;
		float hOff = GetRandomFloatNormalized() / 2.0;
		vec3 Ray = BottomLeftVec + (WidthVec * (gl_FragCoord.x + wOff) / (UImageWidth - 1)) + (HeightVec * (gl_FragCoord.y + hOff) / (UImageHeight - 1));

		HitResult ClosestHit = TraceClosestObject(Ray, 0.0, float(MAX_LENGTH), UCamera.Position);

		if (ClosestHit.bHit) {
			vec3 HitNormal = ClosestHit.ImpactNormal;
			vec3 HitNormalRGB = (HitNormal + 1.0) / 2.0;
			TotalColor += vec4(HitNormalRGB, 1.0);
		}
		else {
			TotalColor += vec4(0.53, 0.80, 0.92, 1.0);
		}
	}

	FragColor = TotalColor / UNumSamples;
	
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
		Result.ImpactPointColor = Object.Color;
		Result.bFrontFacing = bool(dot(Result.ImpactNormal, Ray) < 0.0);
		Result.RayMultiplier = t;
		Result.HitObjectID = Object.ID;
		return Result;
	}
}

HitResult TraceClosestObject(vec3 Ray, float tMin, float tMax, vec3 Origin) {
	float SampleSmallestRayMultiplier = float(MAX_LENGTH);

	HitResult ClosestResult;
	ClosestResult.bHit = false;

	for (int SphereIndex = 0; SphereIndex < USphereNum; ++SphereIndex) {
		HitResult Result = ImpactPoint(USphere[SphereIndex], Ray, tMin, tMax, UCamera.Position);
		if (Result.bHit && Result.RayMultiplier < SampleSmallestRayMultiplier) {
			SampleSmallestRayMultiplier = Result.RayMultiplier;
			ClosestResult = Result;
		}
	}

	return ClosestResult;
}

void InitRandom() {
	RandomSeed = int(gl_FragCoord.x * UImageWidth + gl_FragCoord.y);
}

int GetRandomInt() {
	int a = 48271;
	int c = 0;
	int m = 2147483647;
	RandomSeed = (a * RandomSeed + c) % m;
	return RandomSeed;
}

float GetRandomFloatNormalized() {
	int n = GetRandomInt();
	return sin(n);
}