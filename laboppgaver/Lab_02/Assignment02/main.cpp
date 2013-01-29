/**
 * ASSIGNMENT 3 AND 4!
 * NB: calculator object instantiated in main.h!
 *
 * @file: main.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.1.0 <29.01.2013>
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
	USER_ACTION action;
	Pair numbers;
	bool exit = false;
	
	// Print the name of the program
	cout << "Stigulator v1.1.0" << endl << endl;
	
	// Program should run until user demands an exit
	while (!exit)
	{
		// Retrieve action from user
		action = getUserAction();

		// Retrieve numbers if an appropriate action is selected
		if ((EXIT_ACTION != action) && (CLEAR_ACTION != action))
		{
			// Retrieve the numbers from user
			numbers = getNumbers();

			// Check the action, perform the proper operation, print result
			cout << "Result: ";
		}

		// Perform the proper action
		switch (action)
		{
		case ADD_ACTION: // Addition
			//calc.add(numbers);
			calc + numbers;
			//calc += numbers.b;
			cout << numbers.a << " + " << numbers.b;
			break;
		case SUBTRACT_ACTION: // Subtraction
			//calc.sub(numbers);
			calc - numbers;
			//calc -= numbers.b;
			cout << numbers.a << " - " << numbers.b;
			break;
		case DIVIDE_ACTION: // Division
			// Validate input, dividing by zero will crash the program
			if (0 < numbers.b)
			{
				//calc.div(numbers);
				calc / numbers;
				//calc /= numbers.b;
				cout << numbers.a << " / " << numbers.b;
			}
			else
			{
				cout << "Can't divide by zero ..." << endl << endl;
			}
			
			break;
		case MULTIPLY_ACTION: // Multiplication
			//calc.mul(numbers);
			calc * numbers;
			//calc *= numbers.b;
			cout << numbers.a << " * " << numbers.b;
			break;
		case CLEAR_ACTION: // Clear number
			calc.clear();
			cout << "Number cleared ..." << endl << endl;
			break;
		case EXIT_ACTION: // Exit program
			exit = true;
			cout << "Bye, bye ..." << endl;
			break; // Skip the rest of the loop
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
USER_ACTION getUserAction()
{
	// Set the action to an "invalid" state
	USER_ACTION action = NOT_SET;

	// Ask for an action while "invalid"
	while (NOT_SET == action)
	{
		// Output the action options
		cout << "Enter an action\n 1 - addition | 2 - subtraction | " <<
		"3 - division\n 4 - multiplication |  5 - clear result | 6 - exit\n: ";
			
		// Retrieve user input
		int actionIn;
		cin >> actionIn;

		// Validate input
		if ((ADD_ACTION > actionIn) || (actionIn > EXIT_ACTION))
		{
			cout << "Invalid action..." << actionIn << endl << endl;
		}
		else
		{
			action = static_cast<USER_ACTION>(actionIn);
		}
	}

	return action;
}

/* Retrieves the numbers to perform calculations */
Pair getNumbers()
{
	Pair result;

	// Retrieve the numbers from user
	if (calc.getResult() > 0)
	{
		result.a = calc.getResult(); // Set a if we already have a result
		cout << endl;
	}
	else
	{
		// Retrieve the first number of the calculation
		cout << endl << "Enter the first number: ";
		cin >> result.a; // User input
		cout << "You entered: " << result.a << endl << endl;
	}
		
	// Retrieve the second number of the calculation
	cout << "Enter the second number: ";
	cin >> result.b; // User input
	cout << "You entered: " << result.b << endl << endl;

	return result;
}