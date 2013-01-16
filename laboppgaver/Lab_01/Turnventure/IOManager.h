/**
 * @file: IOManager.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * 
 * @description: A set of functions for user input & output.
 */

#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <string>
#include <sstream>

class IOManager
{
public:
	/* Outputs the given character sequence */
	void printText(const char*);

	/* Outputs the given string */
	void printText(const std::string&);

	/* Outputs the contents of the given stringstream. */
	void printText(const std::stringstream&);

	/* Outputs a new line */
	void newLine();

	/* Outputs a dashed line separator with both
	   post-/prefix spacing */
	void printSeparator();

	/* Retrieves a character from user input. '\n' on failure. */
	char getChar();

	/* Retrieves a character from user input. -1 on failure. */
	int getNumber();

	/* Retrieves a line (string) from user, typically a name */
	std::string getName();
private:
	/* Helper function to reset cin on input errors */
	void clearCin();
};

#endif