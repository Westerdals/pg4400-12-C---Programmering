#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <SDL.h>

class SDLWindow
{
public:
	SDLWindow() : m_window(NULL), m_renderer(NULL), m_open(false) {}
	~SDLWindow()
	{
		if (m_open)
		{
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			m_open = false;
		}
	}

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_open;
};

#endif