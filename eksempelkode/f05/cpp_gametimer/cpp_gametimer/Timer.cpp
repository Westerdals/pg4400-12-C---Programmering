/**
 * @file: Timer.cpp
 * @author: Stig M. Halvorsen
 * @version: 1.0.0 <09.02.2013>
 *
 * @description: A Singleton DeltaTime class, using C++11's high_resolution_clock.
 *				 Tracks time between loops and total runtime of application.
 */

#include "Timer.h"

/* Initializes and kicks off the timers, sets initials start values. */
Timer::Timer() : m_startTick(hr_clock::now())
{
	m_currentTick = m_startTick;
	m_lastTick = m_startTick;
	m_deltaTime = 0.0F;
}

/* Updates the timers, including the DeltaTime value */
void Timer::update()
{
	// Update member values
	m_lastTick = m_currentTick;
	m_currentTick = hr_clock::now();

	// Calculate new deltatime, cast to float in seconds.
	milliseconds delta_ms = std::chrono::duration_cast<milliseconds>(m_currentTick - m_lastTick);
	m_deltaTime = static_cast<float>(delta_ms.count()) / 1000.F;
}

/* Returns current delta time in seconds using pass-by-reference. */
const float& Timer::deltaTime() const
{
	return m_deltaTime;
}

/* Return total runtime since init() in seconds */
float Timer::elapsedTime() const
{
	milliseconds elapsed_ms = std::chrono::duration_cast<milliseconds>(m_currentTick - m_startTick);
	return (static_cast<float>(elapsed_ms.count()) / 1000.F);
}