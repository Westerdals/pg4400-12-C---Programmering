#ifndef GAMEACTION_H
#define GAMEACTION_H

#include "Player.h"

enum e_Action {
	e_noAction,
	e_attack,
	e_dodge
};

class GameAction
{
public:
	Player* m_caller;
	Player* m_target;
	e_Action m_action;
};

#endif