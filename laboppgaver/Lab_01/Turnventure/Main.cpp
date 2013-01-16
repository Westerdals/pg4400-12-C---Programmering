/**
 * @file: Main.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * @version: 1.0.0 <16.01.2013>
 *
 * @description: A turn based console "RPG" with
 *				 a dynamic amount of players. This
 *				 file is the main entry point of the
 *				 game; launches a game instance.
 */
#include "GameObject.h"

/** Launch the game through the Singleton object */
int main(int argc, ...)
{
	GameObject::Instance().run();
	return 0;
}