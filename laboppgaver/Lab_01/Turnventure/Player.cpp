#include "Player.h"

Player::Player(const PClass& c, std::string name)
{
	m_class = &c;
	m_healthPoints = m_class->m_healthPoints;
	setName(name);
}

void Player::setName(const std::string& name)
{
	m_name = name;
}

const std::string& Player::getName()
{
	return m_name;
}

const PClass* Player::getClass()
{
	return m_class;
}

int Player::getHP()
{
	return m_healthPoints;
}

void Player::attack(const int& damage)
{
	// Prevent negative damage (healing)
	if (damage < 0)
	{
		if (damage > m_healthPoints)
		{
			m_healthPoints = 0;
		}
		else
		{
			m_healthPoints -= damage;
		}
	}
}