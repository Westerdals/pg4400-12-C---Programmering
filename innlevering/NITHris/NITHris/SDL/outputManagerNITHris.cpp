////////////////////////////////////////////////////////////////////////////////
//																			  //
//	File: outputManagerNITHris.cpp											  //
//																			  //
//	Original author: Tomas Sandnes / NITH / 2007-2011						  //
//	Changed by:	---															  //
//																			  //
//	Description: Takes care of graphics output (drawing tiles to the screen,  //
//				 blitting, etc.).											  //
//																			  //
//	Special notes: Requires the SDL library and previous SDL_Init call.		  //
//				   Calls, if necessary, SDL_InitSubSystem(SDL_INIT_VIDEO)	  //
//				   on use of own Init() function. (Assumes external			  //
//				   SDL_Quit() AFTER destruction of own object.)				  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

// I N C L U D E S
// ===============

#include <iostream>  // For cout, endl.
#include "../nithris.h"
#include "outputManagerNITHris.h"

using std::cout;
using std::cerr;
using std::endl;

// D E F I N E S   /   C O N S T A N T S   /   . . .
// =================================================

// (NOTE: Static globals are only visible (only have scope) in this file.)
static const unsigned short g_usTILE_PIXELWIDTH =    32;  // Tiles will be this amount of pixels large (squared).
static const unsigned short g_usWINDOW_PIXELWIDTH =  (g_usPLAYAREA_TILEWIDTH + g_usSCOREAREA_TILEWIDTH) * g_usTILE_PIXELWIDTH; // Window width in pixels.
static const unsigned short g_usWINDOW_PIXELHEIGHT = g_usGAME_TILEHEIGHT * g_usTILE_PIXELWIDTH; // Window height in pixels.
static const unsigned short g_usWINDOW_BIT_DEPTH =   16;  // Our bit depth (number of colors and such).
static const unsigned int   g_uiSDL_FLAGS =          SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;  // Flags for SDL: We're using graphic card memory (opposed to system memory).

static const char* g_pcTILE_BMP =       "Assets/gfx/tiles_32x32.bmp";      // Tiles as one bmp.
static const char* g_pcNUMBER_BMP =     "Assets/gfx/numbers_32x32.bmp";    // Scoreboard numbers as one bmp.
static const char* g_pcSTARTUP_BMP =    "Assets/gfx/startup.bmp";          // Startup (main menu) image.
static const char* g_pcGAMEOVER_BMP =   "Assets/gfx/gameover.bmp";         // Game over image.
static const char* g_pcBACKGROUND_BMP = "Assets/gfx/scoreboard_back.bmp";  // Scoreboard background image.

// P U B L I C   F U N C T I O N S
// ===============================

OutputManagerNITHris::OutputManagerNITHris()
{
	// NOTE: It's important to set the surface pointers to 0 in the constructor. 
	//       Se comments in the destructor below for more information.
	m_poWindow = NULL;
	m_poRenderer = NULL;
	m_poTileTexture = NULL;
	m_poNumberTexture = NULL;
	m_poStartupTexture = NULL;
	m_poGameOverTexture = NULL;
	m_poBackgroundTexture = NULL;

}  // END OutputManagerNITHris



OutputManagerNITHris::~OutputManagerNITHris()
{
	// Free all surfaces.
	// NOTE: It's important to set the surface pointers to 0 in the constructor. 
	//       If we fail during init (graphics in the wrong place, for example), 
	//       pointers with no content will then still be 0 when we enter the destructor to clean up, 
	//       and by checking for null-pointers here, we only free initialized stuff. 
	//       (Without null-pointers to start with, we would crash here if we failed during init.)
	if (m_poBackgroundTexture)
	{
		SDL_DestroyTexture(m_poBackgroundTexture);
		m_poBackgroundTexture = NULL;
	}
	if (m_poGameOverTexture)
	{
		SDL_DestroyTexture(m_poGameOverTexture);
		m_poGameOverTexture = NULL;
	}
	if (m_poStartupTexture)
	{
		SDL_DestroyTexture(m_poStartupTexture);
		m_poStartupTexture = NULL;
	}
	if (m_poNumberTexture)
	{
		SDL_DestroyTexture(m_poNumberTexture);
		m_poNumberTexture = NULL;
	}
	if (m_poTileTexture)
	{
		SDL_DestroyTexture(m_poTileTexture);
		m_poTileTexture = NULL;
	}
	if (m_poRenderer)
	{
		SDL_DestroyRenderer(m_poRenderer);
		m_poRenderer = NULL;
	}
	if (m_poWindow)
	{
		SDL_DestroyWindow(m_poWindow);
		m_poWindow = NULL;
	}

}  // END ~OutputManagerNITHris



