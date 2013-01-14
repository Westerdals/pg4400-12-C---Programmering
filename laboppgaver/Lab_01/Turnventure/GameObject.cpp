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

			if ((MIN_NUM_PLAYERS <= num) && (MAX_NUM_PLAYERS >= num))
			{
				numPlayers = num;
			}
			else
			{
				std::stringstream out;
				out << "Invalid number of players, min: " << MIN_NUM_PLAYERS
					<< " | max: " << MAX_NUM_PLAYERS << std::endl;

				m_ioMan.printText(out);
			}
		}

		m_ioMan.printSeparator();

		for (int i = 0; i < numPlayers; ++i)
		{
			std::stringstream out;
			std::string name;
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
			
			m_ioMan.printText(out);
			// TODO: Should add name validation!
			m_players.push_back(std::unique_ptr<Player>(new Player(*playerClass, m_ioMan.getName())));
			m_ioMan.printSeparator();
		}

		/*while (m_players.size() > 1)
		{

		}*/

		gameOver = true;
	}
}