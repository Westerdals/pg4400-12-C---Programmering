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
#include "GameAction.h"

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

	/* Asks player for the amount of players */
	void getPlayers();

	/* Asks player for names and game classes (Wizard, etc.) */
	void getPlayerData();

	/* Function performing the actual game logic, controls the rounds and gameplay */
	void playGame();

	/* Retrieves the selected user actions from all users, stores result in given vector */
	void getPlayerActions();

	/* Performs the actions in the list of the active game round's actions (m_roundActions) */
	void performPlayerActions();

	/* Queries the user for a new game or exit */
	void rematch();

	// Object for controlling input & output
	IOManager m_ioMan;

	// List of players. NOTE: stored in unique_ptr
	std::vector<std::unique_ptr<Player>> m_players;

	bool m_gameOver;						// Whether or not the game is over
	int m_numPlayers;						// Number of players
	std::vector<GameAction> m_roundActions; // List of one round's actions
};

#endif