/**
 * @file: GameObject.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * 
 * @description: A singleton class to control all Gameplay
 */
#include <memory>
#include "GameObject.h"

/* Starts the game loop and all game logic */
void GameObject::run()
{
	// Declare member variables
	m_gameOver = false;
	m_numPlayers = 0;

	// Print game name
	m_ioMan.printText("Turnventure v1.0");
	m_ioMan.printSeparator();

	// Game loop
	while (!m_gameOver)
	{
		getPlayers(); // Get player data
		playGame();	  // Play the rounds
		rematch();	  // Ask for a rematch
	}
}

/* Asks player for the amount of players */
void GameObject::getPlayers()
{
	// Ask while the given number of players is invalid
	while (!m_numPlayers)
	{
		// Query the user, wait for user input
		m_ioMan.printText("\nEnter number of players: ");
		int num = m_ioMan.getNumber(); // Collect user input

		// Validate the input, make sure it's between the min/max values
		if ((e_minPlayers <= num) && (e_maxPlayers >= num))
		{
			m_numPlayers = num; // Success, update number of players
		}
		else
		{
			// Generate a stringstream of data to output
			std::stringstream message;
			message << "Invalid number of players, min: " << e_minPlayers
					<< " | max: " << e_maxPlayers << std::endl;

			// Print stringstream contents
			m_ioMan.printText(message);
		}
	}

	// Output a border and newlines
	m_ioMan.printSeparator();

	// Collect player data
	getPlayerData();
}

/* Asks player for names and game classes (Wizard, etc.) */
void GameObject::getPlayerData()
{
	std::stringstream messages; // Stream to print concatinated messages
	const PClass* playerClass;	// To hold the selected player class
	int playerClassID;		    // To hold the id of selected class

	// Collect data for each specified player
	for (int i = 0; i < m_numPlayers; ++i)
	{
		// Reset variables for a new player
		messages.str(std::string()); // reset stringstream
		playerClass = 0;
		playerClassID = 0;

		// Generate a message listing the available classes, querying the user to select one
		messages << "\nPlayer Classes:\n\t"
				 << "1 - Wizard\n\t2 - Troll\n\t3 - Assassin\n"
				 << "Pick player #" << (i + 1) << "'s class: ";
		
		// Query the user to select a class as long as the given class is invalid
		while (!playerClassID)
		{
			// Print the message, retrieve user input
			m_ioMan.printText(messages);
			playerClassID = m_ioMan.getNumber();
			
			// Validate the input, check for valid class
			if ((1 > playerClassID) || (3 < playerClassID))
			{
				// Input is invalid, print error and ask again
				m_ioMan.printText("Invalid class ...\n");
				playerClassID = 0;
			}
		}
		
		// Find and set the selected user class
		switch (playerClassID)
		{
		case 1:
			playerClass = &Wizard;
			break;
		case 2:
			playerClass = &Troll;
			break;
		case 3:
		default:
			playerClass = &Assassin;
			break;
		}

		// Clear stringstream's buffer for reusal
		messages.str(std::string());

		// Promt the player for his/her's name
		std::string playerName;
		bool invalidName = true;

		messages << "Write player #" << (i + 1) << "'s name: ";
		
		// Query the player for a name as long as given input is invalid
		while (invalidName)
		{
			// Print the request, retrieve the input
			m_ioMan.printText(messages);
			playerName = m_ioMan.getName();
			
			// Validate the player name
			if (0 >= playerName.size())
			{
				m_ioMan.printText("Name can't be empty ...\n\n");
			}
			else if (3 > playerName.size())
			{
				m_ioMan.printText("Too short name, min 3 characters ...\n\n");
			}
			else if (10 < playerName.size())
			{
				m_ioMan.printText("Too long name, max 10 characters ...\n\n");
			}
			else
			{
				// Name passed all validations; proceed
				invalidName = false;
			}
		}
		
		/* Allocate a new player object with the given values in a Smart Pointer.
		   Adds player to the player list. Must be one operation due to unique_ptr. */
		m_players.push_back(std::unique_ptr<Player>(new Player(*playerClass, playerName)));

		// Print a border with newlines
		m_ioMan.printSeparator();
	}
}

/* Function performing the actual game logic, controls the rounds and gameplay */
void GameObject::playGame()
{
	int round = 1; // Game round counter
	std::stringstream messages; // stringstream for concatenated output

	// Play rounds while there are more than 1 player still alive
	while (m_players.size() > 1)
	{
		messages.str(std::string()); // Reset stringstream

		// Add round nr and player statistics to the stringstream 
		messages << "\nRound " << round << "\n\n----------------\n\nPlayer stats:" << std::endl;

		// Loop through the player's list using an iterator (auto <= std::vector<std::unique_ptr<Player>>::iterator) 
		for (auto it = m_players.begin(); it != m_players.end(); ++it)
		{
			// Add the formatted user statistics to the string stream
			messages << "\t" << (*it)->getName() << ": " << (*it)->getHP() << "/"
					 << (*it)->getClass()->m_healthPoints << " HP" << std::endl; 
		}

		// Print statistics
		messages << std::endl;
		m_ioMan.printText(messages);

		// Retrieve & perform the player actions
		getPlayerActions();
		performPlayerActions();

		// Print a separator, increase the round count
		m_ioMan.printSeparator();
		++round;
	}
}

