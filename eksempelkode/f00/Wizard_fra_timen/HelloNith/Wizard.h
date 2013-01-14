#ifndef WIZARD_H
#define WIZARD_H

#include <string>

class Wizard
{
public:
	// Public her
	Wizard(int hitpoints = 100);
	~Wizard();
	void setName(std::string name);
	std::string getName();
	void talk();
private:
	// private her
	std::string m_name;
	int m_hitpoints;
};

#endif