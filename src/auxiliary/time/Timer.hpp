//
// Created by mtesseract on 23-6-19.
//

#ifndef MACH_TIMER_HPP
#define MACH_TIMER_HPP

#include <chrono>
#include <string>

namespace mach {
	class Timer {
	private:
		typedef std::chrono::system_clock ChronoClock;
		typedef std::chrono::duration<double, std::ratio<1> > ChronoSecond;
		std::chrono::time_point<ChronoClock> m_start;

	public:
		Timer();

		void reset();

		double get_elapsed() const;
	};
}


#endif //MACH_TIMER_HPP
