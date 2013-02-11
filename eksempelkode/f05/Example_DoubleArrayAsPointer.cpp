//////////////////////////////////////////////////////////////////////////////
//																			//
//						NITH, 2008, Tomas Sandnes							//
//																			//
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

const int g_iSIZE_X = 4;
const int g_iSIZE_Y = 4;

void TraverseDoubleArray( const int* piDoubleArray )
{
	cout << "Inside function, double-array as pointer, values are:" << endl;
	// Merk: Her finner jeg st�rrelsen via globale konstanter. 
	//       Alternativt kunne array-st�rrelsene v�rt lagt med som inn-parametere.
	for (int x = 0; x < g_iSIZE_X; ++x)
	{
		for (int y = 0; y < g_iSIZE_Y; ++y)
		{
			// "Algoritmen" i utskriften under flytter pekeren s� den treffer 
			// rett element. Blir akkurat det samme som: aaiDoubleArray[x][y]. 
			// Bare at array-notasjon ikke virker n�r vi har en peker inn. :-)
			cout << "Value for x = " << x << ", y = " << y << ": " << *(piDoubleArray + (x * g_iSIZE_Y) + y) << endl;
		}
	}
	cout << endl;
}

int main()
{
/*
	// Visuell m�te � opprette array p�: (men mindre dynamisk enn den under, derfor har jeg valgt for-l�kke versjonen)
	// En array ligger inne i den andre:   x   |---  0  --|  |---  1  --|  |---  2  ----|  |-----  3  ----|  
	//                                     y    0  1  2  3    0  1  2  3    0  1   2   3     0   1   2   3
	int aaiTestValues[g_iSIZE_X][g_iSIZE_Y] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
*/
	// Dynamisk m�te � initialisere arrayen p� - denne vokser i takt med konstantene for array st�rrelsen:
	int iValueCounter = 0;
	int aaiTestValues[g_iSIZE_X][g_iSIZE_Y];  // Initialiserer ikke her, men i for-l�kka under.
	for (int x = 0; x < g_iSIZE_X; ++x)
	{
		for (int y = 0; y < g_iSIZE_Y; ++y)
		{
			aaiTestValues[x][y] = iValueCounter;
			iValueCounter++;
		}
	}

	// Output av array direkte:
	cout << "Inside main, double-array as double-array, values are:" << endl;
	for (int x = 0; x < g_iSIZE_X; ++x)
	{
		for (int y = 0; y < g_iSIZE_Y; ++y)
		{
			cout << "Value for x = " << x << ", y = " << y << ": " << aaiTestValues[x][y] << endl;
		}
	}
	cout << endl;

	// Output via funksjon med peker til array:
	TraverseDoubleArray(&aaiTestValues[0][0]);  // Sender adressen til f�rste element i arrayen som inn-parameter (fungerer da som peker).

	system("Pause");
	return 0;
}
