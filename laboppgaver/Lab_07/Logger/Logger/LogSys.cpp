/**
 * @file: LogSys.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <08.03.12>
 *
 * @description: A singleton class for writing log entries
 *				 to files. Required by the Logger class.
 */

#include <stdexcept>
#include <sstream>
#include <ctime>
#include <chrono>

#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>

#include "LogSys.h"

// Let's make our life a bit easier
using namespace std::chrono;
using namespace boost::property_tree;

/* Initializes the logger, reading it's configuration from the given XML file */
void LogSys::init(const std::string& configFile)
{
	// Try to fetch the data from the XML file
	std::string fileOut;

	try
	{
		// Load XML file
		ptree config;
		xml_parser::read_xml(configFile, config);

		// Retrieve the config values
		m_outputConsole = config.get<bool>("log.outputConsole", false);
		fileOut = config.get<std::string>("log.file", "log.log");
		m_separator = config.get<std::string>("log.separator", " ; ");
		m_triggerLevel = LogSys::instance().stringToLogLevels(
			config.get<std::string>("log.triggerLevel", "ERROR")
		);
	}
	catch(const ptree_error& e)
	{
		// Something with the XML config went wrong
		std::cerr
			<< "Failed to load configuration, using default values. Details: " << e.what();

		// Set default values
		m_outputConsole = false;
		fileOut = "log.log";
		m_separator = " ; ";
		m_triggerLevel = ERROR;
	}

	// Open the file I/O handler (which locks the file to this process)
	// Flags for writing and append.
	m_outputFile.open(fileOut.c_str(), std::fstream::out | std::fstream::app);

	// Check for successful open
	if (!m_outputFile)
	{
		std::stringstream message;
		message << "Failed to init Log System, unable to open or create file \""
			<< fileOut << "\"." << std::endl;

		throw std::runtime_error(message.str());
	}
}

/* Writes the given log entry to file if the LogLevel is within the trigger level.
   Time solution partly fetched from: http://goo.gl/Bo8T9 */
void LogSys::write(const std::string& source, const LogLevels& level, const std::string& message)
{
	// Confirm the trigger level
	if (level < m_triggerLevel)
	{
		return;
	}

	// Fetch current time as time stamp
	high_resolution_clock::time_point now = high_resolution_clock::now();

	// Get milliseconds and seconds by cast
	milliseconds ms = duration_cast<milliseconds>(now.time_since_epoch());
	seconds s = duration_cast<seconds>(ms);

	// Get milliseconds (fractional seconds) and convert seconds to a time_t for time formatting
	std::size_t fractional_seconds = ms.count() % 1000;
	std::time_t msTime = s.count();
	
	// Variables to be used for time string formatting
	char timeBuffer[21];
	tm timeinfo;

	// Populate timeinfo with proper data.
	// NB: localtime_s is a Windows fix, use localtime for other systems!
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		localtime_s(&timeinfo, &msTime);
	#else
		timeinfo = *localtime(&msTime);
	#endif
	
	// Format string
	strftime(timeBuffer, 21, "%d.%m.%Y %H:%M:%S", &timeinfo);

	// Generate complete output with timestamp and message
	std::stringstream output;
	output << timeBuffer << ":" << fractional_seconds << m_separator
		<< LogLevelsTxt[level] << m_separator << message << std::endl;

	// Add message to file
	m_outputFile << output.str();

	// Print eventually to console (should only be used in debug)
	if (m_outputConsole)
	{
		std::cout << output.str();
	}
}

/* Helper function to get the string version of the log levels */
LogLevels LogSys::stringToLogLevels(const std::string& level)
{
	// Loop through the array, look for matches
	for (int i = 0; i < 4; ++i)
	{
		if (LogLevelsTxt[i] == level)
		{
			return static_cast<LogLevels>(i);
		}
	}

	// No match found, return default.
	return ERROR;
}

/* Constructor, calls the init function with the given XML file. */
LogSys::LogSys()
{
	init("Logger/LogConfig.xml");
}

/* Destructor, closes the file IO handler. */
LogSys::~LogSys()
{
	m_outputFile.close();
}