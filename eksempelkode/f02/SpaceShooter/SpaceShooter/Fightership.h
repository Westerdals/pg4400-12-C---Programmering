// Fightership.h
#ifndef FIGHTERSHIP_H
#define FIGHTERSHIP_H

#include "Spaceship.h"

class Fightership : public Spaceship {
public:
	Fightership();
	Fightership(const std::string& name, 
				 const Vector3D& pos, 
				 const Vector3D& vel, 
				 int fuel,
				 int damage,
				 int numMissiles);
	~Fightership();

	void fireLaserGun();
	void fireMissile();
	void draw();  // Rewritten
private:
	int m_numMissiles;
};

#endif