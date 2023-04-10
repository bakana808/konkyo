
<h1><center>Konkyo</center></h1>
<center>A 2D Game Framework</center>

* * *

# Quickstart

```
src/mygame.cpp
```
```c++
#include "kyo/game"

class MyGame: public kyo::Game {
public:

	// runs before the window opens
	// use this method to load any resources
	void on_run() override { /* ... */ }

	// runs after the window closes
	// use this method to unload any resources
	void on_close() override { /* ... */ }

	// runs every tick (at a fixed rate)
	// use this method for any precise logic
	void on_tick(const float& dt) override { /* ... */ }

	// runs every frame (can vary)
	// most of the time, do not use this method for any logic
	void on_update(float delta) override { /* ... */ }

	// runs at every frame between two ticks
	// 't' will be a float between 0.0 - 1.0
	// use this method to smooth a transition between two ticks
	// (needed when framerate > tickrate)
	void on_lerp(float t) override { /* ... */ }
};
```

## 
## Entities

An _entity_ is an object that can be drawn.

```



