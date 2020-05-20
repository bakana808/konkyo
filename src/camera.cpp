
#include "camera.h"


void Camera::arm(sf::RenderWindow &window) {
	
	window.setView(view);
}


void Camera::set_center(const vec2& center) {
	
	this->center = center;
}