bool OutputManagerNITHris::Init(const char* pcWindowTitle)
{
	bool r_bRetVal = true;

	// Initialize wanted SDL module for COutputManager (We only really need video - add other modules if you want to add sounds, etc. :-)
	if (!SDL_WasInit(SDL_INIT_VIDEO))
	{
		if (0 > SDL_Init(SDL_INIT_VIDEO))
		{
			cerr << "OutputManagerNITHris::Init - Cannot Initialize SDL Video SubSystem: " << SDL_GetError() << endl;
			r_bRetVal = false;
		}
	}

	if (r_bRetVal)
	{
		// Create a graphics output screen/window.
		m_poWindow = SDL_CreateWindow
		(
			pcWindowTitle,				// Title
			SDL_WINDOWPOS_UNDEFINED,	// x position on screen
			SDL_WINDOWPOS_UNDEFINED,	// y position on screen
			g_usWINDOW_PIXELWIDTH,		// Width
			g_usWINDOW_PIXELHEIGHT,		// Height
			g_uiSDL_FLAGS				// Flags
		);
		
		if (!m_poWindow) 
		{
			cerr << "OutputManagerNITHris::Init - Cannot create Window:" << SDL_GetError() << endl;
			r_bRetVal = false;
		}
		else
		{
			// Set up our window's renderer. Flag for hardware accelleration!
			m_poRenderer = SDL_CreateRenderer(m_poWindow, -1, SDL_RENDERER_ACCELERATED);

			if (!m_poRenderer)
			{
				cerr << "OutputManagerNITHris::Init - Cannot set up Renderer: " << SDL_GetError() << endl;
				r_bRetVal = false;
			}
			else
			{
				// Select the color for drawing. It is set to black here.
				SDL_SetRenderDrawColor(m_poRenderer, 0, 0, 0, 255);

				// Clear the entire screen to our selected color.
				SDL_RenderClear(m_poRenderer);

				// Init bitmaps. (As long as we don't get any error, we move on to the next.)
				// This is quite "old school" error handling, shoul've been exceptions.
				r_bRetVal = _LoadAndFormatBMP(&m_poTileTexture, g_pcTILE_BMP);
				if(r_bRetVal) 
				{
					r_bRetVal = _LoadAndFormatBMP(&m_poNumberTexture, g_pcNUMBER_BMP);
					if(r_bRetVal) 
					{
						r_bRetVal = _LoadAndFormatBMP(&m_poStartupTexture, g_pcSTARTUP_BMP);
						if(r_bRetVal) 
						{
							r_bRetVal = _LoadAndFormatBMP(&m_poGameOverTexture, g_pcGAMEOVER_BMP);
							if(r_bRetVal) 
							{
								r_bRetVal = _LoadAndFormatBMP(&m_poBackgroundTexture, g_pcBACKGROUND_BMP);
							}
						}
					}
				}
			}
		}
	}

	return r_bRetVal;
}  // END Init



void OutputManagerNITHris::DrawBackground() const
{
	// Paste the scoreboard background image.
	SDL_Rect oBackRect;
	oBackRect.x = g_usPLAYAREA_TILEWIDTH * g_usTILE_PIXELWIDTH;
	oBackRect.y = 0;

	// NB: THESE ARE HARDCODED VALUES. Rezising the game is thus not
	// recommended. SDL 1.2 calculated the w/h itselves, SDL 2.0 textures doesn't!
	oBackRect.h = 640;
	oBackRect.w = 256;

	SDL_RenderCopy(m_poRenderer, m_poBackgroundTexture, NULL, &oBackRect);
}  // END DrawBackground



void OutputManagerNITHris::DrawGameOverMessage() const
{
	SDL_Rect sScreenRect;  // Part of screen we want to draw to.

	sScreenRect.x = 30; 
	sScreenRect.y = 245;

	// NB: THESE ARE HARDCODED VALUES. Rezising the game is thus not
	// recommended. SDL 1.2 calculated the w/h itselves, SDL 2.0 textures doesn't!
	sScreenRect.h = 150;
	sScreenRect.w = 260;

	// Blit Game over image to the screen.
	SDL_RenderCopy(m_poRenderer, m_poGameOverTexture, NULL, &sScreenRect);
}  // END DrawGameOverMessage



