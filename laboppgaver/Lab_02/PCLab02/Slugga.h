#ifndef SLUGGA_H
#define SLUGGA_H
#include "Orc.h"

class Slugga : public Orc
{
public:
	Slugga();
	Slugga(int health, std::string name, int damage, int kills);
	int getDamage();
	int getKillCount();
	std::string getFullDescription();
	void setDamage(int damage);
	void setKills(int kills);

private: 
	int m_damage;
	int m_kills;
};


#endif