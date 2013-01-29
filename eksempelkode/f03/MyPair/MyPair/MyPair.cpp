#ifndef MYPAIR_CPP
#define MYPAIR_CPP

#include "MyPair.h"

template <class T>
MyPair::MyPair(T a, T b) {
	m_pair[0] = a;
	m_pair[1] = b;
}

#endif