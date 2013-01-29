#ifndef MYPAIR_H
#define MYPAIR_H

template <class T>
class MyPair
{
public:
	MyPair(T a, T b);
private:
	T m_pair[2];
};

//template MyPair<int>;
//template MyPair<float>;
#include "MyPair.cpp"

#endif