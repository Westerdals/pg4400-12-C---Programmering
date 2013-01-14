#include <iostream>
#include "IOManager.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;

void IOManager::printText(const char* text)
{
	cout << text;
}

void IOManager::printText(const string& text)
{
	cout << text;
}

void IOManager::printText(const stringstream& s)
{
	cout << s.str();
}


void IOManager::newLine()
{
	cout << endl;
}

char IOManager::getChar()
{
	char a;
	cin >> a;

	return a;
}

int IOManager::getNumber()
{
	int a;
	cin >> a;

	return a;
}

string IOManager::getName()
{
	string name;
	getline(cin, name);

	return name;
}