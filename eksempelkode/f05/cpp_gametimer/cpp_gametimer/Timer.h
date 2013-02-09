/**
 * @file: Timer.h
 * @author: Stig M. Halvorsen
 * @version: 1.0.0 <09.02.2013>
 *
 * @description: A Singleton DeltaTime class, using C++11's high_resolution_clock.
 *				 Tracks time between loops and total runtime of application.
 */

#ifndef TIMER_H
#define TIMER_H

#include <chrono> // Include the C++11 Timer library

// Typedefs of long declarations for simplicity
typedef std::chrono::milliseconds milliseconds;
typedef std::chrono::high_resolution_clock hr_clock;
typedef hr_clock::time_point time_point;
typedef hr_clock::duration duration;

class Timer
{
public:
	/* Standard Meyer's singleton DeltaTime function. Use
	   it to access the object. */
	static Timer& Instance() {
		static Timer t;
		return t;
	}

	/* Initializes and kicks off the timers, sets initials start values.
	   This is not done by the function itselves, but a call to this function
	   triggers the Constructor performing this tasks! */
	inline void init() {};

	/* Updates the timers, including the DeltaTime value */
	void update();

	/* Returns current delta time in seconds using pass-by-reference. */
	const float& deltaTime() const;

	/* Return total runtime since init() in seconds */
	float elapsedTime() const;
private:
	Timer(); // Hidden constructor (Singleton)
	Timer(const Timer&); // Hidden copy constructor
	Timer& operator=(const Timer&); // Hidden assignment operator

	const time_point m_startTick; // Holds timestamp on program init()
	time_point m_currentTick; // Holds current timestamp
	time_point m_lastTick; // Holds last update's timestamp
	float m_deltaTime; // Holds the current deltatime
};

#endif