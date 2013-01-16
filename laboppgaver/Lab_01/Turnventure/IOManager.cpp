/**
 * @file: IOManager.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * 
 * @description: A set of functions for user input & output.
 */

#include <iostream>
#include "IOManager.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;

/* Outputs the given character sequence */
void IOManager::printText(const char* text)
{
	cout << text;
}

/* Outputs the given string */
void IOManager::printText(const string& text)
{
	cout << text;
}

/* Outputs the contents of the given stringstream. */
void IOManager::printText(const stringstream& s)
{
	cout << s.str();
}

/* Outputs a new line */
void IOManager::newLine()
{
	cout << endl;
}

/* Outputs a dashed line separator with both
   post-/prefix spacing */
void IOManager::printSeparator()
{
	cout << "\n----------------\n";
}

/* Retrieves a character from user input. '\n' on failure. */
char IOManager::getChar()
{
	// Retrieve a character from user
	char a;
	cin >> a;
	
	// Check for errors
	if (!cin.fail())
	{
		// Success!
		cin.ignore(); // needed for co-operation with getline
		return a; // return result
	}
	else
	{
		// Error, clear cin. Return '\n'.
		clearCin();
		return '\n';
	}
}

/* Retrieves a character from user input. -1 on failure. */
int IOManager::getNumber()
{
	// Retrieve number from user
	int a;
	cin >> a;
	
	// Check for errors
	if (!cin.fail())
	{
		// Success
		cin.ignore(); // needed for co-operation with getline
		return a;
	}
	else
	{
		// Error, clear cin!
		clearCin();
		return -1;
	}
}

/* Retrieves a line (string) from user, typically a name */
string IOManager::getName()
{
	// Retireve line
	string name;
	getline(cin, name);
	
	// Check for errors
	if (!cin.fail())
	{
		return name; // Success
	}
	else
	{
		// Error, clear cin
		clearCin();
		return "";
	}
}

/* Helper function to reset cin on input errors */
void IOManager::clearCin()
{
	// Clear flags
	cin.clear();

	// Clear bad buffer w/errors
	cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}