void OutputManagerNITHris::DrawStartupMessage() const
{
	SDL_Rect sScreenRect;  // Part of screen we want to draw to.

	sScreenRect.x = 30; 
	sScreenRect.y = 245;

	// NB: THESE ARE HARDCODED VALUES. Rezising the game is thus not
	// recommended. SDL 1.2 calculated the w/h itselves, SDL 2.0 textures doesn't!
	sScreenRect.h = 150;
	sScreenRect.w = 260;

	// Blit Game over image to the screen.
	SDL_RenderCopy(m_poRenderer, m_poStartupTexture, NULL, &sScreenRect);
}  // END DrawStartupMessage



void OutputManagerNITHris::DrawTile(short      sPosX, 
									 short      sPosY, 
									 ETileColor eColor) const
{
	if (TC_NO_DRAW != eColor)
	{
		SDL_Rect oScreenRect;  // Part of screen we want to draw to.
		SDL_Rect oTileRect;  // Part of tileset (all tiles are stored in a single bmp, and we use a small part of it) we want to draw from.

		// Setting up where on screen we want to draw/blit.
		oScreenRect.x = sPosX * g_usTILE_PIXELWIDTH; 
		oScreenRect.y = sPosY * g_usTILE_PIXELWIDTH;
		oScreenRect.w = g_usTILE_PIXELWIDTH;
		oScreenRect.h = g_usTILE_PIXELWIDTH;

		// Setting up what part of the tile-bmp we want to use.
		oTileRect.x = eColor * g_usTILE_PIXELWIDTH;   
		oTileRect.y = 0;
		oTileRect.w = g_usTILE_PIXELWIDTH;   
		oTileRect.h = g_usTILE_PIXELWIDTH;

		// When positions are set, blit the wanted tile to the screen.
		SDL_RenderCopy(m_poRenderer, m_poTileTexture, &oTileRect, &oScreenRect);
	}
}  // END DrawTile

void OutputManagerNITHris::DrawScore(short          sPosX, 
									  short          sPosY, 
									  unsigned short usScore) const
{
	// Render the scoretext output.
	unsigned short usTempScore = usScore;
	unsigned short usDigit = 0;
	for (unsigned short usDigitSpot = 0; usDigitSpot < 4; ++usDigitSpot)
	{
		usDigit = usTempScore % 10;
		usTempScore /= 10;
		_DrawScoreDigit(sPosX + (3 - usDigitSpot), sPosY, usDigit);
	}
}  // END DrawScore



void OutputManagerNITHris::OutputGraphics() const
{
	// Redraw the entire Display.
	SDL_RenderPresent(m_poRenderer);
}  // END OutputGraphics



// P R I V A T E   F U N C T I O N S
// =================================

bool OutputManagerNITHris::_LoadAndFormatBMP(SDL_Texture** r_ppoBitmapTexture, 
											  const char*   pcBitmapName) const
{
	bool r_bRetVal = true;

	// First we load the bitmap into a temporary storage.
	SDL_Surface *poTempSurface = SDL_LoadBMP(pcBitmapName);

	if(!poTempSurface) 
	{
		cerr << "COutputManagerNITHris::Init - File not Found: " << pcBitmapName << endl;
		r_bRetVal = false;
	}
	else
	{
		// Then we convert the temporary stored bitmap to the ideal format and put it in the variable pointed to in the param list.
		// Texture is ideal as data is stored and treated on the GPU, not the CPU.
		*r_ppoBitmapTexture = SDL_CreateTextureFromSurface(m_poRenderer, poTempSurface);
		
		// Finally, we free the dynamically created temporary storage again.
		SDL_FreeSurface(poTempSurface);
	}

	return r_bRetVal;
}  // END _LoadAndFormatBMP

void OutputManagerNITHris::_DrawScoreDigit(short          sPosX, 
											short          sPosY, 
											unsigned short usDigit) const
{
	SDL_Rect oScreenRect;  // Part of screen we want to draw to.
	SDL_Rect oNumberRect;  // Part of the number-bmp-file (all numbers are stored in a single bmp, and we use a small part of it) we want to draw from.

	oScreenRect.x = sPosX * g_usTILE_PIXELWIDTH; 
	oScreenRect.y = sPosY * g_usTILE_PIXELWIDTH;
	oScreenRect.w = g_usTILE_PIXELWIDTH;
	oScreenRect.h = g_usTILE_PIXELWIDTH;

	oNumberRect.x = usDigit * g_usTILE_PIXELWIDTH;   
	oNumberRect.y = 0;
	oNumberRect.w = g_usTILE_PIXELWIDTH;   
	oNumberRect.h = g_usTILE_PIXELWIDTH;

	// When positions are set, blit the wanted tile to the screen.
	SDL_RenderCopy(m_poRenderer, m_poNumberTexture, &oNumberRect, &oScreenRect);

}  // END _DrawScoreDigit