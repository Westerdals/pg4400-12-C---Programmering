/**
 * @file: Calculator.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.1.0 <04.02.2013>
 *
 * @description: A class for number calculations.
 */

#ifndef CALC_H // Inclusion guard
#define CALC_H

#include "Pair.h"

template <class T>
class Calculator
{
public:
	/* Class constructor, initializes calculator */
	Calculator();

	/* Adds two numbers */
	T add(Pair<T> p);

	/* Adds two numbers */
	T operator+(Pair<T> p);

	/* Adds number to current result */
	T operator+=(T n);

	/* Subtracts two numbers */
	T sub(Pair<T> p);

	/* Subtracts two numbers */
	T operator-(Pair<T> p);

	/* Subtracts number from current stored result */
	T operator-=(T n);

	/* Divides two numbers */
	T div(Pair<T> p);

	/* Divides two numbers */
	T operator/(Pair<T> p);

	/* Divides number from current result */
	T operator/=(T n);

	/* Multiplies two numbers */
	T mul(Pair<T> p);

	/* Multiplies two numbers */
	T operator*(Pair<T> p);

	/* Multiplies number with current result */
	T operator*=(T n);

	/* Clears the result */
	void clear();

	/* Returns the result of the last calculation */
	T getResult();
private:
	T m_result; // Variable to hold the results
};

// Exclusive instantiation to make sure we don't support
// unsupported objects.
template Calculator<int>;
template Calculator<float>;
template Calculator<double>;
template Calculator<long>;

// Include the cpp file. This is to be able to separate the files
#include "Calculator.cpp"

#endif // end inclusion guard