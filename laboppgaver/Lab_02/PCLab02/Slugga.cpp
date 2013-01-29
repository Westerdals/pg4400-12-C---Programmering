#include <sstream>
#include "Slugga.h"

#include <iostream>
#include <limits>

using std::endl;

Slugga::Slugga()
	:Orc(10, "Slugga Grunt")
{
	setDamage(10);
	setKills(0);
}

Slugga::Slugga(int health, std::string name, int damage, int kills)
	:Orc(health, name)
{
	setDamage(damage);
	setKills(kills);
}

int Slugga::getDamage()
{
	return m_damage;
}

int Slugga::getKillCount()
{
	return m_kills;
}

string Slugga::getFullDescription()
{
	std::stringstream result;
	result << "Name: " << getName() << endl << "Health: " << 
		getHealth() << endl << "Damage: " << getDamage() << endl << 
		"Kills: " << getKillCount() << endl << endl;
	return result.str();
}

void Slugga::setDamage(int damage)
{
	m_damage = damage;
}

void Slugga::setKills(int kills)
{
	m_kills = kills;
}