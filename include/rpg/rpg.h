
#pragma once

#include "kyo/common.h"
#include "kyo/entity/manager.h"
#include "kyo/game.h"
#include "camera.h"
#include <deque>

class Character;
class Enemy;

class RPGGame: public Game {
private:

    EntityManager em_scene, em_hud;

	std::deque<string> con_log;

	Character* ch;

    sf::Font font;

    sf::Text *text_info, *text_legend, *text_status;

	Enemy *enemy1, *enemy2, *enemy3;

public:

	Camera cam_scene, cam_hud;

	RPGGame();

	void push_console_message(string msg);

	string get_console_string();

    void on_run();

    void key_press(Key key);

    void on_render(sf::RenderWindow* window);

    void on_tick(const float& delta);

	void attack_enemy(int n);

	sf::Font& get_font() { return font; }
};

