
#include "kyo/common.h"
#include "kyo/vector/vec2.h"
#include <random>
#include <ctime>
#include <math.h>


class Camera {
private:

	sf::View view;

	vec2 center = {0, 0};

	int shake_frames_max = 1;
	int shake_frames = -1;
	float shake_strength = 0;

public:
	
	Camera(): shake_frames(-1) {
		
		std::srand(std::time(nullptr));

		view.setCenter(0, 0);
		view.setSize(WIDTH, HEIGHT);

		PRINT("init " << shake_frames << "; " << shake_strength << "; " << shake_frames_max);
	}

	void set_center(const vec2& center);

	void arm(sf::RenderWindow &window);

	void shake(int frames, float strength) {
		PRINT("shaking camera");
		shake_frames_max = frames;
		shake_frames = frames;
		shake_strength = strength;
	}

	void on_tick(float dt) {
		
		if(shake_frames >= 0) {
			PRINT(shake_frames << "; " << shake_strength << "; " << shake_frames_max);
			float strength = shake_strength * shake_frames / shake_frames_max;
			float rad = std::rand()/(float)RAND_MAX * 2 * M_PI;
			float x = cos(rad) * strength;
			float y = sin(rad) * strength;
			PRINT("shake vec: [" << x << ", " << y << "] tick: " << shake_frames);
			view.setCenter(center + vec2(x, y));
			shake_frames--;
		}
	}
};
