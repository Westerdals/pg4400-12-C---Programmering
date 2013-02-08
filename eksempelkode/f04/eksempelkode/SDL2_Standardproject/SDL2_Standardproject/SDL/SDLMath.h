#ifndef SDL_MATH_H
#define SDL_MATH_H

#include <cmath>

namespace sdl
{
	template <class T>
	T round(T number)
	{
		return std::floor(number + static_cast<T>(0.5F));
	}
}

#endif