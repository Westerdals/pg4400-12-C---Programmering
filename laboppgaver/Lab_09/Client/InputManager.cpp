/**
 * @file: InputManager.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <17.04.2013>
 *
 * @description: A input manager that handles real-time user
 *				 input management. Uses the Win32 API, but
 *				 should ideally be modified to support all
 *				 platforms. SDL could do the job as well.
 */

#include "InputManager.h"

/* Returns true if there are any cached keypresses not acted upon yet. */
bool InputManager::anyKeyPressed() const
{
	return (0 != _kbhit()); // conio.h code
}

/* Returns 'false' if no key has been pressed. Else 'true', and the parameter keeps the next 
   buffered keypress (first one that hasn't been extracted or cleared in any way). */
bool InputManager::getNextKey(int* keyPressed)
{
	return getTheKey(keyPressed);
}

/* Waits for input if no key has been pressed yet. Parameter keeps the next buffered keypress
   (first one that hasn't been extracted or cleared in any way). */
bool InputManager::getNextKeyWait(int* keyPressed)
{
	return getTheKey(keyPressed, true);
}

/* Helper function doing the nitty gritty stuff. */
bool InputManager::getTheKey(int* keyPressed, const bool& wait)
{
	bool anyKeyPressed = false;
	*keyPressed = iKEY_NONE;

	if ((0 != _kbhit()) || wait)
	{
		// If wait is true and no key has been pressed,
		// execution will halt here until we get a keypress.
		int iInput = _getch();
		anyKeyPressed = true;

		if ((m_iARROWKEY_PREFIX == iInput) || (m_iFUNCTIONKEY_PREFIX == iInput))
		{
			/* NOTE: Special keys (arrow-keys and function-keys) are coded as TWO keypresses in conio.h, as they don't fit in the 
			         normal ASCII table. Thus, if the first keypress we read indicates a special key, we have to combine it with 
			         the next keypress immediately (which in reality is the 2nd part of the arrow-/function-key anyway). We then
			         translate this double-press and return our own const representing that special key to the caller. */
			iInput = _getch();
		}

		*keyPressed = iInput;
	}

	return anyKeyPressed;
}