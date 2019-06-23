//
// Created by mtesseract on 27-5-19.
//

#ifndef MACH_MACHAPPLICATION_HPP
#define MACH_MACHAPPLICATION_HPP

#include <io/input/KeyInput.hpp>

namespace mach {
	class MachApplication {
	public:
		MachApplication();

		void run();

	protected:
		RenderWindow *m_window;

		void setup_subsystems();

		void shutdown();
	};
}

#endif //MACH_MACHAPPLICATION_HPP
