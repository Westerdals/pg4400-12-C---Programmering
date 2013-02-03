#include <iostream>
#include <SDL.h>

// NB: Denne koden tar seg IKKE av noen feilhåndering ved init.
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO); // Init. SDL2
	SDL_Window* window = NULL; // Pointer to Window

	// Lag et vindu med gitte settings
	window = SDL_CreateWindow ( 
		"Et awesome SDL2-vindu!",          //    window title
		SDL_WINDOWPOS_UNDEFINED,           //    initial x position
		SDL_WINDOWPOS_UNDEFINED,           //    initial y position
		550,                               //    width, in pixels
		400,                               //    height, in pixels
		SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL //    flags
	);
	// For alle mulige konfigurasjonsalternativer, se: http://goo.gl/8vDJN

	// Sjekk om noe gikk galt
	if (window == NULL)
	{
		std::cerr << "Failed to create window: "
				  << SDL_GetError() << std::endl;
		SDL_Quit(); // Rydd opp!
		return EXIT_FAILURE;
	}

	// Pause i 3 sekunder, lukk vinduet
	SDL_Delay(3000);
	SDL_DestroyWindow(window);

	SDL_Quit(); // Be SDL om å rydde opp
	return EXIT_SUCCESS;
}