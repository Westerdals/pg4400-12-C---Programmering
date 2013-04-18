/**
 * @file: Global.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <03.04.2013> 
 *
 * @description: Includes and definitions to make
 *				 the Main program shorter (code).
 */

#ifndef GLOBAL_H // inclusion guard
#define GLOBAL_H

#include <iostream>
#include <array>
#include <chrono>

using std::cout;
using std::endl;
using std::array;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

typedef high_resolution_clock::time_point time_point;

// Prototype functions
long long f(long long);
long long myFunction1(int);

#endif // end inclusion guard