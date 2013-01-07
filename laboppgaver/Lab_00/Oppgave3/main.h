/**
 * @file: main.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <03.01.2013>
 *
 * @description: A primitive integer calculator program for
 *				 educational purposes.
 */

#ifndef MAIN_H
#define MAIN_H

#include "Calculator.h"

/** Global Calculator object */
Calculator calc;

/** USER ACTIONS */
enum USER_ACTION
{
	NOT_SET,
	ADD_ACTION,
	SUBTRACT_ACTION,
	DIVIDE_ACTION,
	MULTIPLY_ACTION,
	CLEAR_ACTION,
	EXIT_ACTION
};

/** PROTOTYPES - helper functions */

/* Retrieves an action from the user & validates it */
USER_ACTION getUserAction();

/* Retrieves the numbers to perform calculations */
Pair getNumbers();

#endif