//
// Created by mtesseract on 23-6-19.
//

#include <sstream>
#include <auxiliary/logging/Logger.hpp>
#include "Timer.hpp"
#include <iostream>

namespace mach {
	Timer::Timer() : m_start(ChronoClock::now()) {}

	void Timer::reset() {
		m_start = ChronoClock::now();
	}

	double Timer::get_elapsed() const {
		return std::chrono::duration_cast<ChronoSecond>(ChronoClock::now() - m_start).count();
	}
}
