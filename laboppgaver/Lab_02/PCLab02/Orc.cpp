#include <sstream>
#include "Orc.h"

using std::stringstream;
using std::endl;

Orc::Orc()
{
	setHealth(100);
	setName("Orc Grunt");
}

Orc::Orc(int health, string name)
{
	setHealth(health);
	setName(name);
}

int Orc::getHealth()
{
	return m_hp;
}

string Orc::getName()
{
	return m_name;
}

string Orc::getFullDescription()
{
	stringstream result;
	result << "Name: " << getName() << endl << "Health: " << getHealth() << endl << endl;
	return result.str();
}

void Orc::setHealth(int health)
{
	m_hp = health;
}

void Orc::setName(string name)
{
	m_name = name;
}