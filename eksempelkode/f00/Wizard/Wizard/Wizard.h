#ifndef WIZARD_H
#define WIZARD_H

// wizard.h
#include <string>
using std::string;

class CWizard {
	public:
		// Constructor
		CWizard();

		// Member functions.
		void Fight();
		void Talk();
		void SetArmor(int iArmor);
		string GetName();
		void CastSpell();
		void PrintStats();
	private:	
		// Member data / helper functions
		string m_zName;
		int m_iHitPoints;
		int m_iMagicPoints;
		int m_iArmor;
};

#endif