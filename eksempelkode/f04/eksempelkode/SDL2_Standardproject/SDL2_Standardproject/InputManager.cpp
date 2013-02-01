#include "InputManager.h"

InputManager::InputManager()
{
	m_keys = NULL;
	m_oldKeys = NULL;
	m_keyCount = NULL;
	m_mouseButtons = NULL;
	m_oldMouseButtons = NULL;
	m_mouseX = NULL;
	m_mouseY = NULL;

	// Creating an array for the current state is taken care of by SDL, so we just get ourselves a 
	// pointer to it. (Array will be deleted by SDL on app exit, so we can forget all about it.)
	m_keys = SDL_GetKeyboardState(&m_keyCount);

	// Allocate sufficent memory for the old keys array
	m_oldKeys = std::unique_ptr<Uint8>(new Uint8[m_keyCount]);

	// Copy over the key states
	memcpy(m_oldKeys.get(), m_keys, m_keyCount * sizeof(Uint8));

	// Pumping twice, to flush any pending keypresses.
	SDL_PumpEvents();
	SDL_PumpEvents();
}

void InputManager::Update()
{
	// Setting "old" states equal to those aquired on last Update().
	m_oldMouseButtons = m_mouseButtons;
	memcpy(m_oldKeys.get(), m_keys, m_keyCount * sizeof(Uint8));

	// Pumping events, meaning we update SDL's input states to match current inputs.
	SDL_PumpEvents();  // Key changes gets updated automatically, as we hold a pointer to SDL's internal key array.
	m_mouseButtons = SDL_GetRelativeMouseState(&m_mouseX, &m_mouseY);  // Mouse updates we must fetch manually.
}