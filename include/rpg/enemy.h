
#include "kyo/entity/composite.h"

class Enemy: public CompositeEntity {
private:

	sf::Text *txt_status;

	float health = 500.f;

public:

	Enemy();

	void on_tick(const float& dt) override;
};
