
#include "kyo/entity/composite.h"

class RPGGame;

class Enemy: public CompositeEntity {
private:

	sf::Text *txt_status;

	RPGGame *game;

	int ticks = 0;
	float health = 500.f;

public:

	Enemy(RPGGame *game);

	void on_tick(const float& dt) override;

	void hurt(float damage);

	float get_health();
};
