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

void IOManager::printSeparator()
{
	cout << "\n----------------\n";
}

char IOManager::getChar()
{
	char a;
	cin >> a;
	
	if (!cin.fail())
	{
		cin.ignore();
		return a;
	}
	else
	{
		clearCin();
		return ' ';
	}
}

int IOManager::getNumber()
{
	int a;
	cin >> a;
	
	if (!cin.fail())
	{
		cin.ignore();
		return a;
	}
	else
	{
		clearCin();
		return -1;
	}
}

string IOManager::getName()
{
	string name;
	getline(cin, name);
	
	if (!cin.fail())
	{
		return name;
	}
	else
	{
		clearCin();
		return "";
	}
}

void IOManager::clearCin()
{
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}