#include "GameObject.h"

GameObject::GameObject()
{
}

void GameObject::run()
{
	bool gameOver = false;

	m_ioMan.printText("Turnventure v1.0\n----------------\n\n");

	while (!gameOver)
	{
		int numPlayers = 0;

		while (!numPlayers)
		{
			m_ioMan.printText("Enter number of players: ");
			int num = m_ioMan.getNumber();

			if ((MIN_NUM_PLAYERS <= num) && (MAX_NUM_PLAYERS >= num))
			{
				numPlayers = num;
			}
			else
			{
				std::stringstream out;
				out << "Invalid number of players, min: " << MIN_NUM_PLAYERS
					<< " | max: " << MAX_NUM_PLAYERS << std::endl << std::endl;

				m_ioMan.printText(out);
			}
		}

		gameOver = true;
	}
}