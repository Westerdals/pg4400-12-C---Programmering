/**
 * @file: Main.cpp
 * @original-author: André R. Brodtkolb
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.1.0 <03.04.2013> 
 *
 * @description: A program that computes the sum from 
 *				 0-k og i+i^2+i^3 for k-N. Stores the
 *				 result in a vector, and prints out the
 *				 first and last five elements.
 *
 *				 This code example is made to be optimized!
 */

// Contains includes and definitions to keep this code short
#include "Global.h"

int main(int argc, char* argv[])
{
	// Number of sums to calculate
	const int N = 5500;

	array<long long, N> sums; // Array to hold the sums
	time_point start = high_resolution_clock::now(); // Retrieve start point

	// Compute the sums
	for (int k = 0; k < N; ++k)
	{
		sums[k] = myFunction1(k);
	}

	// Print the first 5 items in the list
	for (int k = 0; k < 5; ++k)
	{
		cout << "sum_0^" << k << " (i+i^2+i^4) = " << sums[k] << endl;
	}

	cout << "..." << endl;

	// Print the last 5 items in the list
	for (int k = (N - 5); k < N; ++k)
	{
		cout << "sum_0^" << k << " (i+i^2+i^4) = " << sums[k] << endl;
	}

	// Calculate and print processing time in seconds
	cout << endl << "Calculated in " <<
		duration_cast<std::chrono::milliseconds>(
			high_resolution_clock::now() - start).count() / 1000.0
	<< " seconds." << endl << endl;

	//system("pause");
	return EXIT_SUCCESS;
}

// Function performing the heavy calculation
long long f(long long i)
{
	return i + static_cast<long long>(pow(i, 2.0) + pow(i, 4.0));
}

// Compute sum_0^n i+i^2
long long myFunction1(int n)
{
	long long retval = 0;

	for (long long i = 0; i <= n; ++i)
	{
		retval += f(i);
	}

	return retval;
}