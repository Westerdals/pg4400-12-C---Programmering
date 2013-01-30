#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <SDL.h>

static const char GFX_FILE_PATH[] = "Assets/gfx/";

class GameObject
{
public:
	GameObject(const std::string& file, SDL_Renderer* renderer);
	~GameObject();

	SDL_Texture* const getDrawable() const;

	SDL_Rect m_coords;
private:
	SDL_Texture* m_drawable;
};

#endif