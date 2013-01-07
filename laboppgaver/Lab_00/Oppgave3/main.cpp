/**
 * ASSIGNMENT 3 AND 4!
 * NB: calculator object instantiated in main.h!
 *
 * @file: main.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <03.01.2013>
 *
 * @description: A primitive integer calculator program for
 *				 educational purposes.
 */

/* Includes */
#include <iostream> // I/O
#include "main.h"

// We're using functions from the std namespace
using namespace std;

/* Main program */
int main(int argc, char *argv[])
{
	// Declare variables
	int action, a, b;
	
	// Print the name of the program
	cout << "Stigulator v1.0.0" << endl << endl;
	
	// Program should run until user demands an exit
	while (true)
	{
		// Retrieve action from user
		getUserAction(&action);

		// Exit if user picked the exit action
		if (action == EXIT_ACTION)
		{
			cout << "Bye, bye ..." << endl;
			break; // Break the loop
		}

		// Clear result if asked
		if (action == CLEAR_ACTION)
		{
			calc.clear();
			cout << "Number cleared ..." << endl << endl;
			continue; // Skip the rest of the loop
		}

		// Retrieve the numbers from user
		getNumbers(&a, &b);

		// Validate the input, dividing by zero leads to a crash!
		if ((action == DIVIDE_ACTION) && (b == 0))
		{
			cout << "Can't divide by zero ..." << endl << endl;
			continue;
		}

		// Check the action, perform the proper operation, print result
		cout << "Result: ";

		switch (action)
		{
		case ADD_ACTION: // Addition
			calc.add(a, b);
			cout << a << " + " << b;
			break;
		case SUBTRACT_ACTION: // Subtraction
			calc.sub(a, b);
			cout << a << " - " << b;
			break;
		case DIVIDE_ACTION: // Division
			calc.div(a, b);
			cout << a << " / " << b;
			break;
		case MULTIPLY_ACTION: // Multiplication
			calc.mul(a, b);
			cout << a << " * " << b;
			break;
		}

		// Print final result
		cout << " = " << calc.getResult();

		// Make some visual space
		cout << endl << endl;
	} // <- Returns to top of loop

	// User wanted to quit
	return EXIT_SUCCESS;
}

/** Helper functions */

/* Retrieves an action from the user & validates it */
void getUserAction(int *action)
{
	// Reset the action to an "invalid" state
	*action = 0;

	// Ask for an action while "invalid"
	while ((ADD_ACTION > *action) || (*action > EXIT_ACTION))
	{
		// Output the action options
		cout << "Enter an action\n 1 - addition | 2 - subtraction | " <<
		"3 - division\n 4 - multiplication |  5 - clear result | 6 - exit\n: ";
			
		// Retrieve user input
		cin >> *action;

		// Validate input
		if ((ADD_ACTION > *action) || (*action > EXIT_ACTION))
		{
			cout << "Invalid action..." << *action << endl << endl;
		}
	}
}

/* Retrieves the numbers to perform calculations */
void getNumbers(int *a, int *b)
{
	// Retrieve the numbers from user
	if (calc.getResult() > 0)
	{
		*a = calc.getResult(); // Set a if we already have a result
		cout << endl;
	}
	else
	{
		// Retrieve the first number of the calculation
		cout << endl << "Enter the first number: ";
		cin >> *a; // User input
		cout << "You entered: " << *a << endl << endl;
	}
		
	// Retrieve the second number of the calculation
	cout << "Enter the second number: ";
	cin >> *b; // User input
	cout << "You entered: " << *b << endl << endl;
}