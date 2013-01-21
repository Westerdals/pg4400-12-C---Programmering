// Bombership.h
#ifndef BOMBERSHIP_H
#define BOMBERSHIP_H

#include "Spaceship.h"

class Bombership : public Spaceship
{
public:
	Bombership();
	Bombership(const std::string& name, 
				const Vector3D& pos, 
				const Vector3D& vel, 
				int fuel,
				int damage,
				int numBombs);
	~Bombership();

	void dropBombs();
	void draw();  // Rewritten
private:
	int m_numBombs;
};

#endif