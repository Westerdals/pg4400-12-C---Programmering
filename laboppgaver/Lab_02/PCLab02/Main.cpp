/* @file: Main.cpp
 * @author: Torkill Strømmen
 * 
 * @description: An "orc bank" to illustrate inheritage in C++.
 */

#include <iostream>
#include <vector>
#include <memory>

#include "Slugga.h"
#include "MekBoyz.h"
#include "Warboss.h"

int main()
{
	// List to hold the orc bank
	std::vector<std::unique_ptr<Orc>> orcList;
	
	// Push some orc types, test all various constructors
	orcList.push_back(std::unique_ptr<Slugga>(new Slugga(10, "TestSlugga", 20, 21)));
	orcList.push_back(std::unique_ptr<Slugga>(new Slugga()));

	orcList.push_back(std::unique_ptr<MekBoyz>(new MekBoyz(10, "TestMekBoyz", false, 2, Scout)));
	orcList.push_back(std::unique_ptr<MekBoyz>(new MekBoyz()));

	orcList.push_back(std::unique_ptr<Warboss>(new Warboss(20, "TestWarboss", "Corporal", "Just a test.")));
	orcList.push_back(std::unique_ptr<Warboss>(new Warboss()));

	orcList.push_back(std::unique_ptr<Orc>(new Orc(10, "TestOrc")));
	orcList.push_back(std::unique_ptr<Orc>(new Orc()));

	// Loop through the orc list, print descriptions.
	for(int i = 0; i < (signed)orcList.size(); i++)
		std::cout << orcList[i]->getFullDescription();

	system("pause");
	return EXIT_SUCCESS;
}