#include <memory>
#include "GameObject.h"

GameObject::GameObject()
{
}

void GameObject::run()
{
	bool gameOver = false;

	m_ioMan.printText("Turnventure v1.0");
	m_ioMan.printSeparator();

	while (!gameOver)
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
			break; // Temporary!
		}

		gameOver = true;
	}
}