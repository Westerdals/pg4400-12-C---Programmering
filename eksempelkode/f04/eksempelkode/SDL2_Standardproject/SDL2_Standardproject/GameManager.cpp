#include <iostream>
#include "GameManager.h"
#include "GameObject.h"

GameManager::GameManager()
{
	// Initialize stuff here
}

void GameManager::play()
{
	unsigned int mainWindow = m_sdl.createWindow("My Awesome SDL 2.0 Game");
	GameObject background("sdl2.bmp", m_sdl.getRenderer(mainWindow));

	m_sdl.addObject(background, mainWindow);
	m_sdl.renderWindow(mainWindow);

	system("Pause");
}