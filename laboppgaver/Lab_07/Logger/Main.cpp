/**
 * @file: Main.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <08.03.12>
 *
 * @description: A test of a simple log system.
 */

#include <iostream>
#include <thread>
#include "Logger\Logger.h"

int main(int argc, char* argv[])
{
	// Create main's logger
	Logger log("main");

	// Test the varius log levels
	log.log(WARN, "Working!");
	log.log(INFO, "But it's a potential trap.");

	// Sleep for 0.5 seconds to affect the log
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	log.log(CRITICAL, "Abandon the ship!");
	log.log(ERROR, "Everything went much worse than expected ...");

	// Formatted log entry
	log.logf(WARN, "The memory address is: #%08x.", &log);

	log << "Hei på deg\n";

	// Do some calculations to pass time, 5000 times
	for (int i = 0; i < 5000; ++i)
	{
		if ((i > 0) && (i % 1000 == 0))
		{
			log.log(INFO, "Thousand ", "iterations ", "have ", "passed by!", NULL); // End with NULL or "\n"
		}
		
		// DO some distance calculations
		float objectAPosX = 50.f;
		float objectBPosX = 45.f;

		// NB: pow and sqrt are computational heavy!
		float distance = abs(sqrt(pow(objectAPosX, 2) + pow(objectBPosX, 2)));
		objectAPosX -= distance;
		objectBPosX += distance;
	}

	system("pause");
	return EXIT_SUCCESS;
}