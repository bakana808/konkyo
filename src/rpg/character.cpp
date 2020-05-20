
#include "rpg/character.h"
#include "rpg/rpg.h"


Character::Character(RPGGame *game): game(game) {}

void Character::end_turn() {
	
	state = MAIN;
}

void Character::key_press(Key key) {
	
	switch(state) {

		case MAIN:

			switch(key) {
			case Key::Right:
				state = ATTACK;
				break;

			case Key::Up:
				state = ITEM;
				break;

			case Key::Down:
				state = DEFEND;
				break;

			default: break;
			}
			break;

		case ATTACK: {

			int n = -1;

			switch(key) {
			case Key::Up:
				n = 0; break;

			case Key::Right:
				n = 1; break;

			case Key::Down:
				n = 2; break;

			default: break;
			}

			if(n >= 0) {
				game->attack_enemy(n);
				this->end_turn();
			}
		}

		default: break;
	}
}
