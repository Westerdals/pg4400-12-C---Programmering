/**
 * @file: LogSys.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <08.03.12>
 *
 * @description: A singleton class for writing log entries
 *				 to files. Required by the Logger class.
 */

#ifndef LOGSYS_H
#define LOGSYS_H

#include <string>
#include <array>
#include <fstream>

// Define the various supported log levels
static enum LogLevels
{
	INFO, WARN, ERROR, CRITICAL
};

// Log levels as strings
static std::array<std::string, 4> LogLevelsTxt =
{
	"INFO", "WARN", "ERROR", "CRITICAL"
};

class LogSys
{
public:
	/* Standard Meyer's singleton instance function to access the object */
	static LogSys& instance()
	{
		static LogSys log;
		return log;
	}

	/* Initializes the logger, reading it's configuration from the given XML file */
	void init(const std::string& configFile);

	/* Writes the given log entry to file if the LogLevel is within the trigger level. */
	void write(const std::string& source, const LogLevels& level, const std::string& message);

	/* Helper function to get the string version of the log levels */
	LogLevels stringToLogLevels(const std::string&);
private:
	LogSys(); // Hidden constructor
	~LogSys(); // Hidden deconstructor
	LogSys(const LogSys&); // Hidden copy constructor
	LogSys& operator=(const LogSys&); // Hidden assign operator

	bool m_outputConsole; // Whether we should output to console
	std::fstream m_outputFile; // File IO handler
	std::string m_separator; // Separates info in a log message
	LogLevels m_triggerLevel; // Trigger level
};

#endif