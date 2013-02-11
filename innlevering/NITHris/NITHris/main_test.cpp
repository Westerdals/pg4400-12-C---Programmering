////////////////////////////////////////////////////////////////////////////////
//																			  //
//	File: main_test.cpp														  //
//																			  //
//	Original author: Tomas Sandnes / NITH / 2008-2011						  //
//	Changed by:	Stig M. Halvorsen / NITH / 2013								  //
//																			  //
//	Description: The "wrapper" (for windows) to call our gameManager.		  //
//																			  //
//	Special notes: Loads (on starup) and removes (on exit) the SDL2			  //
//				   dll from	memory.											  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

/** THIS MAIN IS FOR TESTING SDL2 ONLY - DO NOT USE IT LIKE THIS IN THE GAME! **/ 

// I N C L U D E S
// ===============

#include <iostream>  // To use cout & endl for debug output.
#include <SDL.h>  // To use (init) SDL2 itself.
#include "SDL/outputManagerNITHris.h"  
#include "SDL/loopTimerSDL.h"
#include "SDL/InputManagerSDL.h"

using std::endl;
using std::cerr;

// E N T R Y   P O I N T
// =====================

// Note to students: There's three ways of calling main in windows. One with a defined parameters,
//                   one with multiple parameters (...), and one without parameters. SDL requires us to
//					 use the variation with a defined parameter list, even if we don't use it. So we do.
//					 (Hence the argc & argv parameters. :-)
int main( int argc,		  // Number of arguments passed. (NOTE: application itself counts as 1st argument.)
		  char* argv[] )  // The arguments themselves, as pointers to c-strings (char arrays).
{
	if (0 > SDL_Init(SDL_INIT_VIDEO))
	{
		// You should probably implement a more C++ friendly implementation with classes and exceptions.
		cerr << "main - Cannot Initialize SDL: " << SDL_GetError() << endl;
	}
	else
	{
		// Note: WHY these extra curly braces? To make sure any objects we create inside 
		//       these are removed again BEFORE we do the SDL_Quit() a little further down.
		{

			/** AGAIN : THIS MAIN IS FOR TESTING SDL2 ONLY - DO NOT USE IT LIKE THIS IN THE GAME! **/ 

			OutputManagerNITHris oOutputManager;  
			if (oOutputManager.Init("MyTestWindow"))  
			{
				/* Test of outputmanager */
				
				// Test of static images
				oOutputManager.DrawBackground();
				oOutputManager.DrawStartupMessage();
				
				// Test of tiles
				for (int i = 2; i < 6; ++i)
					oOutputManager.DrawTile(5, i, TC_RED);

				// Test of score
				oOutputManager.DrawScore(8, 5, 1000);

				// Render
				oOutputManager.OutputGraphics();

				/* Test of timer (2FPS) */
				LoopTimer lt(2);
				lt.Start();
				int count = 0;

				while (true)
				{
					lt.SleepUntilUpdate();
					if (count > 5)
						break;
					// Alternative to sleep: CPU consuming constant loop
					//if (lt.IsTimeForUpdate())
					//{
						std::cout << "Update (" << count++ << ")" << std::endl; 
					//}
				}

				/* Test of inputManager */
				std::cout << "Press [Esc] or close window to exit!" << std::endl;
				LoopTimer inputTimer(1000);
				inputTimer.Start();

				while(true)
				{
					inputTimer.SleepUntilUpdate();
					InputManagerSDL::Instance().Update();

					if (InputManagerSDL::Instance().KeyDown(SDL_SCANCODE_ESCAPE) ||
						InputManagerSDL::Instance().userExit())
					{
						break;
					}

					if (InputManagerSDL::Instance().KeyDown(SDL_SCANCODE_LEFT))
					{
						std::cout << "<-" << std::endl;
					}

					if (InputManagerSDL::Instance().KeyDown(SDL_SCANCODE_RIGHT))
					{
						std::cout << "->" << std::endl;
					}

					if (InputManagerSDL::Instance().MouseDown(SDL_BUTTON_LEFT))
					{
						std::cout << "(-_(-_(-_(-_-)_-)_-)_-)" << std::endl;
					}
				}
			}
		}

		// If we managed to init SDL (which means loading the SDL dll), quit (remove it) again before application exit.
		SDL_Quit();  
	}

	return EXIT_SUCCESS;  // Ok.
}  // END main