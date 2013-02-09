/**
 * @file: Main.cpp
 * @author: Stig M. Halvorsen
 * @version: 1.0.0 <09.02.2013>
 *
 * @description: A program to test the C++11 timer, high_resolution_clock.
 *				 Implements a DeltaTimer object to calculate elapsed time
 *				 between two frames.
 */

#include <iostream>
#include "Timer.h"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[])
{
	Timer::Instance().init(); // Start our timer
	bool gameNotOver = true;
	
	// "Gameloop", asks for user input. Quits on command.
	while (gameNotOver)
	{
		char reply;
		Timer::Instance().update(); // Update the timer

		// Ask user, and fetch reply
		cout << "Exit [y/n]: ";
		cin >> reply;

		// Look for errors with cin
		if (cin.fail())
		{
			// Clear error flags
			cin.clear();

			// Empty buffer by «ignoring» all possible values
			cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			// No errors, check input
			if ((reply == 'y') || (reply == 'Y'))
			{
				gameNotOver = false; // exit
			}
		}
		
		// Print timer stats
		std::cout << "Time elapsed: " << Timer::Instance().elapsedTime() <<
			"s || Delta time: " << Timer::Instance().deltaTime() << "s." << endl;
	}

	return EXIT_SUCCESS;
}