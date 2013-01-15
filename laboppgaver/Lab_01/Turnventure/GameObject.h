#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>

#include "IOManager.h"
#include "Player.h"

class GameObject
{
public:
	static GameObject& Instance()
	{
		static GameObject g;
		return g;
	}

	void run();

	enum {
		e_minPlayers = 2,
		e_maxPlayers = 6
	};
private:
	GameObject();								// Hidden constructor
	GameObject(const GameObject&);				// Hidden copy constructor
	GameObject& operator=(const GameObject&);	// Hidden assign operator

	std::vector<std::unique_ptr<Player>> m_players;
	IOManager m_ioMan;
};

#endif