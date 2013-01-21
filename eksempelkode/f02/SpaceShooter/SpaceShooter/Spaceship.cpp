// Spaceship.cpp
#include "Spaceship.h"

Spaceship::Spaceship()
{
	std::cout << "Spaceship() noparam-constructor called." << std::endl;
	setProperties("Default Name", Vector3D(0.0f, 0.0f,0.0f), Vector3D(0.0f, 0.0f,0.0f), 100, 0);
	//m_name = "Default Name";
	//m_position = Vector3D(0.0f,0.0f,0.0f);
	//m_velocity = Vector3D(0.0f,0.0f,0.0f);
	//m_fuelLevel = 100;
	//m_damage = 0;
}

Spaceship::Spaceship(const std::string& name, const Vector3D& pos, 
					 const Vector3D& vel, int fuel, int damage)
{
	std::cout << "Spaceship() constructor w/params called." << std::endl;
	setProperties(name, pos, vel, fuel, damage);
	//m_name = name;
	//m_position = pos;
	//m_velocity = vel;
	//m_fuelLevel = fuel;
	//m_damage = damage;
}

Spaceship::~Spaceship()
{
	std::cout << "Spaceship() destructor called." << std::endl;
}
	
void Spaceship::fly()
{
	std::cout << "Spaceship flying..." << std::endl;
}

void Spaceship::draw()
{
	std::cout << "=================" << std::endl;
	std::cout << "Name      = " << m_name << std::endl;
	std::cout << "Position  = " << m_position << std::endl;
	std::cout << "Velocity  = " << m_velocity << std::endl;
	std::cout << "FuelLevel = " << m_fuelLevel << std::endl;
	std::cout << "Damage    = " << m_damage << std::endl;
}

void Spaceship::setProperties(const std::string& name, const Vector3D& pos , 
							  const Vector3D& vel, int fuel, int damage)
{
	m_name = name;
	m_position = pos;
	m_velocity = vel;
	m_fuelLevel = fuel;
	m_damage = damage;
}