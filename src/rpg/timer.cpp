
#include "rpg/timer.h"
#include <math.h>

Timer::Timer() {
	
	bar = spawn_entity<sf::RectangleShape>();
	bar->setSize({16, 64});
	bar->setFillColor(sf::Color::White);
	bar->setPosition(-400, -300);

	left = spawn_entity<sf::RectangleShape>();
	left->setSize({16, 64});
	left->setFillColor(sf::Color::White);
	left->setPosition(-400, -300);

	right = spawn_entity<sf::RectangleShape>();
	right->setSize({16, 64});
	right->setFillColor(sf::Color::White);
	right->setPosition(400, -300);
};

void Timer::on_tick(const float& delta) {
	
	vec2 start(-400, -300), end(400, -300);

	float alpha = tick / (float)ROUND_TICKS;

	if(alpha < 0.5) {
		
		bar->setPosition(game::lerp(start, end, pow(alpha*2, 1)));
	}
	else {
		
		bar->setPosition(game::lerp(end, start, pow((alpha-0.5)*2, 1)));
	}

	tick = (tick + 1) % ROUND_TICKS;
}

