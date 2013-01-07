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

	/* Subtracts two integers */
	int sub(Pair p);

	/* Divides two integers */
	int div(Pair p);

	/* Multiplies two integers */
	int mul(Pair p);

	/* Clears the result */
	void clear();

	/* Returns the result of the last calculation */
	int getResult();
private:
	int m_result; // Variable to hold the results
};

#endif // end inclusion guard