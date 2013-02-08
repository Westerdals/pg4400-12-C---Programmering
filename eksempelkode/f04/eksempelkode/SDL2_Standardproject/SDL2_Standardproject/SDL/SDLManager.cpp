#include <sstream>
#include "SDLManager.h"

SDLManager::SDLManager()
{
	m_mainWindow = NULL;
}

void SDLManager::init(Uint32 flags)
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
					const Uint32& flags,
					const bool& mainWindow)
{
	// Create the window where we will draw.
	SDL_Window* window = SDL_CreateWindow(
		title.c_str(), x, y, width, height, flags
	);
	
	// Check for errors
	if (window == NULL)
	{
		std::stringstream msg;
		msg << "Could not create window; \"" << title
			<< "\", details: " << SDL_GetError();

		throw SDLError(msg.str());
	}

	// We must call SDL_CreateRenderer in order for draw calls to affect this window.
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		std::stringstream msg;
		SDL_DestroyWindow(window);

		msg << "Could not create window renderer; \"" << title
			<< "\", details: " << SDL_GetError();

		throw SDLError(msg.str());
	}

	// Select the color for drawing. It is set to black here.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Clear the entire screen to our selected color.
	SDL_RenderClear(renderer);

	// Up until now everything was drawn behind the scenes.
    // This will show the new, red contents of the window.
   // SDL_RenderPresent(window.m_renderer);

	int index = m_windows.size();
	m_windows.push_back(std::unique_ptr<SDLWindow>(new SDLWindow(window, renderer, true)));//window);

	// Set main window if not already set or asked to
	if (mainWindow || (m_mainWindow == NULL))
	{
		m_mainWindow = index;
	}

	renderWindow(index); // Render window immediately
	return index;
}

void SDLManager::setMainWindow(const unsigned int& windowIndex)
{
	if ((m_windows.size() > windowIndex) && m_windows[windowIndex]->m_open)
	{
		m_mainWindow = windowIndex;
	}
}

SDL_Renderer* const SDLManager::getRenderer(const unsigned int& windowIndex) const
{
	if (m_windows.size() > windowIndex)
	{
		return m_windows[windowIndex]->m_renderer;
	}

	return NULL;
}

const unsigned int* const SDLManager::getMainWindow() const
{
	return &m_mainWindow;
}

void SDLManager::closeWindow(const unsigned int& windowIndex)
{
	if (m_windows.size() > windowIndex)
	{
		m_windows[windowIndex]->m_open = false;
		SDL_DestroyRenderer(m_windows[windowIndex]->m_renderer);
		SDL_DestroyWindow(m_windows[windowIndex]->m_window);
	}
}

void SDLManager::renderWindow(const unsigned int& windowIndex)
{
	if ((m_windows.size() > windowIndex) && m_windows[windowIndex]->m_open)
	{
		SDL_RenderPresent(m_windows[windowIndex]->m_renderer);
	}
}

void SDLManager::render()
{
	for (unsigned int i = 0; i < m_windows.size(); ++i)
	{
		renderWindow(i);
	}
}