#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct PClass
{
	int m_healthPoints;
	int m_damagePoints;
	short m_dodges;
};

const PClass Wizard = { 150, 25, 2 };
const PClass Troll = { 350, 10, 1 };
const PClass Assassin = { 250, 15, 2 };

class Player
{
public:
	Player(const PClass&, std::string = "");
	
	void setName(const std::string&);
	void setDodge(int = -1);

	const std::string& getName();
	const PClass* getClass();
	int getHP();

	void attack(const int&);
	bool dodge();
	bool isDead();
private:
	std::string m_name;
	int m_healthPoints;
	int m_dodgeCounter;
	const PClass* m_class;
};

#endif