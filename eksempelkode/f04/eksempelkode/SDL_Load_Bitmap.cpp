#include <iostream>
#include <SDL.h>

// NB: Denne koden tar seg IKKE av noen feilhåndering
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
	// NB: denne koden "bygger på" forrige eksempel!
	SDL_Renderer* renderer; // Pointer to window's renderer
	
	// Lag en renderer til det spesifikke vinduet. Setter Hardware accelerated flag.
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	// Sjekk om noe gikk galt
	if (renderer == NULL)
	{
		std::cerr << "Failed to create renderer: "
				  << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window); SDL_Quit(); // rydd opp
		return EXIT_FAILURE;
	}

	// Set renderens bakgrunnsfarge til svart
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer); // Nullstiller renderen (til svart)

	// Last inn et bilde fra disk (NB: støtter KUN BMP!)
	SDL_Surface* surface = SDL_LoadBMP("my_picture.bmp");

	// Sjekk for feil
	if (surface == NULL)
	{
		std::cerr << "Failed to load image: "
				  << SDL_GetError() << std::endl;
		SDL_DestroyRenderer(renderer); SDL_DestroyWindow(window); SDL_Quit(); // rydd opp
		return EXIT_FAILURE;
	}

	// Konverter surface om til et HW Accelerated Texture, laster objektet opp på skjermkortet
	SDL_Texture* drawable = SDL_CreateTextureFromSurface(renderer, surface);

	// Sett opp et "koordinatsystem" for bildet
	SDL_Rect coords;
	coords.h = surface->h; // Samme bredde og høyde som surface
	coords.w = surface->w;
	coords.x = 0; // Endre disse for å "flytte" bildet i vinduet/renderer
	coords.y = 0;

	SDL_FreeSurface(surface); // Frigjør surface fra CPU-minnet

	/* GAME LOOP START */
		// Endre koordinatene ved brukerinput (coords.x, coords.y
	
		// Legg til objektet i vinduets renderer
		SDL_RenderCopy(renderer, drawable, NULL, &coords);
		
		// BLIT/rendre bildet
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer); // Tøm renderen for innhold
	/* GAME LOOP SLUTT */

	// Pause i 3 sekunder, lukk vinduet
	SDL_Delay(3000);
	SDL_DestroyWindow(window);

	SDL_Quit(); // Be SDL om å rydde opp
	return EXIT_SUCCESS;
}