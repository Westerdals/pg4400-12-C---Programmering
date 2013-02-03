#include <SDL.h>

int main(int argc, char* argv[])
{
	bool gameNotOver = true;

	// Variabler til å holde pekere til key states
	Uint8* keys = NULL;
	int numKeys; // Antall keys varierer fra system til system

	// Initialiser key state-pekeren
	keys = SDL_GetKeyboardState(&numKeys);

	while (gameNotOver)
	{
		// Oppdater key state-arrayen
		SDL_PumpEvents();

		// Sjekk om brukeren har trykket Escape
		if (keys[SDL_SCANCODE_ESCAPE] != 0)
		{
			gameNotOver = false; // Avslutt
		}

		// Sjekk om brukeren har krysset ut (X) vinduet
		if (SDL_HasEvent(SDL_QUIT))
		{
			gameNotOver = false; // Avslutt
		}
	}
}