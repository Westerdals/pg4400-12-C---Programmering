#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <memory>
#include <SDL.h>

class InputManager
{
public:
	static InputManager& Instance()
	{
		static InputManager iM;
		return iM;
	}

	void Update();

	// Keyboard functions.
	bool KeyDown(int keyIndex) const		 { return (CurKeyDown(keyIndex)) && (!OldKeyDown(keyIndex)); }
	bool KeyStillDown(int keyIndex) const { return (CurKeyDown(keyIndex)) && ( OldKeyDown(keyIndex)); }
	bool KeyUp(int keyIndex) const		 { return (!CurKeyDown(keyIndex)) && (OldKeyDown(keyIndex)); }
	bool KeyStillUp(int keyIndex) const	 { return (!CurKeyDown(keyIndex)) && (!OldKeyDown(keyIndex)); }

	// Mouse functions.
	bool MouseDown(int button)		{ return ( CurMouseDown(button))&&(!OldMouseDown(button)); }
	bool MouseStillDown(int button)	{ return ( CurMouseDown(button))&&( OldMouseDown(button)); }
	bool MouseUp(int button)		{ return (!CurMouseDown(button))&&( OldMouseDown(button)); }
	bool MouseStillUp(int button)	{ return (!CurMouseDown(button))&&(!OldMouseDown(button)); }
protected:
	// Helper functions to make things easier.
	bool CurKeyDown(const int& keyIndex) const { return (m_keys[keyIndex] != 0); }
	bool OldKeyDown(const int& keyIndex) const { return (m_oldKeys.get()[keyIndex] != 0); }
	bool CurMouseDown(const int& button) const { return (m_mouseButtons & SDL_BUTTON(button)) != 0; }
	bool OldMouseDown(const int& button) const { return (m_oldMouseButtons & SDL_BUTTON(button)) != 0; }

	Uint8* m_keys;    // A pointer to SDL's internal key state array. (Memory handled by SDL.)
	std::unique_ptr<Uint8> m_oldKeys; // Our own copy of last update's array. NB! Memory handled dynamically by us!
	int m_keyCount;  // Number of keys in the arrays above, for this application. (Can vary depending on setup/hardware.)

	int m_mouseX; // Mouse pos x.
	int m_mouseY; // Mouse pos y.
	Uint8 m_mouseButtons; // Mouse buttons clicked
	Uint8 m_oldMouseButtons; // Mouse buttons clicked last update
private:
	InputManager(); // Hidden constructor
	InputManager(const InputManager&); // Hidden copy constructor
	InputManager& operator=(const InputManager&); // Hidden assign operator
};

#endif