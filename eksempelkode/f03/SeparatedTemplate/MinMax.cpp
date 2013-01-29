#ifndef MINMAX_CPP
#define MINMAX_CPP

#include "MinMax.h"

// syntax: template<class T> RETURTYPE Klassenavn<T>::funksjon()
template<class T> T MinMax<T>::min(const T& a, const T& b) const
{
	return ((a < b) ? a : b);
}

template<class T> T MinMax<T>::max(const T& a, const T& b) const
{
	return ((a > b) ? a : b);
}

#endif