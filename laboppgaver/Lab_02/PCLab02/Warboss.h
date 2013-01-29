#ifndef WARBOSS_H
#define WARBOSS_H
#include "Orc.h"

class Warboss : public Orc
{
public:
	Warboss();
	Warboss(int health, std::string name,std::string rank, std::string description);
	std::string getRank();
	std::string getDescription();
	std::string getFullDescription();
	void setRank(std::string rank);
	void setDescription(std::string description);

private: 
	std::string m_rank;
	std::string m_description;
};


#endif