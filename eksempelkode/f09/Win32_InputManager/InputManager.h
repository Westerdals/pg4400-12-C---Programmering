#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#ifdef WIN32
	/* This is Windows only, for UNIX
	   check: Curses and NCurses */
	#include <conio.h>
#else
	// Check documentation of curses!
	// Perhaps: #include <curses.h>?
#endif

#include "InputKeys.h"

class InputManager
{
public:
	/* Returns true if there are any cached keypresses not acted upon yet. */
	bool anyKeyPressed() const;

	/* Returns 'false' if no key has been pressed. Else 'true', and the parameter keeps the next 
	   buffered keypress (first one that hasn't been extracted or cleared in any way). */
	bool getNextKey(int* keyPressed);

	/* Waits for input if no key has been pressed yet. Parameter keeps the next buffered keypress
	   (first one that hasn't been extracted or cleared in any way). */
	bool getNextKeyWait(int* keyPressed);
private:
	/* Helper function doing the nitty gritty stuff. */
	bool getTheKey(int* keyPressed, const bool& wait = false);
};

#endif