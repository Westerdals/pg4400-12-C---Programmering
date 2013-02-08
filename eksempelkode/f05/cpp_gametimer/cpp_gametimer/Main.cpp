#include <iostream>
#include "Timer.h"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[])
{
	bool gameNotOver = true;
	Timer::Instance().init();

	while (gameNotOver)
	{
		char reply;
		Timer::Instance().update();

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
				gameNotOver = false;
			}
		}
		
		std::cout << "Time elapsed: " << Timer::Instance().elapsedTime() << "s || Delta time: " << Timer::Instance().deltaTime() << "s." << endl;
	}

	return EXIT_SUCCESS;
}