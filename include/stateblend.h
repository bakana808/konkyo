
#include "kyo/common.h"
#include <vector>
#include <algorithm>

using std::vector;

/**
 * A helper class allowing for the lerping between two states.
 *
 * T must overload operator*(float) and operator-(T) to work with this class.
 */
template<class T>
class StateBlend {
private:

	T *prev_state, *curr_state;

	int blend_frames_max = -1;
	int blend_frames = -1;

	vector<T> frames;

	int tick_count = 0;

public:

	StateBlend<T>& set_state(const T& state, int blend_frames) {

		prev_state = curr_state;
		curr_state = &state;

		this->tick_count = 0;
		this->frames.clear();
		this->blend_frames_max = blend_frames;
		this->blend_frames = blend_frames;
	}

	/**
	 * Increments the internal tick counter.
	 */
	void tick() { this->tick_count++; }

	T get_state_at_frame(int n) {
		
		n = std::clamp(n, 0, frames.size());
		return frames[n];
	}
};
