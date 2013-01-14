#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <string>
#include <sstream>

class IOManager
{
public:
	void printText(const char*);
	void printText(const std::string&);
	void printText(const std::stringstream&);
	void newLine();

	char getChar();
	int getNumber();
	std::string getName();
};

#endif