/**
 * @file: Main.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <17.04.2013>
 *
 * @description: A simple text based chat using Boost.Asio for
 *				 network communications. Behaves as both client and
 *				 server. Requires C++11 and Boost 1.53 libraries.
 */

#include <thread>
#include <chrono>
#include <iostream>
#include <regex>

#include "Main.h" // function prototypes and globals here.
#include "InputManager.h"
#include "NetworkManager.h"

/* Runs the program's logic */
int main(int argc, char* argv[])
{
	bool running = true;
	const std::string ip = "127.0.0.1";
	unsigned short port = 8008;
	int keyPressed = iKEY_NONE;
	std::string userName;

	// Declare and initialize the input and network managers
	InputManager inputManager;
	NetworkManager netManager(boost::asio::ip::address::from_string(ip), port);

	// Try to connect (as client)
	if (netManager.tryConnect())
	{
		std::cout << "Connected successfully, behaving as client!" << std::endl;
	}
	else
	{
		// Failed, behave as server.
		std::cout << "Failed to connect, behaving as server!" << std::endl;
		netManager.startServer();
	}

	// Get a user name
	userName = getUsername();
	
	// Main program loop (similar to a game loop)
	while (running)
	{
		// Check for input
		if (inputManager.getNextKey(&keyPressed))
		{
			// FOR "DEBUGGING": (if you want to add keys to InputKeys.h)
			// std::cout << "Key pressed: " << keyPressed << std::endl;

			// Check if user pressed Q, exit in that case
			if ((keyPressed == iKEY_q) || (keyPressed == iKEY_Q))
			{
				running = false;
			}

			// Check if user pressed W (write)
			if ((keyPressed == iKEY_w) || (keyPressed == iKEY_W))
			{
				// Retrieve message from user, combine it with username
				std::string message = getMessage();
				std::string data = userName + ": " + message;

				netManager.sendData(data); // Transmit message
			}

			// Check if user pressed N (new username)
			if ((keyPressed == iKEY_n) || (keyPressed == iKEY_N))
			{
				userName = getUsername();
			}
		}

		// Network does it's job in asynchronous threads

		// Sleep for 100ms, prevent CPU exhaustion
		if (running)
		{
			std::this_thread::sleep_for(
				std::chrono::milliseconds(100)
			);
		}
	}

	std::cout << "Bye bye ..." << std::endl;
	return EXIT_SUCCESS;
}

/* Helper function to retrieve user name. */
std::string getUsername()
{
	return getInput("Set username: ", "[a-zA-Z0-9]{3,20}");
}

/* Helper function to retrieve a message name. */
std::string getMessage()
{
	return getInput("Message: ",
		"[a-zA-Z0-9 ?!'\"\".:,;<>«»|@£$€#¤%&-+=*/{}()æøå]{1,100}");
}

/**
 * Helper function to retrieve user input.
 * 
 * @param std::string prompt - Message to display to user.
 * @param std::string regex - regular expression to validate input.
 */
std::string getInput(const std::string& prompt, const std::string& regex)
{
	std::string input;
	bool invalid = true;
	std::regex validator(regex);

	// Keep asking while input is marked as invalid.
	while (invalid)
	{
		// Print the prompt, retrieve a line from the user
		std::cout << prompt;
		std::getline(std::cin, input);

		// Check for cin failures (really bad input)
		if (std::cin.fail())
		{
			std::cout << "Invalid input!" << std::endl;
			input = ""; // Reset in-data

			// Reset cin; clear buffer and error flags.
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
		}
		else
		{
			// C++11: validate the input with the regular expression
			if (std::regex_match(input, validator))
			{
				invalid = false;
			}
			else
			{
				std::cout << "Invalid input, only " << regex << "." << std::endl;
			}
		}
	}

	return input;
}