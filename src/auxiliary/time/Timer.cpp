//
// Created by mtesseract on 23-6-19.
//

#include "Timer.hpp"

namespace mach {
	Timer::Timer() : m_start(ChronoClock::now()) {}

	void Timer::reset() {
		m_start = ChronoClock::now();
	}

	double Timer::get_elapsed() const {
		return std::chrono::duration_cast<ChronoSecond>(ChronoClock::now() - m_start).count();
	}
}
