/**
 * @file: GameObject.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * 
 * @description: A singleton class to control all Gameplay
 */

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>

#include "IOManager.h"
#include "Player.h"

class GameObject
{
public:
	/* Meyer's singleton style instance call */
	static GameObject& Instance()
	{
		static GameObject g;
		return g;
	}

	/* Starts the game loop and all game logic */
	void run();

	/* Constants to adjust the amount of players */
	enum e_playerAmount {
		e_minPlayers = 2,
		e_maxPlayers = 6
	};
private:
	GameObject();							  // Hidden constructor
	GameObject(const GameObject&);			  // Hidden copy constructor
	GameObject& operator=(const GameObject&); // Hidden assign operator

	// Object for controlling input & output
	IOManager m_ioMan;

	// List of players. NOTE: stored in unique_ptr
	std::vector<std::unique_ptr<Player>> m_players;

	// Whether or not the game is over
	bool m_gameOver;
};

#endif