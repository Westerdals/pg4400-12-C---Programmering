/*
 * @file: main.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.1
 *
 * @description: A program that implements and tests a std::shared_ptr
 * like Smart Pointer. NB: I've put it in the std namespace on purpose.
 * It does NOT support arrays!
 */

// Includes
#include <iostream>
#include <string>
#include "smart_ptr.h"

// Main, "..." means support for multiple arguments
int main(...)
{
	// Brackets to test the scope
	{
		// Test with integers
		std::smart_ptr<int> integer(new int(56)); // Creation
		std::smart_ptr<int> integer2(integer); // Copy
		std::smart_ptr<int> integer3 = integer2; // Copy assignment

		// Test with strings (objects)
		std::smart_ptr<std::string> string(new std::string("C++ rules!")); // Creation
		std::smart_ptr<std::string> string2 = string; // Copy assignment

		// Example of usage (substring, object function)
		std::string regularString = string->substr(0, string->size() / 2);

		// Print substring result
		std::cout << std::endl << "The string cut in half at memory location #"
			<< string.get()<< " is: " << regularString << std::endl << std::endl;
	} // Smart pointers out of scope

	system("pause");
	return EXIT_SUCCESS;
}