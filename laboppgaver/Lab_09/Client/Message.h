#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <chrono>

typedef std::chrono::high_resolution_clock::time_point time_point;

class Message
{
public:
	std::string sender;
	std::string message;
	time_point timestamp;
};

#endif