/**
 * @file: Calculator.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <03.01.2013>
 *
 * @description: A class for integer calculations.
 */

#ifndef CALC_H // Inclusion guard
#define CALC_H

#include "Pair.h"

class Calculator
{
public:
	/* Class constructor, initializes calculator */
	Calculator();

	/* Adds two integers */
	int add(Pair p);

	/* Adds two integers */
	int operator+(Pair p);

	/* Adds integer to current result */
	int operator+=(int n);

	/* Subtracts two integers */
	int sub(Pair p);

	/* Subtracts two integers */
	int operator-(Pair p);

	/* Subtracts integer from current stored result */
	int operator-=(int n);

	/* Divides two integers */
	int div(Pair p);

	/* Divides two integers */
	int operator/(Pair p);

	/* Divides integer from current result */
	int operator/=(int n);

	/* Multiplies two integers */
	int mul(Pair p);

	/* Multiplies two integers */
	int operator*(Pair p);

	/* Multiplies integer with current result */
	int operator*=(int n);

	/* Clears the result */
	void clear();

	/* Returns the result of the last calculation */
	int getResult();
private:
	int m_result; // Variable to hold the results
};

#endif // end inclusion guard