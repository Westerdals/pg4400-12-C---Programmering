#include "GameManager.h"
#include "GameObject.h"
#include "InputManager.h"

GameManager::GameManager()
{
	m_window = m_sdl.createWindow("My Awesome SDL 2.0 Game");
}

void GameManager::play()
{
	bool notGameOver = true;
	GameObject background("sdl2.bmp", m_sdl.getRenderer(m_window));
	GameObject player("sdl_bro.bmp", m_sdl.getRenderer(m_window));

	while (notGameOver)
	{
		InputManager::Instance().Update();

		if (InputManager::Instance().KeyDown(SDL_SCANCODE_ESCAPE))
		{
			notGameOver = false;
		}

		if (InputManager::Instance().KeyDown(SDL_SCANCODE_LEFT))
		{
			player.m_coords.x -= 5;
		}
		
		if (InputManager::Instance().KeyDown(SDL_SCANCODE_RIGHT))
		{
			player.m_coords.x += 5;
		}

		if (InputManager::Instance().KeyDown(SDL_SCANCODE_UP))
		{
			player.m_coords.y -= 5;
		}

		if (InputManager::Instance().KeyDown(SDL_SCANCODE_DOWN))
		{
			player.m_coords.y += 5;
		}

		m_sdl.addObject(background, m_window);
		m_sdl.addObject(player, m_window);
		m_sdl.renderWindow(m_window);

		if (SDL_HasEvent(SDL_QUIT))
		{
			notGameOver = false;
		}
	}
}