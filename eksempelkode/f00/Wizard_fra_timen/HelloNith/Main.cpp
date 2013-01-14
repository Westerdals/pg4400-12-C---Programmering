#include <iostream>
#include <string>
#include "Wizard.h"

using namespace std;

int main()
{
	{
		Wizard wiz;

		wiz.setName("Habib");
		wiz.talk();
	}

	system("Pause");
	return EXIT_SUCCESS;
}