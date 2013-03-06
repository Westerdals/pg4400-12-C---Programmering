/**
 * @file: TestBoost.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <06.03.2013>
 *
 * @description: Tests whether you have installed boost
 *               successfully or not using boost's edition
 *               of shared_ptr.
 */

#include <iostream>
#include <string>
#include <boost\shared_ptr.hpp> // NB: Do not cunfuse this with C++11s (std::)shared_ptr!!!

// Entire program written in main
int main()
{
  // Create a new string on the heap using shared_ptr
	boost::shared_ptr<std::string> output(
		new std::string("It works!\n")
	);
	
	std::cout << *output; // Output string

	system("Pause");
	return EXIT_SUCCESS;
}