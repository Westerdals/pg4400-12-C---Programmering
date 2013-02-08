#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

#include <memory>
#include <vector>
#include <SDL.h>
#include "SDLError.h"
#include "SDLWindow.h"

class SDLManager
{
public:
	~SDLManager();

	static SDLManager& Instance()
	{
		static SDLManager sdl;
		return sdl;
	}

	void init(Uint32 flags = SDL_INIT_VIDEO);

	int createWindow(
		const std::string& title,
		const int& width = 550,
		const int& height = 400,
		const int& x = SDL_WINDOWPOS_CENTERED,
		const int& y = SDL_WINDOWPOS_CENTERED,
		const Uint32& flags = SDL_WINDOW_SHOWN,
		const bool& mainWindow = false
	);

	SDL_Renderer* const getRenderer(const unsigned int& windowIndex = NULL) const;
	const unsigned int* const getMainWindow() const;

	void setMainWindow(const unsigned int& windowIndex);

	void closeWindow(const unsigned int& windowIndex);
	void renderWindow(const unsigned int& windowIndex);
	void render();
private:
	SDLManager();
	SDLManager(const SDLManager&);
	SDLManager& operator=(const SDLManager&);

	std::vector<std::unique_ptr<SDLWindow>> m_windows;
	unsigned int m_mainWindow;
};

#endif