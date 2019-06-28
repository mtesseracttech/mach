//
// Created by mtesseract on 6/24/19.
//

#include <glad/glad.h>
#include <io/FileIO.hpp>
#include <auxiliary/exceptions/NotImplemented.hpp>
#include <optional>
#include <iostream>
#include "OpenGLShader.hpp"
#include <auxiliary/logging/Logger.hpp>
#include <auxiliary/logging/LogUtils.hpp>

namespace mach::gfx {
	void OpenGLShader::load_shader_module(const std::string &p_shader_name) {
		const std::string shader_path = "../res/shaders/" + p_shader_name + "/";
		const std::string vert_shader_name = shader_path + p_shader_name + ".vert";
		const std::string frag_shader_name = shader_path + p_shader_name + ".frag";
		const std::string geom_shader_name = shader_path + p_shader_name + ".geom";

		const bool has_vert_shader = io::FileIO::file_exists(vert_shader_name);
		const bool has_frag_shader = io::FileIO::file_exists(frag_shader_name);
		const bool has_geom_shader = io::FileIO::file_exists(geom_shader_name);

		m_program_name = p_shader_name;
		m_shader_program = glCreateProgram();

		uint32_t vert_shader_handle = has_vert_shader ? compile_shader(GL_VERTEX_SHADER, vert_shader_name) : 0;
		uint32_t geom_shader_handle = has_geom_shader ? compile_shader(GL_GEOMETRY_SHADER, geom_shader_name) : 0;
		uint32_t frag_shader_handle = has_frag_shader ? compile_shader(GL_FRAGMENT_SHADER, frag_shader_name) : 0;

		if (vert_shader_handle != 0) glAttachShader(m_shader_program, vert_shader_handle);
		if (geom_shader_handle != 0) glAttachShader(m_shader_program, geom_shader_handle);
		if (frag_shader_handle != 0) glAttachShader(m_shader_program, frag_shader_handle);

		glLinkProgram(m_shader_program);
		int success;
		glGetProgramiv(m_shader_program, GL_LINK_STATUS, &success);
		if (!success) print_linking_error_info(m_shader_program, p_shader_name);

		if (vert_shader_handle != 0) glDeleteShader(vert_shader_handle);
		if (geom_shader_handle != 0) glDeleteShader(geom_shader_handle);
		if (frag_shader_handle != 0) glDeleteShader(frag_shader_handle);
	}

	uint32_t OpenGLShader::compile_shader(GLenum p_shader_type, const std::string &p_filename) {
		std::string shader_src = io::FileIO::read_file(p_filename);
		const char *shader_c_str = shader_src.c_str();
		uint32_t shader_handle = glCreateShader(p_shader_type);
		glShaderSource(shader_handle, 1, &shader_c_str, nullptr);
		glCompileShader(shader_handle);
		int success;
		glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);
		if (!success) {
			print_shader_error_info(shader_handle, p_filename);
			return 0;
		}
		return shader_handle;
	}

	void OpenGLShader::print_shader_error_info(uint32_t p_shader_handle, const std::string &p_filename) {
		char info_log[512];
		glGetShaderInfoLog(p_shader_handle, sizeof(info_log), nullptr, info_log);
		std::stringstream ss;
		ss << "OpenGL shader '" << p_filename << "' compilation failed:\n" << info_log;
		Logger::log(ss.str(), Error);
	}

	void OpenGLShader::print_linking_error_info(uint32_t p_program_handle, const std::string &p_shader_name) {
		char info_log[512];
		glGetProgramInfoLog(m_shader_program, 512, nullptr, info_log);
		std::stringstream ss;
		ss << "OpenGL shader program '" << p_shader_name << "' linking failed:\n" << info_log;
		Logger::log(ss.str(), Error);
	}

	void OpenGLShader::load_shader_file() {
		throw NotImplemented("Individual shader file loading is not implemented yet");
	}

	void OpenGLShader::compile_shader() {
		throw NotImplemented("Separate shader file compilation is not implemented yet");
	}

	void OpenGLShader::use() {
		//Logger::log(to_str(m_shader_program), LogInfo);
		glUseProgram(m_shader_program);
	}
}
