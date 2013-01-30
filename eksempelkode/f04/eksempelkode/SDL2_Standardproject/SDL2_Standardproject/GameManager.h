#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "SDL/SDLManager.h"

class GameManager
{
public:
	/* Meyer's singleton style instance call */
	static GameManager& Instance()
	{
		static GameManager g;
		return g;
	}

	void play();
private:
	GameManager();								// Hidden constructor
	GameManager(const GameManager&);			// Hidden copy constructor
	GameManager& operator=(const GameManager&); // Hidden assign operator

	SDLManager m_sdl;
};

#endif