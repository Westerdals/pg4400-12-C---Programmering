#ifndef ORC_H
#define ORC_H

#include <string>

using std::string;

class Orc
{
public:
	Orc();
	Orc(int health, string name);
	int getHealth();
	string getName();
	virtual string getFullDescription();
	void setHealth(int health);
	void setName(string name);

protected:
	string m_name;
	int m_hp;
};
#endif