//Spaceship.h
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <string>
#include "Vector3D.h"

class Spaceship
{
public:
    Spaceship();
    Spaceship(const std::string& name, const Vector3D& pos, 
              const Vector3D& vel, int fuel, int damage);
    ~Spaceship();
    void fly();
    void draw();
protected:
    void setProperties(const std::string& name, const Vector3D& pos, 
                       const Vector3D& vel, int fuel, int damage); 
    std::string m_name;
    Vector3D m_position;
    Vector3D m_velocity;
    int m_fuelLevel;
    int m_damage;
};

#endif