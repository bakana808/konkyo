
#pragma once


#include <cmath>
#include <vector>

#include "kyo/frame_clock.h"
#include "kyo/common.h"
#include "kyo/camera.h"


class Game {
private:

    sf::RenderWindow* window;

	float tickrate = 1/60.f; // ticks per second
	float tick_timer = 0.f;  // delta accumulation to process ticks

    FrameClock fc;

    void processEvents();

    /**
     * @brief Process game logic with the given change in time
     * from the last frame.
     *
     * @param delta
     */
    void update(float delta);

    /**
     * @brief Render a frame.
     */
    void render();

public:

    Game(const Game&) = delete;

    Game& operator=(const Game&) = delete;

    Game();

    ~Game();

    void run();

    void close();

	void set_view(const Camera& camera);

    virtual void on_run() {}

    virtual void on_close() {}

	/**
	 * @brief Called on every tick.
	 *
	 * This method is used to process any game logic.
	 * The delta time provided is guaranteed to be a constant equal to
	 * the current tickrate.
	 *
	 * @param delta the current tickrate (in seconds)
	 */
    virtual void on_tick(const float& delta) {}

	/**
	 * @brief Called on every frame.
	 *
	 * This method is used for interpolation between the last tick and
	 * the current tick. Useful if the framerate is much higher than
	 * the tickrate.
	 *
	 * The time variable provided is a float between 0 and 1.
	 * 0 means we are still at the last tick.
	 * 1 means we are at the current tick.
	 *
	 * @param t a "time variable" between 0 and 1
	 */
	virtual void on_lerp(float t) {}

	/**
	 * @brief Called on every frame.
	 *
	 * This method is used to process logic that requires the raw time delta
	 * between frames.
	 *
	 * @param delta the delta time from the last frame to this frame (in
     * seconds)
	 */
	virtual void on_update(float delta) {}

    virtual void on_render(sf::RenderWindow* window) {}

    virtual void on_key_press(Key key) {}

    virtual void on_key_release(Key key) {}

    virtual void on_key_hold(Key key) {}

	void set_tickrate(float tickrate) { this->tickrate = 1/tickrate; }

	const float& get_tickrate() { return this->tickrate; }
};
