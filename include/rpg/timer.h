
#include "kyo/common.h"
#include "kyo/entity/composite.h"

#define ROUND_TICKS 120

class Timer: public CompositeEntity {
private:
	
	int tick = 0;

	sf::RectangleShape *bar, *left, *right;

public:

	Timer();

	void on_tick(const float& delta) override;
};



