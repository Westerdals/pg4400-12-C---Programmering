// vector3D.cpp
#include <cmath>  // Lets us use math functions: sqrtf(...), pow(...).
#include "Vector3D.h"

Vector3D::Vector3D()
{
	setCoordinates(0.0, 0.0, 0.0);
}

Vector3D::Vector3D(float fX, 
					 float fY, 
					 float fZ)
{
	setCoordinates(fX, fY, fZ);
}

Vector3D::Vector3D(const float afCoords[3])
{
	setCoordinates(afCoords[0], afCoords[1], afCoords[2]);
}

std::istream& operator>>(std::istream& oInStream, Vector3D& oV)
{
	std::cout << "Enter x: ";
	oInStream >> oV.m_fX;
	std::cout << "Enter y: ";
	oInStream >> oV.m_fY;
	std::cout << "Enter z: ";
	oInStream >> oV.m_fZ;
	return oInStream;
}

// Prints on form: "(x, y, z)"
std::ostream& operator<<(std::ostream& oOutStream, const Vector3D& oV)
{
	oOutStream << "(" << oV.m_fX << ", " << oV.m_fY << ", " << oV.m_fZ << ")";
	return oOutStream;
}

float Vector3D::Length() const
{
	//return sqrtf(pow(m_fX, 2) + pow(m_fY, 2) + pow(m_fZ, 2));
	return sqrtf((m_fX * m_fX) + (m_fY * m_fY) + (m_fZ * m_fZ));
}

bool Vector3D::operator==(const Vector3D& oV) const
{
	return ((oV.m_fX == m_fX) && (oV.m_fY == m_fY) && (oV.m_fZ == m_fZ));
}

bool Vector3D::operator!=(const Vector3D& oV) const
{
	//return ((oV.m_fX != m_fX) || (oV.m_fY != m_fY) || (oV.m_fZ != m_fZ));
	return (!(oV==(*this)));
}

// u+v = (ux, uy, uz)+(vx, vy, vz) = (ux+vx, uy+vy, uz+vz)
Vector3D Vector3D::operator+(const Vector3D& oV) const
{
	Vector3D oResult(m_fX + oV.m_fX, m_fY + oV.m_fY, m_fZ + oV.m_fZ);
	return oResult;
}

// u-v = (ux, uy, uz)-(vx, vy, vz) = (ux-vx, uy-vy, uz-vz)
Vector3D Vector3D::operator-(const Vector3D& oV) const
{
	Vector3D oResult(m_fX - oV.m_fX, m_fY - oV.m_fY, m_fZ - oV.m_fZ);
	return oResult;
}

// u*k = (ux, uy, uz)*k = (ux*k,  uy*k, uz*k)
Vector3D Vector3D::operator*(float fScalar) const
{
	Vector3D oResult(m_fX * fScalar, m_fY * fScalar, m_fZ * fScalar);
	return oResult;
}

// NEW Multiply, version 2: scalar * vector.
Vector3D operator*(float fScalar, 
					const Vector3D& oV)
{
	Vector3D oResult(oV.m_fX * fScalar, oV.m_fY * fScalar, oV.m_fZ * fScalar);
	return oResult;
}

// Sets vectorlength to 1.
void Vector3D::Normalize()
{ 
	// Find current length.
	float fLength = Length();

	// Divide each component by current length to get length of 1.
	m_fX /= fLength;
	m_fY /= fLength;
	m_fZ /= fLength;
}

// u*v = (ux, uy, uz)*(vx, vy, vz) = ux*vx + uy*vy + uz*vz
float Vector3D::operator*(const Vector3D& oV) const
{
	return (m_fX * oV.m_fX) + (m_fY * oV.m_fY) + (m_fZ * oV.m_fZ);
}

Vector3D::operator const float*()  // Note: No return type for cast overloading.
{
	return &m_fX;  // To students: How can this work as an array!?
}

void Vector3D::CopyToFloatArray(float afCopy[3]) const
{
	afCopy[0] = m_fX;
	afCopy[1] = m_fY;
	afCopy[2] = m_fZ;
}