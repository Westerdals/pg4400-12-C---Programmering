/**
 * @file: Calculator.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <03.01.2013>
 *
 * @description: A class for integer calculations.
 */

#include "Calculator.h"

/* Class constructor */
Calculator::Calculator()
{
	clear(); // Clears result
}

/* Adds two integers */
int Calculator::add(Pair p)
{
	m_result = p.a + p.b;
	return m_result;
}

/* Subtracts two integers */
int Calculator::sub(Pair p)
{
	m_result = p.a - p.b;
	return m_result;
}

/* Divides two integers */
int Calculator::div(Pair p)
{
	m_result = p.a / p.b;
	return m_result;
}

/* Multiplies two integers */
int Calculator::mul(Pair p)
{
	m_result = p.a * p.b;
	return m_result;
}

/* Clears the result */
void Calculator::clear()
{
	m_result = 0;
}

/* Returns the result of the last calculation */
int Calculator::getResult()
{
	return m_result;
}