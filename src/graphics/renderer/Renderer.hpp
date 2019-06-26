//
// Created by mtesseract on 6/25/19.
//

#ifndef MACH_RENDERER_HPP
#define MACH_RENDERER_HPP

#include <memory>

namespace mach::gfx {
	class Renderer {
	public:
		virtual void setup() = 0;

		virtual void render_scene() = 0;

	public:
		template<typename RendererType>
		static std::shared_ptr<RendererType> create() {
			return std::shared_ptr<RendererType>(new RendererType());
		};
	};
}


#endif //MACH_RENDERER_HPP
