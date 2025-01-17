#include "ObjectManager.h"
#include "CollisionManager.h"
#include "AssetLoader.h" // Para los sonidos.
#include "Game.h" // Para el game time.
#include "Animations.h" // Para las explosiones.

#include <iostream>

namespace ObjManager {
	// Asteroids
	const int maxAsteroids = 200;
	Asteroid asteroids[maxAsteroids];
	int activeAsteroids;

	//Bullets
	const int maxBullets = 50;
	Bullet bullets[maxBullets];
	int activeBullets;

	// Pickups
	const int maxPickups = 25;
	Pickup pickups[maxPickups];
	int activePickups;
	
	void HandleCollision(int bulletID, int asteroidID);
	// Asteroids
	void DestroyAsteroid(int id, float angle);
	void PrintLog(AsteroidType type, bool creating);
	// Bullets
	void HandleBulletLifeTime(int id);

	// --
	
	void HandleCollision(int bulletID, int asteroidID) {
		float bulletAngle = bullets[bulletID].direction;
		DeActivateBullet(bulletID);
		DestroyAsteroid(asteroidID, bulletAngle);
	}

	// Asteroids
	void DestroyAsteroid(int id, float angle) {
		switch (asteroids[id].type)
		{
		case AsteroidType::BIG:
			Game::AddScore(10);
			ActivateAsteroid(asteroids[id].pos, AsteroidType::MEDIUM, 
				asteroids[id].direction - .25f, Asteroids::GetSpeed(AsteroidType::MEDIUM));
			ActivateAsteroid(asteroids[id].pos, AsteroidType::MEDIUM,
				asteroids[id].direction + .25f, Asteroids::GetSpeed(AsteroidType::MEDIUM));
			break;
		case AsteroidType::MEDIUM:
			Game::AddScore(25);
			ActivateAsteroid(asteroids[id].pos, AsteroidType::SMALL,
				angle - .25f, Asteroids::GetSpeed(AsteroidType::SMALL));
			ActivateAsteroid(asteroids[id].pos, AsteroidType::SMALL,
				angle + .25f, Asteroids::GetSpeed(AsteroidType::SMALL));
			break;
		default:
			Game::AddScore(50);
			break;
		}
		Animations::PlayAnimation(Anims::EXPLOSION, asteroids[id].pos, 
			Vector2{ static_cast<float>(Asteroids::GetSize(asteroids[id].type) * 6), static_cast<float>(Asteroids::GetSize(asteroids[id].type) * 6) });
		DeActivateAsteroid(id);
		Assets::PlayAudio((Audio)GetRandomValue(static_cast<int>(Audio::EXPLOSION_1), static_cast<int>(Audio::EXPLOSION_3)), .5);
		Game::AddAsteroidsDestroyed(1);
	}

	void PrintLog(AsteroidType type, bool creating) {
		std::cout << ((creating) ?  "Created " : "Destroyed ") << 
			Asteroids::GetTypeString(type) << " Asteroid! (" << 
			activeAsteroids << " active)\n";
	}

	// Bullets
	void HandleBulletLifeTime(int id) {
		if (bullets[id].lifeTime < (Game::GetGameTime() - bullets[id].spawnTime))
			DeActivateBullet(id);
	}

	void PrintLog(bool creating) {
		std::cout << ((creating) ? "Created " : "Destroyed ") <<"Bullet! (" <<
			activeBullets << " active)\n";
	}

	// Global

	int GetMaxPickups() {
		return maxPickups;
	}

	int GetActivePickups() {
		return activePickups;
	}

	int GetMaxBullets() {
		return maxBullets;
	}

	int GetActiveBullets() {
		return activeBullets;
	}

	int GetMaxAsteroids() {
		return maxAsteroids;
	}

	int GetActiveAsteroids() {
		return activeAsteroids;
	}
	
	// Pickups

	void DeActivatePickup(int id) {
		if (id < activePickups) {
			pickups[id] = pickups[activePickups - 1];
			activePickups--;
		}
	}

	void ActivatePickup() {
		if (activePickups < maxPickups) {
			Pickups::Init(pickups[activePickups], PickupType::COIN);
			activePickups++;
		}
	}

	void ActivatePickup(PickupType type) {
		if (activePickups < maxPickups) {
			Pickups::Init(pickups[activePickups], type);
			activePickups++;
		}
	}

	// Bullets
	void DeActivateBullet(int id) {
		if (id < activeBullets) {
			bullets[id] = bullets[activeBullets - 1];
			activeBullets--;
		}
	}

	void ActivateBullet(Vector2 pos, float size, float direction, float speed, float lifeTime, bool hurtsPlayer) {
		if (activeBullets < maxBullets) {
			Bullets::Init(bullets[activeBullets], pos, size, direction, speed, lifeTime, Game::GetGameTime(), hurtsPlayer);
			activeBullets++;
		}
	}

