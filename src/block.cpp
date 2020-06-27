
#include "block.h"
#include <math.h>


void Box::on_key_press(Key key) {
	
	switch(key) {
	case Key::D:

		slide_frames = SLIDE_FRAMES;
		prev_grid_pos = grid_pos;

		grid_pos += {2, 0};
		break;

	case Key::A:

		slide_frames = SLIDE_FRAMES;

		prev_grid_pos = grid_pos;
		grid_pos += {-2, 0};
		break;

	case Key::W:

		slide_frames = SLIDE_FRAMES;
		prev_grid_pos = grid_pos;

		grid_pos += {0, -2};
		break;

	case Key::S:

		slide_frames = SLIDE_FRAMES;

		prev_grid_pos = grid_pos;
		grid_pos += {0, 2};
		break;

	default: break;
	}
}

void Box::on_tick(const float& delta) {

	prev_pos = curr_pos;

	curr_pos = game::lerp(prev_grid_pos * GRID_SIZE,
						  grid_pos * GRID_SIZE,
						  pow(1 - (slide_frames / (float)SLIDE_FRAMES), 2));

	if(slide_frames > 0) slide_frames--;

	//if(slide_frames == 1) game->cam.shake(6, 8);
}


void Box::on_lerp(float alpha) {

	this->set_pos(game::lerp(prev_pos, curr_pos, alpha));
}
