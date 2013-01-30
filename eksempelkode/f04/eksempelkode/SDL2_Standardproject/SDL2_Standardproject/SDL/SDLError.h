#ifndef SDL_ERROR_H
#define SDL_ERROR_H

#include <exception>
#include <string>

class SDLError : public std::exception
{
public:
	SDLError();
	SDLError(const std::string&);
	virtual ~SDLError() throw();
	virtual const char* what() const throw();
private:
	std::string m_message;
};

#endif