	// Asteroids
	void DeActivateAsteroid(int id) {
		if (id < activeAsteroids) {
			asteroids[id] = asteroids[activeAsteroids - 1];
			activeAsteroids--;
		}
	}

	void ActivateAsteroid(AsteroidType type) {
		if (activeAsteroids < maxAsteroids) {
			Asteroids::Init(asteroids[activeAsteroids], type);
			activeAsteroids++;
		}
	}

	void ActivateAsteroid(Vector2 pos, AsteroidType type, float direction, float speed) {
		if (activeAsteroids < maxAsteroids) {
			Asteroids::Init(asteroids[activeAsteroids], pos, type, direction, speed);
			activeAsteroids++;
		}
	}

	// General
	void Draw() {
		// Bullets
		for (int i = 0; i < activeBullets; i++) {
			Bullets::Draw(bullets[i]);
		}
		// Pickups
		for (int i = 0; i < activePickups; i++) {
			Pickups::Draw(pickups[i]);
		}
		// Asteroids
		for (int i = 0; i < activeAsteroids; i++) {
			Asteroids::Draw(asteroids[i]);
		}
	}

	void AdjustToRes(){
		// Asteroids
		for (int i = 0; i < activeAsteroids; i++) {
			Asteroids::AdjustToRes(asteroids[i]);
		}
		// Bullets
		for (int i = 0; i < activeBullets; i++) {
			Bullets::AdjustToRes(bullets[i]);
		}
		// Pickups
		for (int i = 0; i < activePickups; i++) {
			Pickups::AdjustToRes(pickups[i]);
		}
	}

	void Update() {
		// Asteroids
		for (int i = 0; i < activeAsteroids; i++) {
			Asteroids::Update(asteroids[i]);
			if (Collisions::CheckShipAsteroidCollision(asteroids[i])) {
				DeActivateAsteroid(i);
				Spaceship::ResetAcceleration(Game::GetPlayer());
				Game::SetHalted();
				Game::RemoveLive(1);
				Assets::PlayAudio(Audio::HURT, 1);
			}
		}
		// Bullets
		for (int i = 0; i < activeBullets; i++) {
			Bullets::Update(bullets[i]);
			HandleBulletLifeTime(i);
			if (bullets[i].hurtsPlayer) {
				if (Collisions::CheckBulletShipCollision(bullets[i], Game::GetPlayer())) {
					DeActivateBullet(i);
					Spaceship::ResetAcceleration(Game::GetPlayer());
					Game::SetHalted();
					Game::RemoveLive(1);
					Assets::PlayAudio(Audio::HURT, 1);
					if(Game::GetInvaderActive())
						Game::SetInvader(false);
				}
			}
			else {
				if (Game::GetInvaderActive())
					if (Collisions::CheckBulletShipCollision(bullets[i], Game::GetInvader())) {
						Game::SetInvader(false);
						Game::AddScore(100);
						Animations::PlayAnimation(Anims::EXPLOSION, Game::GetInvader().pos,
							Vector2{ static_cast<float>(Spaceship::GetCollisionRadius(Game::GetInvader()) * 12.0f ), static_cast<float>(Spaceship::GetCollisionRadius(Game::GetInvader()) * 12.0f ) });
						Assets::PlayAudio((Audio)GetRandomValue(static_cast<int>(Audio::EXPLOSION_1), static_cast<int>(Audio::EXPLOSION_3)), .5);
					}
			}
		}
		// Primero Updateamos todos, despues loopeamos nuevamente para checkear colisiones.
		for (int i = 0; i < activeBullets; i++) {
			for (int j = 0; j < activeAsteroids; j++) {
				if (Collisions::CheckBulletAsteroidCollision(bullets[i], asteroids[j]))
					HandleCollision(i, j);
			}
		}
		// Pickups
		for (int i = 0; i < activePickups; i++) {
			Pickups::Update(pickups[i]);
			if (Collisions::CircleCircleCollision(pickups[i].pos,
				(Spaceship::GetCollisionRadius(Game::GetPlayer()) * 2.5f),
				Game::GetPlayer().pos, Spaceship::GetCollisionRadius(Game::GetPlayer()) * 2.5f)) {

				PickupType type = pickups[i].type;
				DeActivatePickup(i);
				Pickups::HandlePickup(type);
			}
		}
	}

	void Init() {
		// Asteroids
		for (int i = 0; i < maxAsteroids; i++) {
			asteroids[i] = Asteroids::Create();
		}
		activeAsteroids = 0;

		// Bullets
		for (int i = 0; i < maxBullets; i++) {
			bullets[i] = Bullets::Create();
		}
		activeBullets = 0;

		// Pickups
		for (int i = 0; i < maxPickups; i++) {
			pickups[i] = Pickups::Create();
		}
		activePickups = 0;
	}
}
