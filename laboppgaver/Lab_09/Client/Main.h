/**
 * @file: Main.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <17.04.2013>
 *
 * @description: A simple text based chat using Boost.Asio for
 *				 network communications. Behaves as both client and
 *				 server. Requires C++11 and Boost 1.53 libraries.
 */

#ifndef MAIN_H
#define MAIN_H

// For Linux
#ifndef EXIT_SUCCESS
	#define EXIT_SUCCESS 0
#endif // !EXIT_SUCCESS

// For Linux
#ifndef EXIT_FAILURE
	#define EXIT_FAILURE 1
#endif // !EXIT_FAILURE

#include <string>

/* PROTOTYPES */

/* Helper function to retrieve user name. */
std::string getUsername();

/* Helper function to retrieve a message name. */
std::string getMessage();

/**
 * Helper function to retrieve user input.
 * 
 * @param std::string prompt - Message to display to user.
 * @param std::string regex - regular expression to validate input.
 */
std::string getInput(const std::string& prompt, const std::string& regex);

#endif // inclusion guard