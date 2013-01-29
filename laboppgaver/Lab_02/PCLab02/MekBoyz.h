#ifndef MEKBOYZ_H
#define MEKBOYZ_H
#include "Orc.h"

enum MekType{
		Offensive,
		Defensive,
		Transport,
		Scout	
	};

class MekBoyz : public Orc
{
public:
	MekBoyz();
	MekBoyz(int health, std::string name, bool stuffYN, int learned, MekType mekType);
	bool getStuff();
	std::string getStuffString();
	int getLearnedMechs();
	MekType getMekType();
	std::string getMekTypeString();
	std::string getFullDescription();
	void setStuff(bool stuffYN);
	void setLearnedMechs(int learned);
	void setMekType(MekType mekType);

private: 
	bool m_hasStuff;
	int m_learnedMechs;
	MekType m_mekType;
};


#endif