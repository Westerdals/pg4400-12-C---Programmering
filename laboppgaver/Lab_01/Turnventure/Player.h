#ifndef PLAYER_H
#define PLAYER_H

#include <string>

struct PClass
{
	int m_healthPoints;
	int m_damagePoints;
	short m_dodges;
};

const PClass Wizard = { 100, 25, 2 };
const PClass Troll = { 500, 10, 1 };
const PClass Assassin = { 250, 15, 2 };

class Player
{
public:
	Player(const PClass&, std::string = "");
	
	void setName(const std::string&);

	const std::string& getName();
	const PClass* getClass();
	int getHP();

	void attack(const int&);
private:
	std::string m_name;
	int m_healthPoints;
	const PClass* m_class;
};

#endif