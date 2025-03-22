#ifndef GAME_H
#define GAME_H

#include "../../engine/GameEngine.h"

class Game : public GameEngine
{
protected:
	virtual void update_systems() override;
	virtual void update_debug_window() override;
};

#endif

