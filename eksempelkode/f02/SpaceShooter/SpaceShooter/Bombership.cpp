#include "Bombership.h"

Bombership::Bombership()
{
	std::cout << "Bombership() noparam-constructor called." << std::endl;
	m_numBombs = 5;
}

Bombership::Bombership(const std::string& name, const Vector3D& pos, const Vector3D& vel, 
					   int fuel, int damage, int numBombs)
// NOTE: Following line COMMENTED OUT to show WRONG USAGE, and what happens then (check the console when you run the program for output).
//: Spaceship(name, pos, vel, fuel, damage)
{
	std::cout << "Bombership() constructor w/params called." << std::endl;
	m_numBombs = numBombs;
}

Bombership::~Bombership()
{
	std::cout << "Bombership() destructor called." << std::endl;
}

void Bombership::dropBombs()
{
	if(m_numBombs-- > 0)
	{
		std::cout << "Dropping bombs." << std::endl;
	}
	else
	{
		std::cout << "Out of bombs." << std::endl;
	}
}