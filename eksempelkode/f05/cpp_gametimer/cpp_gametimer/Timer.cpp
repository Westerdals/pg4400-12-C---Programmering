#include "Timer.h"

Timer::Timer() : m_startTick(hr_clock::now())
{
	m_currentTick = m_startTick;
	m_lastTick = m_startTick;
	m_deltaTime = 0.0F;
}

void Timer::update()
{
	m_lastTick = m_currentTick;
	m_currentTick = hr_clock::now();

	milliseconds delta_ms = std::chrono::duration_cast<milliseconds>(m_currentTick - m_lastTick);
	m_deltaTime = static_cast<float>(delta_ms.count()) / 1000.F;
}

const float& Timer::deltaTime() const
{
	return m_deltaTime;
}

float Timer::elapsedTime() const
{
	milliseconds elapsed_ms = std::chrono::duration_cast<milliseconds>(m_currentTick - m_startTick);
	return (static_cast<float>(elapsed_ms.count()) / 1000.F);
}