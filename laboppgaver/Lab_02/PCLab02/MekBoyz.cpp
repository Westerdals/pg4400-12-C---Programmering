#include <sstream>
#include "MekBoyz.h"

using std::endl;

MekBoyz::MekBoyz()
	:Orc(10, "MekBoyz Grunt")
{
	setStuff(true);
	setLearnedMechs(1);
	setMekType(Offensive);
}

MekBoyz::MekBoyz( int health, string name, bool stuffYN, int learned, MekType mekType )
	:Orc(health, name)
{
	setStuff(stuffYN);
	setLearnedMechs(learned);
	setMekType(mekType);
}

bool MekBoyz::getStuff()
{
	return m_hasStuff;
}

string MekBoyz::getStuffString()
{
	if(getStuff())
		return "Yes";
	else 
		return "No";
}

int MekBoyz::getLearnedMechs()
{
	return m_learnedMechs;
}

MekType MekBoyz::getMekType()
{
	return m_mekType;
}

std::string MekBoyz::getMekTypeString()
{
	switch(getMekType()){
		case Offensive:
			return "Offensive";
			break;

		case Defensive:
			return "Defensive";
			break;

		case Transport:
			return "Transport";
			break;

		case Scout:
			return "Scout";
			break;

		default:
			return "None";
			break;
	}
}

std::string MekBoyz::getFullDescription()
{
	std::stringstream result;
	result << "Name: " << getName() << endl << "Health: " << getHealth() << endl 
		<< "Has available tools and materials: " << getStuffString() << endl << 
		"Learned mechs: " << getLearnedMechs() << endl << "Mek type: " << getMekTypeString() 
		<< endl << endl;
	return result.str();
}

void MekBoyz::setStuff( bool stuffYN )
{
	m_hasStuff = stuffYN;
}

void MekBoyz::setLearnedMechs( int learned )
{
	m_learnedMechs = learned;
}

void MekBoyz::setMekType( MekType mekType )
{
	m_mekType = mekType;
}



