#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

#include <memory>
#include <vector>
#include <SDL.h>
#include "SDLError.h"
#include "SDLWindow.h"
#include "../GameObject.h"

class SDLManager
{
public:
	SDLManager(Uint32 flags = SDL_INIT_VIDEO);
	~SDLManager();

	int createWindow(
		const std::string& title,
		const int& width = 550,
		const int& height = 400,
		const int& x = SDL_WINDOWPOS_CENTERED,
		const int& y = SDL_WINDOWPOS_CENTERED,
		const Uint32& flags = SDL_WINDOW_SHOWN
	);

	SDL_Renderer* const getRenderer(const unsigned int& windowIndex) const;

	void addObject(const GameObject& obj, const unsigned int& windowIndex);
	void closeWindow(const unsigned int& windowIndex);
	void renderWindow(const unsigned int& windowIndex);
	void render();
private:
	std::vector<std::unique_ptr<SDLWindow>> m_windows;
};

#endif