#include <SDL.h>

int main(int argc, char* argv[])
{
	bool gameNotOver = true;
	SDL_Event event; // Lag et event-objekt

	while (gameNotOver)
	{
		// Sjekk om en event har oppstått
		if (SDL_PollEvent(&event))
		{
			// Sjekk om det var en key-event
			if (event.type == SDL_KEYDOWN)
			{
				// Sjekk om brukeren trykket Escape
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					gameNotOver = false; // avslutt
				}
			}
			// Sjekk om brukeren trykket krysset (X) i vindu
			else if (event.type == SDL_QUIT)
			{
				gameNotOver = false; // avslutt
			}
		}
	}
}