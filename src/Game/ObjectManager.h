#pragma once
#include "raylib.h"
#include "Asteroid.h"
#include "Bullet.h"

/*
Pseudo Pool, se ocupa de instanciar, activar y desactivar objetos dentro de arrays.
*/

namespace ObjManager {
	// Bullets
	void DeActivateBullet(int id);
	void ActivateBullet(Vector2 pos, float size, float direction, float speed);

	// Asteroids
	void DeActivateAsteroid(AsteroidType type, int id);
	void ActivateAsteroid(AsteroidType type); // Sobrecarga, crea un asteroide de caracteristicas random.
	void ActivateAsteroid(Vector2 pos, AsteroidType type, float direction, float speed);

	// General
	void Draw();
	void Update();
	void Init();
}