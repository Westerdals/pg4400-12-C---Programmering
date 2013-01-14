// main.cpp
#include "Wizard.h"

int main()
{
	CWizard oWiz;

	oWiz.CastSpell();
	oWiz.Fight();

	//oWiz.m_iArmor = 10;  // Compiler error

	oWiz.PrintStats();
	oWiz.Talk();
	oWiz.Talk();

	system("Pause");
	return EXIT_SUCCESS;
}