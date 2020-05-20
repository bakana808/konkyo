
#include "rpg/rpg.h"
#include "rpg/timer.h"
#include "rpg/character.h"

void RPGGame::on_run() {
	
	font.loadFromFile("FiraCode-VF.ttf");

	text_info = em_hud.spawn_entity<sf::Text>();
	text_info->setFont(font);
	text_info->setCharacterSize(14);
	text_info->setPosition(-600, -300);

	text_legend = em_hud.spawn_entity<sf::Text>();
	text_legend->setFont(font);
	text_legend->setCharacterSize(14);
	text_legend->setPosition(-300, 100);

	ch = em_scene.spawn_entity<Character>(this);

	em_hud.spawn_entity<Timer>();

	this->set_tickrate(60);
}

void RPGGame::key_press(Key key) {
	
	switch(key) {
	case Key::Escape:
		this->close(); break;

	case Key::Space:
		push_console_message("Hello !"); break;

	case Key::Return:
		push_console_message("Enter"); break;

	default: break;
	}

	ch->key_press(key);
}

void RPGGame::push_console_message(string msg) {
	
	con_log.push_back(msg);

	if(con_log.size() > 16) {
		con_log.pop_front();
	}
}

string RPGGame::get_console_string() {
	
	string lines = "";

	for(string msg: con_log)
		lines += msg + "\n";

	return lines;
}

void RPGGame::on_tick(const float& delta) {

	em_scene.on_tick(delta);
	em_hud.on_tick(delta);
	cam_scene.on_tick(delta);
	cam_hud.on_tick(delta);

	text_info->setString(get_console_string());

	string legend = "";

	switch(ch->get_state()) {
		case MenuState::MAIN:
			legend =
			"^: Item \n"
			">: Attack \n"
			"V: Defend \n";
			break;

		case MenuState::ATTACK:
			legend =
			"^: Enemy 0 \n"
			">: Enemy 1 \n"
			"V: Enemy 2 \n";
			break;

		default: break;
	}

	text_legend->setString(legend);
}

void RPGGame::on_render(sf::RenderWindow* window) {
	
	window->clear();

	cam_scene.arm(*window);
	window->draw(em_scene);

	cam_hud.arm(*window);
	window->draw(em_hud);
}

void RPGGame::attack_enemy(int n) {
	
	push_console_message("You are attacking enemy " + STR(n));
	cam_hud.shake(10, 10);
}
