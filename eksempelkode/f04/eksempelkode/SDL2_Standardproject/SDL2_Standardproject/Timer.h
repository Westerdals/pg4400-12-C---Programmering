#ifndef TIMER_H
#define TIMER_H

#include <chrono>

typedef std::chrono::milliseconds milliseconds;
typedef std::chrono::high_resolution_clock hr_clock;
typedef hr_clock::time_point time_point;
typedef hr_clock::duration duration;

class Timer
{
public:
	static Timer& Instance() {
		static Timer t;
		return t;
	}

	inline void init() {};
	void update();
	const float& deltaTime() const;
	float elapsedTime() const;
private:
	Timer();
	Timer(const Timer&);
	Timer& operator=(const Timer&);

	const time_point m_startTick;
	time_point m_currentTick;
	time_point m_lastTick;
	float m_deltaTime;
};

#endif