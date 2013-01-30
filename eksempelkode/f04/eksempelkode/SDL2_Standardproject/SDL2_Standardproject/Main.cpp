/*
 * NOTE: WORK IN PROGRESS, DO NOT EXPECT THIS TO WORK!
 * Author: Stig M. Halvorsen <halsti@nith.no>
 */

#include <iostream>
#include "GameManager.h"

int main(int argc, char* argv[])
{
	try
	{
		GameManager::Instance().play();
		return EXIT_SUCCESS;
	}
	catch(const SDLError& err)
	{
		std::cerr << "An SDL error occured: "
				  << err.what() << std::endl;
	}
	catch(const std::exception& err)
	{
		std::cerr << "An error occured: "
				  << err.what() << std::endl;
	}
	catch(...)
	{
		std::cerr << "An unknown error occured ..." << std::endl;
	}

	return EXIT_FAILURE;
}