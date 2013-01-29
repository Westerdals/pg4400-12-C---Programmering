#ifndef MINMAX_H
#define MINMAX_H

template<class T>
class MinMax
{
public:
	T min(const T& a, const T& b) const;
	T max(const T& a, const T& b) const;
};

#include "MinMax.cpp"

#endif