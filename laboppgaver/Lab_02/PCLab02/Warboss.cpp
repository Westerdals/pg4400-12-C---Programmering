#include <sstream>
#include "Warboss.h"

using std::endl;

Warboss::Warboss()
	:Orc(10, "Warboss Grunt")
{
	setRank("Soldier");
	setDescription("Part of the Orc army. Wife, two kids, soon to be retired. Would be a shame if something was to happen to him.");
}

Warboss::Warboss(int health, std::string name,std::string rank, std::string description)
	:Orc(health, name)
{
	setRank(rank);
	setDescription(description);
}

std::string Warboss::getRank()
{
	return m_rank;
}

std::string Warboss::getDescription()
{
	return m_description;
}

std::string Warboss::getFullDescription()
{
	std::stringstream result;
	result << "Name: " << getName() << endl << "Health: " << getHealth() << endl <<
		"Rank: " << getRank() << endl << "Description: " << getDescription() << endl << endl; 
	return result.str();
}

void Warboss::setRank( std::string rank )
{
	m_rank = rank;
}

void Warboss::setDescription( std::string description )
{
	m_description = description;
}
