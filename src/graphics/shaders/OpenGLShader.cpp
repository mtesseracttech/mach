//
// Created by mtesseract on 6/24/19.
//

#include <glad/glad.h>
#include <io/FileIO.hpp>
#include <auxiliary/exceptions/NotImplemented.hpp>
#include "OpenGLShader.hpp"

namespace mach::gfx {
	void OpenGLShader::print_source() {
		std::stringstream ss;
		ss << m_program_name << " OpenGL shader sources:\n\n";
		ss << "Vertex Source:\n\n" << m_vert_src << "\n\n";
		ss << "Fragment Source:\n\n" << m_frag_src << "\n\n";
		Logger::log(ss.str(), LogInfo);
	}

	void OpenGLShader::load_shader_module(const std::string &p_shader_name) {

		const std::string shader_path = "../res/shaders/" + p_shader_name + "/";
		const std::string vert_shader_name = shader_path + p_shader_name + ".vert";
		const std::string frag_shader_name = shader_path + p_shader_name + ".frag";

		int success;

		m_program_name = p_shader_name;

		m_vert_src = io::FileIO::read_file(vert_shader_name);
		const char *vert_src_cstring = m_vert_src.c_str();
		uint32_t m_vert_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vert_shader, 1, &vert_src_cstring, nullptr);
		glCompileShader(m_vert_shader);

		glGetShaderiv(m_vert_shader, GL_COMPILE_STATUS, &success);
		if (!success) print_shader_error_info(m_vert_shader, vert_shader_name);

		m_frag_src = io::FileIO::read_file(frag_shader_name);
		const char *frag_src_cstring = m_frag_src.c_str();

		uint32_t m_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_frag_shader, 1, &frag_src_cstring, nullptr);
		glCompileShader(m_frag_shader);

		glGetShaderiv(m_frag_shader, GL_COMPILE_STATUS, &success);
		if (!success) print_shader_error_info(m_frag_shader, frag_shader_name);

		m_shader_program = glCreateProgram();
		glAttachShader(m_shader_program, m_vert_shader);
		glAttachShader(m_shader_program, m_frag_shader);
		glLinkProgram(m_shader_program);

		glGetProgramiv(m_shader_program, GL_LINK_STATUS, &success);
		if (!success) print_linking_error_info(m_shader_program, p_shader_name);

		glDeleteShader(m_vert_shader);
		glDeleteShader(m_frag_shader);
	}

	void OpenGLShader::print_shader_error_info(uint32_t p_shader_handle, const std::string &p_filename) {
		char info_log[512];
		glGetShaderInfoLog(p_shader_handle, 512, nullptr, info_log);

		std::stringstream ss;
		ss << "OpenGL shader '" << p_filename << "' compilation failed:\n" << info_log;
		Logger::log(ss.str(), LogError);
	}

	void OpenGLShader::print_linking_error_info(uint32_t p_program_handle, const std::string &p_shader_name) {
		char info_log[512];
		glGetProgramInfoLog(m_shader_program, 512, NULL, info_log);
		std::stringstream ss;
		ss << "OpenGL shader program '" << p_shader_name << "' linking failed:\n" << info_log;
		Logger::log(ss.str(), LogError);
	}

	void OpenGLShader::load_shader_file() {
		throw NotImplemented("Individual shader file loading is not implemented yet");
	}

	void OpenGLShader::compile_shader() {
		throw NotImplemented("Separate shader file compilation is not implemented yet");
	}

	void OpenGLShader::use() {
		glUseProgram(m_shader_program);
	}
}
