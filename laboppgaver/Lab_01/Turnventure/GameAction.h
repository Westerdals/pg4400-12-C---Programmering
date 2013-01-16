/**
 * @file: GameAction.h
 * @author: Stig M. Halvorsen <halsti@nith.no>
 * 
 * @description: An object to hold information on player actions.
 *				 NOTE: only a h-file.
 */

#ifndef GAMEACTION_H
#define GAMEACTION_H

#include "Player.h"

/* Various player actions */
enum e_Action {
	e_noAction,
	e_attack,
	e_dodge
};

/* Class definition */
class GameAction
{
public:
	/* Constructor. Declares safe member values. */
	GameAction() {
		m_caller = m_target = 0;
		m_action = e_noAction;
	}

	Player* m_caller;  // Player object calling the action
	Player* m_target;  // Potential player target
	e_Action m_action; // The specified action
};

#endif