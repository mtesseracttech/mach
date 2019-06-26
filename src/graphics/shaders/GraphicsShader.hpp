//
// Created by mtesseract on 6/24/19.
//

#ifndef MACH_GRAPHICSSHADER_HPP
#define MACH_GRAPHICSSHADER_HPP

#include <string>

namespace mach::gfx {
	class GraphicsShader {
		virtual void print_source() = 0;

		virtual void load_shader_module(const std::string &p_shader_name) = 0;

		virtual void load_shader_file() = 0;

		virtual void compile_shader() = 0;

		virtual void use() = 0;
	};
}


#endif //MACH_GRAPHICSSHADER_HPP
