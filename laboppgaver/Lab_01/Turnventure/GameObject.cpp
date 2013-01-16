/**
 * @file: GameObject.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * 
 * @description: A singleton class to control all Gameplay
 */
#include <memory>
#include "GameObject.h"
#include "GameAction.h"

/* Starts the game loop and all game logic */
void GameObject::run()
{
	m_gameOver = false;

	// Print game name
	m_ioMan.printText("Turnventure v1.0");
	m_ioMan.printSeparator();

	//while (!m_gameOver)
	//{
		// getPlayers();
		// playGame();
		// rematch();
	//}

	// get

	while (!m_gameOver)
	{
		int numPlayers = 0;
		int round = 1;

		while (!numPlayers)
		{
			m_ioMan.printText("\nEnter number of players: ");
			int num = m_ioMan.getNumber();

			if ((e_minPlayers <= num) && (e_maxPlayers >= num))
			{
				numPlayers = num;
			}
			else
			{
				std::stringstream out;
				out << "Invalid number of players, min: " << e_minPlayers
					<< " | max: " << e_maxPlayers << std::endl;

				m_ioMan.printText(out);
			}
		}
		
		m_ioMan.printSeparator();

		for (int i = 0; i < numPlayers; ++i)
		{
			std::stringstream out;
			const PClass* playerClass;
			int playerClassID = 0;
			
			out << "\nPlayer Classes:\n\t"
				<< "1 - Wizard\n\t2 - Troll\n\t3 - Assassin\n"
				<< "Pick player #" << (i + 1) << "'s class: ";
			
			while (!playerClassID)
			{
				m_ioMan.printText(out);
				playerClassID = m_ioMan.getNumber();
				
				if ((1 > playerClassID) || (3 < playerClassID))
				{
					m_ioMan.printText("Invalid class ...\n");
					playerClassID = 0;
				}
			}
			
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

			out.str(std::string()); // Clear stringstream's buffer
			out << "Write player #" << (i + 1) << "'s name: ";
			std::string playerName;
			bool invalidName = true;
			
			while (invalidName)
			{
				m_ioMan.printText(out);

				playerName = m_ioMan.getName();
				
				if (0 >= playerName.size())
				{
					m_ioMan.printText("Name can't be empty ...\n\n");
				}
				else if (10 < playerName.size())
				{
					m_ioMan.printText("Too long name, max 10 characters ...\n\n");
				}
				else
				{
					invalidName = false;
				}
			}
			
			m_players.push_back(std::unique_ptr<Player>(new Player(*playerClass, playerName)));
			m_ioMan.printSeparator();
		}

		while (m_players.size() > 1)
		{
			std::stringstream out;
			out << "\nRound " << round << "\n\n----------------\n\nPlayer stats:" << std::endl;

			for (auto it = m_players.begin(); it != m_players.end(); ++it)
			{
				out << "\t" << (*it)->getName() << ": " << (*it)->getHP() << "/"
					<< (*it)->getClass()->m_healthPoints << " HP" << std::endl; 
			}

			out << std::endl << "Actions:\n\t1 - Attack\n\t2 - Dodge\n\n";
			m_ioMan.printText(out);
			out.str(std::string()); // Clear stringstream

			int currentPlayer = 0;
			std::vector<GameAction> roundActions;

			for (auto it = m_players.begin(); it != m_players.end(); ++it)
			{
				GameAction action;
				action.m_caller = (*it).get();
				action.m_action = e_noAction;

				out << (*it)->getName() << ", pick an action: ";
				m_ioMan.printText(out);
				out.str(std::string()); // Clear stringstream

				while (e_noAction == action.m_action)
				{
					int givenAction = m_ioMan.getNumber();

					if ((givenAction < e_attack) || (givenAction > e_dodge))
					{
						m_ioMan.printText("Invalid action ...\n");
					}
					else
					{
						action.m_action = static_cast<e_Action>(givenAction);
					}
				}

				if (e_attack == action.m_action)
				{
					std::stringstream targets;
					targets << "Targets:\n";

					for (auto target = m_players.begin(); target != m_players.end(); ++target)
					{
						if (target != it)
						{
							targets << "\t" << ((target - m_players.begin()) + 1) << " - " << (*target)->getName() << std::endl;
						}
					}

					m_ioMan.printText(targets);

					int targetIndex = -1;

					while (0 > targetIndex)
					{
						m_ioMan.printText("Pick a target: ");
						targetIndex = m_ioMan.getNumber();

						if (((1 > targetIndex) || (targetIndex > static_cast<int>(m_players.size())) || ((targetIndex - 1) == currentPlayer)))
						{
							m_ioMan.printText("Invalid target ...\n");
							targetIndex = -1;
						}
					}
					m_ioMan.printText("\n");
					action.m_target = m_players[targetIndex - 1].get();
				}

				if (e_dodge == action.m_action)
				{
					(*it)->setDodge();
				}

				roundActions.push_back(action);
				++currentPlayer;
			}

			for (auto action = roundActions.begin(); action != roundActions.end(); ++action)
			{
				if (action->m_action == e_attack)
				{
					std::stringstream message;
					message << action->m_caller->getName() << " attacked " << action->m_target->getName();
					
					if (action->m_target->dodge())
					{
						message << " but failed.\n";
						message << action->m_target->getName() << " dodged an attack.";
					}
					else
					{
						action->m_target->attack(action->m_caller->getClass()->m_damagePoints);
						message << " for " << action->m_caller->getClass()->m_damagePoints << " damage.";
					}

					message << std::endl;
					m_ioMan.printText(message);
				}
			}

			// Remove dead players
			for (auto it = m_players.begin(); it != m_players.end();)
			{
				(*it)->setDodge(0);
				if ((*it)->isDead())
				{
					std::stringstream message;
					message << (*it)->getName() << " was killed (KIA)!\n";

					it->reset();
					it = m_players.erase(it);
				}
				else
				{
					++it;
				}
			}

			m_ioMan.printSeparator();
			++round;
		}

		if (m_players.size() > 0)
		{
			std::stringstream message;
			message << m_players[0]->getName() << " WON!";
			m_ioMan.printText(message);
		}
		else
		{
			m_ioMan.printText("The game ended up as a draw!");
		}

		m_ioMan.printText("\n\nGame Over, again [Y/n]: ");
		char playAgain = m_ioMan.getChar();

		if ((playAgain == 'N') || (playAgain == 'n'))
		{
			m_gameOver = true;
		}
		else
		{
			m_ioMan.printSeparator();
		}
	}
}

/* Empty private constructor */
GameObject::GameObject()
{
}