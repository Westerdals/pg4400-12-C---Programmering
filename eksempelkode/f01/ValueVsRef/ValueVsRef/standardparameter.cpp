#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int GetRandomNumber(int iMin = 0, 
                    int iMax = 100);

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	int iRandomNum1 = GetRandomNumber(10, 20);  // Alle tilstede.
	int iRandomNum2 = GetRandomNumber(50);      // Siste mangler.
	int iRandomNum3 = GetRandomNumber();        // Begge mangler.
	cout << "The random numbers are "  << iRandomNum1 << ", " 
		   << iRandomNum2 << ", " << iRandomNum3 << endl;
	system("Pause");
	return 0;
}

int GetRandomNumber(int iMin, int iMax)
{
	cout << "random number in [" << iMin << ", " << iMax << "]" << endl;
	return iMin + (rand() % (iMax + 1 - iMin));
}