/* Retrieves the selected user actions from all users, stores result in given vector */
void GameObject::getPlayerActions()
{
	int currentPlayer = 0; // Holds the id of the current player
	std::stringstream messages; // Stringstream for concated output messages
	
	// Print available actions
	m_ioMan.printText("Actions:\n\t1 - Attack\n\t2 - Dodge\n\n");

	// Loop through the player's list using an iterator
	for (auto it = m_players.begin(); it != m_players.end(); ++it)
	{
		// Create a new GameAction, set the action caller to the current user
		GameAction action;
		action.m_caller = (*it).get();

		// Ask the player to pick an action
		messages << (*it)->getName() << ", pick an action: ";

		// Ask for an action while the given action is invalid
		while (e_noAction == action.m_action)
		{
			// Query user, retrieve input (selected action)
			m_ioMan.printText(messages);
			int givenAction = m_ioMan.getNumber();

			// Make sure it's valid
			if ((givenAction < e_attack) || (givenAction > e_dodge))
			{
				m_ioMan.printText("Invalid action ...\n");
			}
			else
			{
				// Success, store the selected action as an action enum
				action.m_action = static_cast<e_Action>(givenAction);
			}
		}

		// Clear stringstream for reuse
		messages.str(std::string());

		// Check if user picked attack
		if (e_attack == action.m_action)
		{

			// User selected "attack". User has to pick a target. Print available targets.
			messages << "Targets:\n";

			// Loop through the player's list using iterators, print available target's names
			for (auto target = m_players.begin(); target != m_players.end(); ++target)
			{
				// Skip if the current target is the user, players can't be suicidal. ;)
				if (target != it)
				{
					// Calculate the player's ID and add it together with the player's name to sstream.
					messages << "\t" << ((target - m_players.begin()) + 1) << " - " << (*target)->getName() << std::endl;
				}
			}

			// Print the available targets to console
			m_ioMan.printText(messages);

			// Variable to hold the selected target's ID in vector
			int targetIndex = -1;

			// Query the user for a valid target while the given action is invalid
			while (0 > targetIndex)
			{
				// Query the user, retrieve input
				m_ioMan.printText("Pick a target: ");
				targetIndex = m_ioMan.getNumber();

				// Verify that the target is valid and not the same target as the user
				if (((1 > targetIndex) || (targetIndex > static_cast<int>(m_players.size()))
					|| ((targetIndex - 1) == currentPlayer)))
				{
					// User selected an invalid target
					m_ioMan.printText("Invalid target ...\n");
					targetIndex = -1;
				}
			}

			// Print a new line to console and store the target in the action object
			m_ioMan.printText("\n");
			action.m_target = m_players[targetIndex - 1].get();
			messages.str(std::string());
		}

		// Check if user picked dodge as an action
		if (e_dodge == action.m_action)
		{
			(*it)->setDodge(); // Set the user's object to "Dodge mode"
		}

		// Add the selected action to the list of the round's actions
		m_roundActions.push_back(action);
		++currentPlayer;
	}
}

/* Performs the actions in the list of the active game round's actions (m_rounActions) */
void GameObject::performPlayerActions()
{
	// Iterate through the list of actions, and execute them
	for (auto action = m_roundActions.begin(); action != m_roundActions.end(); ++action)
	{
		// Check if it's an attack action
		if (action->m_action == e_attack)
		{
			// Pointers for readability
			Player* caller = action->m_caller;
			Player* target = action->m_target;

			// Stringstream to print concatinated messages, add the start of a message.
			std::stringstream message;
			message << caller->getName() << " attacked " << target->getName();
			
			// Check if the target has a positive dodge action
			if (target->dodge())
			{
				// Target successfully dodged, add info to stringstream
				message << " but failed.\n" << target->getName() << " dodged an attack.";
			}
			else
			{
				// Player attacked successfully, add damage to target (the caller's class set damage points)
				target->attack(caller->getClass()->m_damagePoints);

				// Add info to target string
				message << " for " << caller->getClass()->m_damagePoints << " damage.";
			}

			// Add an endline to sstream, print message to output
			message << std::endl;
			m_ioMan.printText(message);
		}
	}

	// Check for an remove dead players
	for (auto it = m_players.begin(); it != m_players.end();)
	{
		// Fetch the player object, erase any dodge state
		Player* player = (*it).get();
		player->setDodge(0);

		// Check if the player is dead
		if (player->isDead())
		{
			// Player is dead, prepare message for output
			std::stringstream message;
			message << (*it)->getName() << " was killed (KIA)!\n";
			m_ioMan.printText(message);

			it->reset(); // Reset the Smart Pointer (free allocated object)
			it = m_players.erase(it); // Remove the player from the list
		}
		else
		{
			// PLayer is alive, increment iterator.
			++it;
		}
	}

	// Finally, reset/empty the action's list. All have been executed.
	m_roundActions.clear();
}

/* Queries the user for a new game or exit */
void GameObject::rematch()
{
	// Print the round results
	if (m_players.size() > 0)
	{
		// Print the name of the winner
		std::stringstream message;
		message << std::endl << m_players[0]->getName() << " WON!";
		m_ioMan.printText(message);
	}
	else
	{
		// Game ended up as a draw between 2..* players
		m_ioMan.printText("\nThe game ended up as a draw!");
	}

	// Game Over! Ask the user for a new game.
	m_ioMan.printText("\nGame Over, again [Y/n]: ");
	char playAgain = m_ioMan.getChar();

	// Check if user asked no
	if ((playAgain == 'N') || (playAgain == 'n'))
	{
		m_gameOver = true; // exit game
	}
	else
	{
		// User wants to play again (anything but "n"), reset player data
		m_numPlayers = 0;
		m_players.clear();

		// Print a pretty border
		m_ioMan.printSeparator();
	}
}

/* Empty private constructor */
GameObject::GameObject()
{
}