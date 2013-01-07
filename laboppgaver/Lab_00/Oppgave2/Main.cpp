#include <iostream> 
using namespace std;

int main()
{
	cout << endl << "Printing the ascii table:" << endl << endl;

	for (int i = 33; i < 256; ++i)
	{
		// Casting counter as char to get output:
		cout << i << ": " << static_cast<char>(i) << " ";
		if (0 == ((i - 32) % 10))
		{
			cout << endl;
		}
	}
	cout << endl << endl;
	
	system("Pause");
	return 0;
}