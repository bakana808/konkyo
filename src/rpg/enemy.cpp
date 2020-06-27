
#include "rpg/enemy.h"
#include "rpg/rpg.h"


Enemy::Enemy(RPGGame *game): game(game) {
	
	txt_status = spawn_entity<sf::Text>();
	txt_status->setFont(game->get_font());
	txt_status->setCharacterSize(14);
}


void Enemy::on_tick(const float& dt) {
	
	ticks++;

	txt_status->setPosition(this->get_pos());
	txt_status->setString("HP: " + STR(get_health()));
}

void Enemy::hurt(float damage) {
	
	health -= damage;
}

float Enemy::get_health() {
	
	return health - (ticks * game->get_tickrate());
}
