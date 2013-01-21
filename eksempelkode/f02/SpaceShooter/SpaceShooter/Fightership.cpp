#include "Fightership.h"

Fightership::Fightership(const std::string& name, 
						 const Vector3D& pos, 
						 const Vector3D& vel, 
						 int fuel,
						 int damage,
						 int numMissiles)
: Spaceship(name, pos, vel, fuel, damage), m_numMissiles(numMissiles)
{
	std::cout << "Fightership() constructor w/params called." << std::endl;
	//m_numMissiles = numMissiles;
}

Fightership::~Fightership()
{
	std::cout << "Fightership() destructor called." << std::endl;
}

void Fightership::fireLaserGun()
{
	std::cout << "Firing laser gun." << std::endl;
}

void Fightership::fireMissile()
{
	if(m_numMissiles > 0)
	{
		std::cout << "Firing missile." << std::endl;
		m_numMissiles--;
	}
	else
	{
		std::cout << "Out of missiles." << std::endl;
	}
}

void Fightership::draw()
{
	Spaceship::draw();
	std::cout << "Missiles = " << m_numMissiles << std::endl << std::endl;
}