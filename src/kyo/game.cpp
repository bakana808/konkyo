
#include "kyo/game.h"
#include <math.h>


Game::Game() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Game", sf::Style::None, settings);
    //window->setFramerateLimit(200);
    window->setKeyRepeatEnabled(false);

    PRINT("created game");
}

Game::~Game() {

    delete window;
}

void Game::run() {

    this->on_run();

    while (window->isOpen()) {

        float dt = fc.get_delta();

        processEvents();
        update(dt);
        render();
        window->display();

        fc.push_frame();
    }

    this->on_close();
}


void Game::close() {
    window->close();
}


void Game::processEvents() {

    sf::Event event;
    while (window->pollEvent(event)) {

        switch(event.type) {
        case sf::Event::Closed:
            close(); break;

        case sf::Event::KeyPressed:
            this->on_key_press(event.key.code); break;

        case sf::Event::KeyReleased:
            this->on_key_release(event.key.code); break;
        }
    }
}


void Game::update(float delta) {

	tick_timer += delta;

	while(tick_timer >= tickrate) {
		tick_timer -= tickrate;
		this->on_tick(tickrate);
	}

    this->on_lerp(tick_timer / tickrate);
	this->on_update(delta);
}


void Game::render() {

    this->on_render(window);
}
