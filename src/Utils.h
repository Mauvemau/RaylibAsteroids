#pragma once
#include "raylib.h"
#include <iostream>

#include <math.h>

const double m_pi = 3.14159265358979323846;

namespace Utils {
	Vector2 GetLastRelativePosition(Vector2 currentPos);
	Vector2 GetRelativePosition(Vector2 currentPos);
	Vector2 GetRandomSpawnPosition();
	void DrawCenteredText(const char* text, Vector2 pos, int fontSize, Color color);
	float Modulo(Vector2 vec);
	float DegreesToRadians(float deg);
	float RadiansToDegrees(float rad);
	Vector2 GetTargetVector(Vector2 origin, Vector2 target); // Returns a vector between two vectors.
	float GetDistance(Vector2 v1, Vector2 v2); // Returns distance between two vectors.
	float CalculateRotationAngle(Vector2 origin, Vector2 target); // Return angle between origin and position.
	void AdjustLastFrameSize(int width, int height);
}
