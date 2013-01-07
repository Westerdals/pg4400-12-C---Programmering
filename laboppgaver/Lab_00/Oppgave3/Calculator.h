/**
 * @file: Calculator.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <03.01.2013>
 *
 * @description: A class for integer calculations.
 */

#ifndef CALC_H // Inclusion guard
#define CALC_H

class Calculator
{
public:
	/* Class constructor, initializes calculator */
	Calculator();

	/* Adds two integers */
	int add(int a, int b);

	/* Subtracts two integers */
	int sub(int a, int b);

	/* Divides two integers */
	int div(int a, int b);

	/* Multiplies two integers */
	int mul(int a, int b);

	/* Clears the result */
	void clear();

	/* Returns the result of the last calculation */
	int getResult();
private:
	int m_result; // Variable to hold the results
};

#endif // end inclusion guard