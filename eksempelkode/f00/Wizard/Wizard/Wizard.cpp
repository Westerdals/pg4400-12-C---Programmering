// wizard.cpp
#include <iostream>
#include "wizard.h"

using namespace std;

// Constructor, sets some default values
CWizard::CWizard()
{
	m_zName = "Gandalf";
	m_iHitPoints = 5;
	m_iMagicPoints = 20;
	m_iArmor = 100;
}

void CWizard::Fight()
{
    cout << "Fighting!" << endl;
}

void CWizard::Talk()
{
    cout << "Talking." << endl;
}

void CWizard::SetArmor(int iArmor)
{
	if(0 <= iArmor)
	{
		m_iArmor = iArmor;
	}
}

string CWizard::GetName()
{
	return m_zName;
}

void CWizard::CastSpell()
{
    if(4 < m_iMagicPoints)
	{
		cout << "Casting spell." << endl;
		m_iMagicPoints -= 5;
	} else {
		cout << "Not enough magic points to cast spell." << endl;
	}
}

void CWizard::PrintStats()
{
    cout << "Wizard stats:"
         << "\nName:\t" << m_zName 
         << "\n# hitpoints:\t" << m_iHitPoints 
		 << "\n# magicpoints:\t" << m_iMagicPoints
		 << "\nArmor strength:\t" << m_iArmor << endl;
}