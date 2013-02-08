#include "SDL/SDLBmp.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Timer.h"

GameManager::GameManager()
{
	SDLManager::Instance().init();
	m_window = SDLManager::Instance().createWindow("My Awesome SDL 2.0 Game");
	Timer::Instance().init();
}

void GameManager::play()
{
	bool notGameOver = true;
	SDLBmp backround("Assets/gfx/sdl2.bmp");
	SDLBmp player("Assets/gfx/sdl_bro.bmp");

	while (notGameOver)
	{
		InputManager::Instance().Update();
		Timer::Instance().update();

		float displacement = 150.F * Timer::Instance().deltaTime();

		if (InputManager::Instance().KeyDown(SDL_SCANCODE_LEFT) ||
			InputManager::Instance().KeyStillDown(SDL_SCANCODE_LEFT))
		{
			player.x -= displacement;
		}
		
		if (InputManager::Instance().KeyDown(SDL_SCANCODE_RIGHT) ||
			InputManager::Instance().KeyStillDown(SDL_SCANCODE_RIGHT))
		{
			player.x += displacement;
		}

		if (InputManager::Instance().KeyDown(SDL_SCANCODE_UP) ||
			InputManager::Instance().KeyStillDown(SDL_SCANCODE_UP))
		{
			player.y -= displacement;
		}

		if (InputManager::Instance().KeyDown(SDL_SCANCODE_DOWN) ||
			InputManager::Instance().KeyStillDown(SDL_SCANCODE_DOWN))
		{
			player.y += displacement;
		}

		if (InputManager::Instance().hasExit() || InputManager::Instance().KeyDown(SDL_SCANCODE_ESCAPE))
		{
			notGameOver = false;
		}

		backround.draw();
		player.draw();
		SDLManager::Instance().renderWindow(m_window);
	}
}