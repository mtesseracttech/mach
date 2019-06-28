//
// Created by mtesseract on 6/24/19.
//

#ifndef MACH_OPENGLSHADER_HPP
#define MACH_OPENGLSHADER_HPP

#include "GraphicsShader.hpp"

namespace mach::gfx {
	class OpenGLShader : public GraphicsShader {
	protected:
		uint32_t m_shader_program = 0;
		std::string m_program_name = "";
	private:
		void load_shader_file() override;

		void compile_shader() override;

	protected:

		void print_shader_error_info(uint32_t p_shader_handle, const std::string &p_filename);

		void print_linking_error_info(uint32_t p_program_handle, const std::string &p_shader_name);

		uint32_t compile_shader(GLenum p_shader_type, const std::string &p_filename);

	public:
		void load_shader_module(const std::string &p_shader_name) override;

		void use() override;
	};
}

#endif //MACH_OPENGLSHADER_HPP
