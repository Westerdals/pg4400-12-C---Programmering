#include <sstream>
#include "SDLManager.h"

SDLManager::SDLManager(Uint32 flags)
{
	if (SDL_Init(flags))
	{
		std::stringstream msg;
		msg << "Could not initialize SDL: " << SDL_GetError();

		throw SDLError(msg.str());
	}
}

SDLManager::~SDLManager()
{
	SDL_Quit();
}

int SDLManager::createWindow(const std::string& title,
					const int& width, const int& height,
					const int& x, const int& y,
					const Uint32& flags)
{
	SDLWindow window;

	// Create the window where we will draw.
	window.m_window = SDL_CreateWindow(
		title.c_str(), x, y, width, height, flags
	);
	
	if (window.m_window == NULL)
	{
		std::stringstream msg;
		msg << "Could not create window; \"" << title
			<< "\", details: " << SDL_GetError();

		throw SDLError(msg.str());
	}

	// We must call SDL_CreateRenderer in order for draw calls to affect this window.
	window.m_renderer = SDL_CreateRenderer(window.m_window, -1, SDL_RENDERER_ACCELERATED);

	if (window.m_renderer == NULL)
	{
		std::stringstream msg;
		SDL_DestroyWindow(window.m_window);

		msg << "Could not create window renderer; \"" << title
			<< "\", details: " << SDL_GetError();

		throw SDLError(msg.str());
	}

	// Select the color for drawing. It is set to black here.
	SDL_SetRenderDrawColor(window.m_renderer, 0, 0, 0, 255);

	// Clear the entire screen to our selected color.
	SDL_RenderClear(window.m_renderer);

	// Up until now everything was drawn behind the scenes.
    // This will show the new, red contents of the window.
   // SDL_RenderPresent(window.m_renderer);

	int index = m_windows.size();
	window.m_open = true;
	// THIS DOESN'T WORK! REQUIRES DYNAMIC ALLOCATION! 
	m_windows.push_back(window);

	renderWindow(index);

	return index;
}

void SDLManager::addObject(const GameObject& obj, const unsigned int& windowIndex)
{
	if ((m_windows.size() > windowIndex) && m_windows[windowIndex].m_open)
	{
		SDL_RenderCopy(m_windows[windowIndex].m_renderer, obj.getDrawable(), &obj.m_coords, NULL);
	}
}

SDL_Renderer* const SDLManager::getRenderer(const unsigned int& windowIndex) const
{
	if (m_windows.size() > windowIndex)
	{
		return m_windows[windowIndex].m_renderer;
	}

	return NULL;
}

void SDLManager::closeWindow(const unsigned int& windowIndex)
{
	if (m_windows.size() > windowIndex)
	{
		m_windows[windowIndex].m_open = false;
		SDL_DestroyWindow(m_windows[windowIndex].m_window);
	}
}

void SDLManager::renderWindow(const unsigned int& windowIndex)
{
	if ((m_windows.size() > windowIndex) && m_windows[windowIndex].m_open)
	{
		SDL_RenderClear(m_windows[windowIndex].m_renderer);
		SDL_RenderPresent(m_windows[windowIndex].m_renderer);
	}
}

void SDLManager::render()
{
	for (unsigned int i = 0; i < m_windows.size(); ++i)
	{
		renderWindow(i);
	}
}