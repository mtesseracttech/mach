//
// Created by mtesseract on 6/24/19.
//

#ifndef MACH_OPENGLSHADER_HPP
#define MACH_OPENGLSHADER_HPP

#include "GraphicsShader.hpp"
#include <map>
#include <math/linalg/Vector/Vector3.hpp>
#include <math/linalg/Vector/Vector4.hpp>

namespace mach::gfx {
	class OpenGLShader : public GraphicsShader {
	protected:
		uint32_t m_shader_program = 0;
		std::string m_program_name = "";

	private:
		void load_shader_file() override;

		void compile_shader() override;

	protected:

		static void print_shader_error_info(uint32_t p_shader_handle, const std::string &p_filename);

		void print_linking_error_info(uint32_t p_program_handle, const std::string &p_shader_name);

		uint32_t compile_shader(GLenum p_shader_type, const std::string &p_filename);

	public:
		void load_shader_module(const std::string &p_shader_name) override;

		void use() override;

		template<typename T>
		void set_val(const std::string &p_name, T p_value) const {
			if constexpr (std::is_same<T, float>::value) {
				glUniform1f(glGetUniformLocation(m_shader_program, p_name.c_str()), p_value);
			} else if constexpr(std::is_same<T, int>::value) {
				glUniform1i(glGetUniformLocation(m_shader_program, p_name.c_str()), p_value);
			} else if constexpr(std::is_same<T, bool>::value) {
				glUniform1i(glGetUniformLocation(m_shader_program, p_name.c_str()), static_cast<int>(p_value));
			} else {
				mach_assert(false, "Type: " + std::string(typeid(T).name()) + " in " + m_program_name +
				                   " does not have an implementation for use in shader uniforms.");
			}
		}

		template<typename T>
		void set_vec2(const std::string &p_name, const Vector2<T> &p_value) const {
			if constexpr (std::is_same<T, float>::value) {
				glUniform2fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, p_value.get_value_ptr());
			} else if constexpr(std::is_same<T, int>::value) {
				glUniform2iv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, p_value.get_value_ptr());
			} else if constexpr(std::is_same<T, bool>::value) {
				glUniform2iv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1,
				             static_cast<int *>(p_value.get_value_ptr()));
			} else {
				mach_assert(false, "Type: " + std::string(typeid(T).name()) + " in " + m_program_name +
				                   " does not have an implementation for use in shader uniforms.");
			}
		}

		template<typename T>
		void set_vec3(const std::string &p_name, const Vector3<T> &p_value) const {
			if constexpr (std::is_same<T, float>::value) {
				glUniform3fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, p_value.get_value_ptr());
			} else if constexpr(std::is_same<T, int>::value) {
				glUniform3iv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, p_value.get_value_ptr());
			} else if constexpr(std::is_same<T, bool>::value) {
				glUniform3iv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1,
				             static_cast<int *>(p_value.get_value_ptr()));
			} else {
				mach_assert(false, "Type: " + std::string(typeid(T).name()) + " in " + m_program_name +
				                   " does not have an implementation for use in shader uniforms.");
			}
		}

		template<typename T>
		void set_vec4(const std::string &p_name, const Vector4<T> &p_value) const {
			if constexpr (std::is_same<T, float>::value) {
				glUniform4fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, p_value.get_value_ptr());
			} else if constexpr(std::is_same<T, int>::value) {
				glUniform4iv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, p_value.get_value_ptr());
			} else if constexpr(std::is_same<T, bool>::value) {
				glUniform4iv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1,
				             static_cast<int *>(p_value.get_value_ptr()));
			} else {
				mach_assert(false, "Type: " + std::string(typeid(T).name()) + " in " + m_program_name +
				                   " does not have an implementation for use in shader uniforms.");
			}
		}
	};
}
#endif //MACH_OPENGLSHADER_HPP
