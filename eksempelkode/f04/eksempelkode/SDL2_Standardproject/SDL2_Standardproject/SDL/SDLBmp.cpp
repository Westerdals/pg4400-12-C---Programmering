#include <sstream>
#include "SDLBmp.h"
#include "SDLManager.h"

SDLBmp::SDLBmp(const std::string& file)
{
	m_texture = NULL;
	SDL_Surface* surface = SDL_LoadBMP(file.c_str());

	if (surface == NULL)
	{
		std::stringstream msg;
		msg << "Failed to load bitmap: " << file
			<< " | details: " << SDL_GetError(); 

		throw SDLError(msg.str());
	}

	m_renderer = SDLManager::Instance().getRenderer(*(SDLManager::Instance().getMainWindow()));
	m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	m_rect.h = surface->h;
	m_rect.w = surface->w;
	m_rect.x = 0;
	m_rect.y = 0;
	x = y = 0.0F;

	SDL_FreeSurface(surface);

	if (m_texture == NULL)
	{
		throw SDLError();
	}
}

SDLBmp::~SDLBmp()
{
	SDL_DestroyTexture(m_texture);
}

void SDLBmp::draw()
{
	m_rect.x = static_cast<int>(x);
	m_rect.y = static_cast<int>(y);

	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_rect);
}