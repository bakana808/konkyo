
#pragma once

#include "kyo/entity/controllable.h"

class RPGGame;

enum MenuState {
	MAIN = 0,
	ATTACK,
	ITEM,
	DEFEND
};

class Character: public ControllableEntity {
private:

	RPGGame *game;

	MenuState state = MAIN;

public:


	Character(RPGGame *game);

	void key_press(Key key) override;

	void end_turn();

	const MenuState& get_state() { return state; }
};
