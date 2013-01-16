/**
 * @file: Player.cpp
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * 
 * @description: A class defining a Player object
 *				 and the various player game classes.
 */

#include "Player.h"

/* Constructor, creates a new player of the given class
   NOTE: pass by reference */
Player::Player(const PClass& c, std::string name)
{
	// Set the player class, health and name
	m_class = &c;
	m_healthPoints = m_class->m_healthPoints;
	setName(name);
	m_dodgeCounter = 0; // init the dodge counter
}

/* Set the name of the character */
void Player::setName(const std::string& name)
{
	m_name = name;
}

/* Sets the amount of active dodges.
   -1 (default) = use the class' dodge amount */
void Player::setDodge(int amount)
{
	// Use the player class' amount of dodges if negative.
	if (0 > amount)
		amount = getClass()->m_dodges;

	m_dodgeCounter = amount; // Set the counter
}

/* Returns the name of the character */
const std::string& Player::getName()
{
	return m_name;
}

/* Returns a const pointer to the player class */
const PClass* Player::getClass()
{
	return m_class;
}

/* Returns the amount of player's HP*/
int Player::getHP()
{
	return m_healthPoints;
}

/* Attacks the player with the specified damage */
void Player::attack(const int& damage)
{
	// Prevent negative damage (healing)
	if (damage > 0)
	{
		// Set health to zero if damage is too wast
		if (damage > m_healthPoints)
		{
			m_healthPoints = 0;
		}
		else
		{
			m_healthPoints -= damage;
		}
	}
}

/* Return whether or not the player successfully dodged.
   setDodge() must be called first! */
bool Player::dodge()
{
	// Check if the player has any remaining dodges
	if (m_dodgeCounter > 0)
	{
		// Increase avalaible dodges, return success
		--m_dodgeCounter;
		return true;
	}

	// Failed to dodge
	return false;
}

/* Returns whether the player is dead (HP = 0) */
bool Player::isDead()
{
	return (0 == m_healthPoints);
}