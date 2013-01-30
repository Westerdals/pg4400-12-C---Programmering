#include <SDL.h>
#include "SDLError.h"

SDLError::SDLError() : exception()
{
	m_message = SDL_GetError();
}

SDLError::SDLError(const std::string& msg) : exception()
{
	m_message = msg;
}

SDLError::~SDLError() throw()
{
}

const char* SDLError::what() const throw()
{
	return m_message.c_str();
}