#include <iostream>
#include <memory>
using namespace std;

struct SBigOne
{
	double adLotsOfBytes[50000000];
};

int main()
{
	unique_ptr<SBigOne> apoBigOnePointerArray[50];

	try
	{
		cout << "Starter allokering ..." << endl;

		for (int i = 0; i < 50; ++i)
		{
			apoBigOnePointerArray[i] = unique_ptr<SBigOne>(new SBigOne);
			cout << "Allokerte 50 000 000 doubles, runde " << (i + 1) << "." << endl;
		}

		cout << "... allokering ferdig." << endl;
	}
	catch (const bad_alloc& oBadAlloc)
	{
		cout << "Kunne ikke allokere: " << oBadAlloc.what() << endl;
		exit(EXIT_FAILURE);
	}
	
	system("Pause");  // Note: exit(...) overrides this.
	return EXIT_SUCCESS;
}