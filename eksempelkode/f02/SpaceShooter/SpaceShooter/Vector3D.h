// vector3D.h
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

class Vector3D
{
public:
	Vector3D();
	Vector3D(float fX, float fY, float fZ);
	Vector3D(const float afCoords[3]);
	
	float Length() const;
	void Normalize();

	bool operator==(const Vector3D& oV) const;  // NEW "Equals".
	bool operator!=(const Vector3D& oV) const;  // NEW "!Equals".
	Vector3D operator+(const Vector3D& oV) const;  // NEW "Add".
	Vector3D operator-(const Vector3D& oV) const;  // NEW "Subtract".
	Vector3D operator*(float fScalar) const;  // NEW "Multiply", version 1: vector * scalar. 
	float operator*(const Vector3D& oV) const;  // NEW "Dot".

	operator const float*();  // NEW "RefToFloatArray".
	void CopyToFloatArray(float afCopy[3]) const;

private:
	friend Vector3D operator*(float fScalar, const Vector3D& oV);  // NEW Multiply, version 2: scalar * vector.
	friend std::istream& operator>>(std::istream& oInStream, Vector3D& oV);  // NEW "InputFromCin".
	friend std::ostream& operator<<(std::ostream& oOutStream, const Vector3D& oV);  // NEW "OutputToCout".

	inline void setCoordinates(float fX, float fY, float fZ) { m_fX = fX; m_fY = fY; m_fZ = fZ; }

	float m_fX;
	float m_fY;
	float m_fZ;
};

#endif