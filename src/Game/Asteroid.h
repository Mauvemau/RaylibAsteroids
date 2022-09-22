#pragma once
#include "raylib.h"

enum class AsteroidType {
	BIG,
	MEDIUM,
	SMALL
};

struct Asteroid {
	Vector2 pos;
	float radius;
	float direction;
	float speed;
};

namespace Asteroids {
	void Draw(Asteroid asteroid);
	void Update(Asteroid& asteroid);
	Asteroid Create();
	void Init(Asteroid& asteroid); // Sobrecarga, crea un asteroide grande en una posicion, direccion y velocidad random.
	void Init(Asteroid& asteroid, Vector2 pos, AsteroidType type, float direction, float speed);
}
