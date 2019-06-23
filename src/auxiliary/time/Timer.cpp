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

	std::string Timer::get_time_in_hh_mm_ss() {
		using namespace std::chrono;

		// get current time
		auto now = system_clock::now();
		auto now_other = (system_clock::now() - m_start).count();

		std::cout << typeid(now_other).name() << std::endl;
		auto timer = system_clock::to_time_t(now);
		// convert to broken time
		std::tm bt = *std::localtime(&timer);

		std::ostringstream oss;
		//oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
		return oss.str();
	}
}
