// @author: Tomas Sandnes (2011)
#include <iostream>
#include <cstring>
using namespace std;

/*
void GetName(char* pcName)
{
	cout << "Skriv inn navn" << endl;
	cin >> pcName;
}

*/

void GetName(char** ppcName)
{
	char acBuffer[1024] = {0};
	cout << "Skriv inn navn" << endl;
	cin >> acBuffer;
	delete[] *ppcName;
	*ppcName = new char[strlen(acBuffer) + 1];
	strncpy(*ppcName, acBuffer, strlen(acBuffer) + 1);
	cout << "Navnet jeg skrev inn var:" << endl << *ppcName << endl;
}

int main()
{
	char* pcName = 0;

	pcName = new char[4];
	strncpy(pcName, "Tst", 4);

	GetName(&pcName);

	cout << "Navnet jeg skrev inn var:" << endl << pcName << endl;

	delete[] pcName;
	system("pause");
	return 0;
}