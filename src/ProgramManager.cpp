#include "raylib.h"

#include "ProgramManager.h"
#include "Menu/MainMenu.h"
#include "Game/Game.h"

#include <iostream>

ProgramStatus programStatus; // El estado actual del juego.
bool gameShouldClose; // Para salir del game loop.

const int screenWidth = 1024;
const int screenHeight = 768;

void InitRespectiveStatus(ProgramStatus status);

void CloseProgram();
void UpdateProgram();
void InitProgram();

// --

void InitRespectiveStatus(ProgramStatus status) {
	switch (status)
	{
	case ProgramStatus::MAINMENU:
		MainMenu::Init();
		break;
	case ProgramStatus::INGAME:
		Game::Init();
		break;
	default:
		std::cout << "Invalid program Status! [ProgramManager.cpp - InitRespectiveStatus()]\n";
		break;
	}
}

void CloseProgram() {
	CloseWindow();
}

void UpdateProgram() {
	while (!WindowShouldClose() && !gameShouldClose) {
		switch (programStatus)
		{
		case ProgramStatus::MAINMENU:
			MainMenu::Update();
			break;
		case ProgramStatus::INGAME:
			Game::Update();
			break;
		default:
			std::cout << "Invalid program Status! [ProgramManager.cpp - UpdateProgram()]\n";
			break;
		}
	}
}

void InitProgram() {
	InitWindow(screenWidth, screenHeight, "Raylib Asteroids");
	SetProgramStatus(ProgramStatus::MAINMENU);

}

// Global

void SetGameShouldClose(bool value) {
	gameShouldClose = value;
}

void SetProgramStatus(ProgramStatus status) {
	InitRespectiveStatus(status);
	programStatus = status;
}

void StartProgram() {
	InitProgram();
	UpdateProgram();
	CloseProgram();
}