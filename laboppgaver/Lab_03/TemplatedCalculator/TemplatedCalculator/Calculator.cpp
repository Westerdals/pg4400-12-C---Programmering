/**
 * @file: Calculator.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.1.0 <04.02.2013>
 *
 * @description: A class for number calculations.
 */

#ifndef CALCULATOR_CPP // Inclusion guard due to include of cpp file in h file
#define CALCULATOR_CPP // This is to be able to separate the files

#include "Calculator.h"

/* Class constructor */
template <class T> Calculator<T>::Calculator()
{
	clear(); // Clears result
}

/* Adds two numbers */
template <class T> T Calculator<T>::add(Pair<T> p)
{
	m_result = p.a + p.b;
	return m_result;
}

/* Adds two numbers */
template <class T> T Calculator<T>::operator+(Pair<T> p)
{
	return add(p);
}

/* Adds numbers to current result */
template <class T> T Calculator<T>::operator+=(T n)
{
	m_result += n;
	return m_result;
}

/* Subtracts two numbers */
template <class T> T Calculator<T>::sub(Pair<T> p)
{
	m_result = p.a - p.b;
	return m_result;
}

/* Subtracts two numbers */
template <class T> T Calculator<T>::operator-(Pair<T> p)
{
	return sub(p);
}

/* Subtracts number from current stored result */
template <class T> T Calculator<T>::operator-=(T n)
{
	m_result -= n;
	return m_result;
}

/* Divides two numbers */
template <class T> T Calculator<T>::div(Pair<T> p)
{
	m_result = p.a / p.b;
	return m_result;
}

/* Divides two numbers */
template <class T> T Calculator<T>::operator/(Pair<T> p)
{
	return div(p);
}

/* Divides number from current result */
template <class T> T Calculator<T>::operator/=(T n)
{
	m_result /= n;
	return m_result;
}

/* Multiplies two numbers */
template <class T> T Calculator<T>::mul(Pair<T> p)
{
	m_result = p.a * p.b;
	return m_result;
}

/* Multiplies two numbers */
template <class T> T Calculator<T>::operator*(Pair<T> p)
{
	return mul(p);
}

/* Multiplies number with current result */
template <class T> T Calculator<T>::operator*=(T n)
{
	m_result *= n;
	return m_result;
}

/* Clears the result */
template <class T> void Calculator<T>::clear()
{
	m_result = 0;
}

/* Returns the result of the last calculation */
template <class T> T Calculator<T>::getResult()
{
	return m_result;
}

#endif