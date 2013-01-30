#include <sstream>
#include "SDL\SDLError.h"
#include "GameObject.h"

GameObject::GameObject(const std::string& file, SDL_Renderer* renderer)
{
	std::stringstream filePath;
	filePath << GFX_FILE_PATH << file;

	m_drawable = NULL;
	SDL_Surface* surface = SDL_LoadBMP(filePath.str().c_str());

	if (surface == NULL)
	{
		std::stringstream msg;
		msg << "Failed to load bitmap: " << filePath.str()
			<< " | details: " << SDL_GetError(); 

		throw SDLError(msg.str());
	}

	m_drawable = SDL_CreateTextureFromSurface(renderer, surface);
	m_coords.h = surface->h;
	m_coords.w = surface->w;
	m_coords.x = 0;
	m_coords.y = 0;

	SDL_FreeSurface(surface);

	if (m_drawable == NULL)
	{
		throw SDLError();
	}
}

GameObject::~GameObject()
{
	SDL_DestroyTexture(m_drawable);
}

SDL_Texture* const GameObject::getDrawable() const
{
	return m_drawable;
}