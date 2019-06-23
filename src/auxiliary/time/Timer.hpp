//
// Created by mtesseract on 23-6-19.
//

#ifndef MACH_TIMER_HPP
#define MACH_TIMER_HPP

#include <chrono>

namespace mach {
	class Timer {
	private:
		typedef std::chrono::high_resolution_clock ChronoClock;
		typedef std::chrono::duration<double, std::ratio<1> > ChronoSecond;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;

	public:
		Timer();

		void reset();

		double get_elapsed() const;
	};
}


#endif //MACH_TIMER_HPP
