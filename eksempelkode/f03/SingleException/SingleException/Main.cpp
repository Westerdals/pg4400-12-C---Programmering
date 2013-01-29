#include <iostream>
using namespace std;

// Make a custom exception
class DivideByZeroException : public runtime_error
{
public:
	DivideByZeroException::DivideByZeroException ()
		: runtime_error("Attempt to divide by zero!") {}
};

// Tries to divide to integers, throws exception on zero denominator
double Divide(int iNum, int iDenom) throw(DivideByZeroException)
{
	if (0 == iDenom)
	{
		throw DivideByZeroException();
	}

	return static_cast<double>(iNum)/iDenom;
}

// Main program
int main()
{
	int iNumerator = 0;  // "numerator"
	int iDenominator = 1;  // "denominator"

	cout << "Enter numerator: ";
	cin >> iNumerator;
	cout << "Enter denominator: ";
	cin >> iDenominator;

	try
	{
		cout << "The answer is " << Divide(iNumerator, iDenominator) << endl;
	}
	catch (exception& oException)
	{
		cout << "Exception: " << oException.what() << endl;
	}

	system("Pause");
	return EXIT_SUCCESS;
}