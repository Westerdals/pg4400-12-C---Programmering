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
enum ACTIONS
{
	ADD_ACTION = 1,
	SUBTRACT_ACTION,
	DIVIDE_ACTION,
	MULTIPLY_ACTION,
	CLEAR_ACTION,
	EXIT_ACTION
};

/** PROTOTYPES - helper functions */

/* Retrieves an action from the user & validates it */
void getUserAction(int *action);

/* Retrieves the numbers to perform calculations */
void getNumbers(int *a, int *b);

#endif