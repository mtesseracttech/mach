//
// Created by mtesseract on 27-5-19.
//

#ifndef MACH_MACHAPPLICATION_HPP
#define MACH_MACHAPPLICATION_HPP

#include <io/input/KeyInput.hpp>
#include <graphics/renderer/Renderer.hpp>
#include <graphics/renderer/window/RenderWindow.hpp>
#include <core/scene/Camera.hpp>

namespace mach {
	class MachApplication {
	public:
		MachApplication();

		void run();

	protected:
		std::shared_ptr<gfx::RenderWindow> m_window;
		std::shared_ptr<gfx::Renderer> m_renderer;

		void setup_subsystems();

		void shutdown();
	};
}

#endif //MACH_MACHAPPLICATION_HPP
