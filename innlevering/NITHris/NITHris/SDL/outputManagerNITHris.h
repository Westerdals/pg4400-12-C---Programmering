////////////////////////////////////////////////////////////////////////////////
//																			  //
//	File: outputManagerNITHris.h											  //
//																			  //
//	Original author: Tomas Sandnes / NITH / 2007-2011						  //
//	Changed by:	Stig M. Halvorsen / NITH / 2013								  //
//																			  //
//	Description: Takes care of graphics output (drawing tiles to the screen,  //
//				 blitting, etc.).											  //
//																			  //
//	Special notes: Requires the SDL2 library and previous SDL_Init call.	  //
//				   Calls, if necessary, SDL_InitSubSystem(SDL_INIT_VIDEO)	  //
//				   on use of own Init() function. (Assumes external			  //
//				   SDL_Quit() AFTER destruction of own object.)				  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

#ifndef OUTPUTMANAGERNITHRIS_H  // Inclusion guard.
#define OUTPUTMANAGERNITHRIS_H

// I N C L U D E S
// ===============

#include <SDL.h>
#include "../nithris.h"

// C L A S S   D E C L A R A T I O N
// =================================

class OutputManagerNITHris
{
public:
	/* Constructor */
	OutputManagerNITHris();

	/* Destructor */
	~OutputManagerNITHris();

	/* Initialize needed SDL subsystems and application window stuff. */
	bool Init(const char* pcWindowTitle);

	/* Blits the scorearea background image. */
	void DrawBackground() const;  

	/* Blits the game over "window" onto the gamearea. */
	void DrawGameOverMessage() const;

	/* Blits the startup "window" onto the gamearea. */
	void DrawStartupMessage() const;

	/* Function to blit a tile. (At the position and with the color specified.) */
	void DrawTile(short sPosX,
				  short sPosY,
				  ETileColor eColor) const;

	/* Function to blit a 4-digit score. (At the position and with the value specified.) */
	void DrawScore(short sPosX, 
				   short sPosY, 
				   unsigned short usScore) const;

	/* Updates what we see on screen with any newly blitted changes. (Flips current visual buffer and current update buffer.) */
	void OutputGraphics() const;
private:
	/* Helper function to load and optimize graphics.
	 * Note to Students: This function has a "double pointer" as the first parameter! 
	 *                   This was explained in the lecture when the game was announced. */
	bool _LoadAndFormatBMP(SDL_Texture** ppoBitmapTexture, 
						   const char* pcBitmapName) const;

	/* Helper function to draw a single digit. */
	void _DrawScoreDigit(short sPosX, 
						 short sPosY, 
						 unsigned short usDigit) const;

	SDL_Window* m_poWindow;			     // Our output/window surface. This is the one we Blit the others to.
	SDL_Renderer* m_poRenderer;			 // Our window's renderer. Used to draw graphics.
	SDL_Texture* m_poTileTexture;        // Surface containing tile graphics.
	SDL_Texture* m_poNumberTexture;      // Surface containing digit/number graphics (text-as-bitmap).
	SDL_Texture* m_poStartupTexture;     // Surface containing startup image.
	SDL_Texture* m_poGameOverTexture;    // Surface containing game over image.
	SDL_Texture* m_poBackgroundTexture;  // Surface containing scoreboard background image.

};  // END class OutputManagerNITHris



#endif  // OUTPUTMANAGERNITHRIS_H