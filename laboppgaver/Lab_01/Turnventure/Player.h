/**
 * @file: Player.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * 
 * @description: A class defining a Player object
 *				 and the various player game classes.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

/* Player Class Definition. Struct as you
   haven't learned inheritage yet. */
struct PClass
{
	int m_healthPoints; // Amount of health
	int m_damagePoints; // Amount of damage
	short m_dodges;		// Amount of possible dodges per round
};

/* Various game classes */
const PClass Wizard = { 150, 25, 2 };
const PClass Troll = { 350, 10, 1 };
const PClass Assassin = { 250, 15, 2 };

/* The Player class definition */
class Player
{
public:
	/* Constructor, creates a new player of the given class
	   NOTE: pass by reference */
	Player(const PClass&, std::string = "");

	/* Set the name of the character */
	void setName(const std::string&);

	/* Sets the amount of active dodges.
	   -1 (default) = use the class' dodge amount */
	void setDodge(int = -1);

	/* Returns the name of the character */
	const std::string& getName();

	/* Returns a const pointer to the player class */
	const PClass* getClass();

	/* Returns the amount of player's HP*/
	int getHP();

	/* Attacks the player with the specified damage */
	void attack(const int&);

	/* Returns whether or not the player successfully dodged.
	   setDodge() must be called first! */
	bool dodge();

	/* Returns whether the player is dead (HP = 0) */
	bool isDead();
private:
	std::string m_name; // Name
	int m_healthPoints; // Healt points
	int m_dodgeCounter; // Amount of remaining dodges
	const PClass* m_class; // Player class (Wizard, Troll, etc.)
};

#endif