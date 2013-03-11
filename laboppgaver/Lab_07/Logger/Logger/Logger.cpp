/**
 * @file: Logger.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <08.03.12>
 *
 * @description: A log system wrapping the Singleton LogSys class. Gives
 *				 multiple logging possibilities to the user.
 */

#include <cstdarg>
#include <sstream>
#include "Logger.h"

/* Creates a new Logger with the given String as the log caller (i.e. "OutputManager") */
Logger::Logger(const std::string& owner)
{
	m_owner = owner;
}

/* Creates a new Logger with the given String as the log caller (i.e. typeid(this)) */
Logger::Logger(const type_info& owner)
{
	Logger(typeid(owner).name());
}

/* Logs a single message */
void Logger::log(const LogLevels& level, const std::string& message)
{
	m_currentLevel = level;
	LogSys::instance().write(m_owner, m_currentLevel, message);
}

/* Logs a single message, with loglevel as a string */
void Logger::log(const std::string& level, const std::string& message)
{
	log(LogSys::instance().stringToLogLevels(level), message);
}

/* Logs a message of multiple parameters. Remember to terminate with NULL or \n as final param. */
void Logger::log(const LogLevels level, ...)
{
	std::stringstream combined; // Used to combine the arguments
	m_currentLevel = level; // Set current level (for op<<)
	
	// Fetch argument list
	va_list args;
	va_start(args, level);
	
	// Get the first argument
	char *arg = va_arg(args, char*);

	// Fetch arguments as long as we haven't terminated (NULL or \n)
	while ((arg != NULL) && (arg != "\n"))
	{
		combined << arg;
		arg = va_arg(args, char*);
	}

	// "Clean-up" and write results to file
	va_end(args);
	LogSys::instance().write(m_owner, m_currentLevel, combined.str());
}

/* Logs a formatted message of multiple parameters, works just like printf()! */
void Logger::logf(const LogLevels level, const char* format, ...)
{
	m_currentLevel = level; // Set current level (for op<<)

	// Fetch argument list
	va_list args;
	va_start(args, level);

	// We will only support 1024 characters
	char buffer[1024];

	// Format the string, using format
	// NB: vsprintf_s is a Windows fix (not C++ standard), use vsprintf for other systems!
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		vsnprintf_s(buffer, (1024 * sizeof(char)), format, args);
	#else
		vsnprintf(buffer, (1024 * sizeof(char)), format, args);
	#endif

	// "Clean-up" and write results to file
	va_end(args);
	LogSys::instance().write(m_owner, m_currentLevel, buffer);
}

/* Overloaded << which sets the active LogLevel. This is required for
	us to be able to set the LogLevel through the << operator. */
Logger& Logger::operator<<(const LogLevels& level){
	m_currentLevel = level;
	return *this;
}