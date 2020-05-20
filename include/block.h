
#include "kyo/entity/object.h"
#include "kyo/vector/vec2.h"

#define GRID_SIZE 64
#define SLIDE_FRAMES 10

class TestGame;

class Box: public GameObject<sf::RectangleShape> {
public:

	vec2 prev_pos, curr_pos;

	int slide_frames = 0;
	vec2 prev_grid_pos, grid_pos;

	TestGame *game;

    Box(TestGame *game): game(game) {

        handle->setSize({64, 64});
        handle->setFillColor(sf::Color::White);

		prev_pos = get_pos();
    }

	void key_press(Key key);

    void on_tick(const float& delta) override;

	void on_lerp(float t) override;
};

