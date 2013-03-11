/**
 * @file: Logger.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <08.03.12>
 *
 * @description: A log system wrapping the Singleton LogSys class. Gives
 *				 multiple logging possibilities to the user.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
#include "LogSys.h"

class Logger
{
public:
	/* Creates a new Logger with the given String as the log caller (i.e. "OutputManager") */
	Logger(const std::string& owner);

	/* Creates a new Logger with the given String as the log caller (i.e. typeid(this)) */
	Logger(const type_info& owner);

	/* Logs a single message */
	void log(const LogLevels& level, const std::string& message);

	/* Logs a single message, with loglevel as a string */
	void log(const std::string& level, const std::string& message);

	/* Logs a message of multiple parameters. Remember to terminate with NULL or \n as final param. */
	void log(const LogLevels level, ...);

	/* Logs a formatted message of multiple parameters, works just like printf()! */
	void logf(const LogLevels level, const char* format, ...);

	/* Overloaded << which sets the active LogLevel. This is required for
	us to be able to set the LogLevel through the << operator. */
	Logger& operator<<(const LogLevels& level);

	/* Overloaded << "hack" that triggers on newlines std::endl in << ostreams.
	This is required in order to be able to catch the end of a stream and
	write to our log file. */
	Logger& operator<<(std::ostream& (*f)(std::ostream&))
	{
		// Write our buffer to the log
		LogSys::instance().write(m_owner, m_currentLevel, m_ostreamBuffer.str());

		// Clear our buffer and potential error flags
		m_ostreamBuffer.str("");
		m_ostreamBuffer.clear();

		return *this;
	}

	/* Overloaded << template function which populates our buffer with
	various data. It allows us to log anything possible. NB: log() is
	more efficient */
	template<typename T> Logger& operator<<(const T& message)
	{
		bool writeFile = false; // Whether we should write to file or not.

		// Check for a NULL, marking end of line. We should write to file then.
		if (NULL == message)
		{
			std::cout << "NULL type!" << std::endl;
		}
		else
		{
			// Try to put the data in another stream first in order to prevent
			// destroying our own data on failure.
			std::stringstream errorChecker;
			errorChecker << message;

			// Check for failures
			if (errorChecker.good())
			{
				// No failure occured, get the contents of the data as string
				std::string newLineCheck = errorChecker.str();

				// Check for newline, we should write to file then.
				if (newLineCheck == "\n")
				{
					writeFile = true;
				}
				// Check for newline at the end of the string.
				else if ((newLineCheck.length() > 2) &&
						(newLineCheck.substr(newLineCheck.length() - 1, 1) == "\n"))
				{
					// Newline detected, add data to stream and set write to file
					m_ostreamBuffer << newLineCheck.substr(0, newLineCheck.length() - 1);
					writeFile = true;
				}
				else
				{
					// Everything is OK, add our message to the stream
					m_ostreamBuffer << message;
				}
			}
		}

		// Write to file if instructed
		if (writeFile)
		{
			// Write our buffer to the log
			LogSys::instance().write(m_owner, m_currentLevel, m_ostreamBuffer.str());

			// Clear our buffer and potential error flags
			m_ostreamBuffer.str("");
			m_ostreamBuffer.clear();
		}

		return *this;
	}
private:
	std::string m_owner; // Owner object, i.e.: "OutputManager"
	LogLevels m_currentLevel; // Last set/current set log level
	std::stringstream m_ostreamBuffer; // buffer for operator<< functions
};

#endif