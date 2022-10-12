#pragma once

#include "Spaceship.h"

namespace Game {
	void AddScore(int amount);
	void AddLive(int amount);
	void RemoveLive(int amount);
	void OpenUpgradeMenu();
	void StartGame();

	bool GetAutoshootActive(); // Devuelve si el autoshoot esta activo.
	bool GetHasStarted(); // Devuelve si el juego comenz� o si el jugador sigue leyendo el tutorial.
	bool GetInvaderActive();
	long GetScore();
	int GetLives();
	float GetGameTime();
	Ship& GetInvader();
	Ship& GetPlayer();
	bool GetIsHalted();
	float GetHaltTime();

	void SetAutoShoot(bool val);
	void SetInvader(bool active);
	void SetPaused(bool val);
	void SetHalted();

	void Update();
	void Init();
}