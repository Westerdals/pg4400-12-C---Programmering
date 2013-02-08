#ifndef SDL_BMP_H
#define SDL_BMP_H

#include <string>
#include <SDL.h>

class SDLBmp
{
public:
	SDLBmp(const std::string& file);
	~SDLBmp();

	void draw();

	float x;
	float y;
private:
	SDL_Texture* m_texture;
	SDL_Renderer* m_renderer;
	SDL_Rect m_rect;
};

#endif