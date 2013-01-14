#include <iostream>
#include "Wizard.h"

Wizard::Wizard(int hitpoints)
{
	m_name = "Gandalf";

	if (hitpoints > 0)
		m_hitpoints = hitpoints;
	else
		m_hitpoints = 100;
	
	std::cout << "Wizard created!" << std::endl;
}

Wizard::~Wizard()
{
	std::cout << "Wizard going out of memory" << std::endl;
}

void Wizard::setName(std::string name)
{
	m_name = name;
}

std::string Wizard::getName()
{
	return m_name;
}

void Wizard::talk()
{
	std::cout << "You shall not pass!" << std::endl;
}