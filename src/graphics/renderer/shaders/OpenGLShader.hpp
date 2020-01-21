//
// Created by mtesseract on 6/24/19.
//

#ifndef MACH_OPENGLSHADER_HPP
#define MACH_OPENGLSHADER_HPP

#include <map>
#include <math/linalg/Vector.hpp>
#include <io/files/FileIO.hpp>

namespace mach::gfx {
	class OpenGLShader {
	protected:
		uint32_t m_shader_program = 0;
		std::string m_program_name = "";

	protected:

		static void print_shader_error_info(uint32_t p_shader_handle, const std::string &p_filename) {
			char info_log[512];
			glGetShaderInfoLog(p_shader_handle, sizeof(info_log), nullptr, info_log);
			std::stringstream ss;
			ss << "OpenGL shader '" << p_filename << "' compilation failed:\n" << info_log;
			Logger::log(ss.str(), Error);
		}

		void print_linking_error_info(uint32_t p_program_handle, const std::string &p_shader_name) {
			char info_log[512];
			glGetProgramInfoLog(m_shader_program, 512, nullptr, info_log);
			std::stringstream ss;
			ss << "OpenGL shader program '" << p_shader_name << "' linking failed:\n" << info_log;
			Logger::log(ss.str(), Error);
		}

		uint32_t compile_shader(GLenum p_shader_type, const std::string &p_filename) {
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

	public:
		explicit OpenGLShader(const std::string &p_program_name) {
			Logger::log("Loading shader module: " + p_program_name);

			const std::string shader_path = "../res/shaders/" + p_program_name + "/";
			const std::string vert_shader_name = shader_path + p_program_name + ".vert";
			const std::string frag_shader_name = shader_path + p_program_name + ".frag";
			const std::string geom_shader_name = shader_path + p_program_name + ".geom";

			const bool has_vert_shader = io::FileIO::file_exists(vert_shader_name);
			const bool has_frag_shader = io::FileIO::file_exists(frag_shader_name);
			const bool has_geom_shader = io::FileIO::file_exists(geom_shader_name);

			if (!has_vert_shader || !has_frag_shader) {
				std::stringstream ss;
				ss << "The shader ";
				ss << '"' << p_program_name << '"' << " is incomplete, it is missing: ";
				if (!has_vert_shader) ss << "Vertex";
				if (!has_vert_shader && !has_frag_shader) ss << " and ";
				if (!has_frag_shader) ss << "Fragment";
				ss << " file(s).";
				throw std::runtime_error(ss.str());
			}

			m_program_name = p_program_name;
			m_shader_program = glCreateProgram();

			uint32_t vert_shader_handle = compile_shader(GL_VERTEX_SHADER, vert_shader_name);
			uint32_t frag_shader_handle = compile_shader(GL_FRAGMENT_SHADER, frag_shader_name);
			uint32_t geom_shader_handle = has_geom_shader ? compile_shader(GL_GEOMETRY_SHADER_ARB, geom_shader_name) : 0;

			if (vert_shader_handle != 0) glAttachShader(m_shader_program, vert_shader_handle);
			if (geom_shader_handle != 0) glAttachShader(m_shader_program, geom_shader_handle);
			if (frag_shader_handle != 0) glAttachShader(m_shader_program, frag_shader_handle);

			glLinkProgram(m_shader_program);
			int success;
			glGetProgramiv(m_shader_program, GL_LINK_STATUS, &success);
			if (!success) {
				print_linking_error_info(m_shader_program, p_program_name);
			}

			if (vert_shader_handle != 0) glDeleteShader(vert_shader_handle);
			if (geom_shader_handle != 0) glDeleteShader(geom_shader_handle);
			if (frag_shader_handle != 0) glDeleteShader(frag_shader_handle);

			if (!success) {
				throw std::runtime_error("Could not correctly link the shaders for " + p_program_name);
			}
		}

		template<typename T>
		inline void set_val(const std::string &p_name, const T &p_value) const {
			if constexpr (std::is_same<T, float>::value) {
				glUniform1f(glGetUniformLocation(m_shader_program, p_name.c_str()), p_value);
			} else if constexpr(std::is_same<T, int>::value) {
				glUniform1i(glGetUniformLocation(m_shader_program, p_name.c_str()), p_value);
			} else if constexpr(std::is_same<T, bool>::value) {
				glUniform1i(glGetUniformLocation(m_shader_program, p_name.c_str()), static_cast<int>(p_value));
			} else {
				std::stringstream ss;
				ss << "Type: " << typeid(T).name() << " in " << m_program_name
				   << " does not have an implementation for use in shader uniforms.";
				throw NotImplemented(ss.str().c_str());
			}
		}

		template<typename T, size_t N>
		inline void set_val(const std::string &p_name, const Vector<T, N> &p_value) const {
			if constexpr (N == 2) {
				if constexpr (std::is_same<T, float>::value) {
					glUniform2fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, p_value.get_value_ptr());
				} else if constexpr(std::is_same<T, int>::value) {
					glUniform2iv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, p_value.get_value_ptr());
				} else if constexpr(std::is_same<T, bool>::value) {
					glUniform2iv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1,
					             static_cast<int *>(p_value.get_value_ptr()));
				} else {
					throw NotImplemented("Type: " + std::string(typeid(T).name()) + " in " + m_program_name +
					                     " does not have an implementation for use in shader uniforms.");
				}
			} else if constexpr (N == 3) {
				if constexpr (std::is_same<T, float>::value) {
					glUniform3fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, p_value.get_value_ptr());
				} else if constexpr(std::is_same<T, int>::value) {
					glUniform3iv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, p_value.get_value_ptr());
				} else if constexpr(std::is_same<T, bool>::value) {
					glUniform3iv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1,
					             static_cast<int *>(p_value.get_value_ptr()));
				} else {
					throw NotImplemented("Type: " + std::string(typeid(T).name()) + " in " + m_program_name +
					                     " does not have an implementation for use in shader uniforms.");
				}
			} else if constexpr (N == 4) {
				if constexpr (std::is_same<T, float>::value) {
					glUniform4fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, p_value.get_value_ptr());
				} else if constexpr(std::is_same<T, int>::value) {
					glUniform4iv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, p_value.get_value_ptr());
				} else if constexpr(std::is_same<T, bool>::value) {
					glUniform4iv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1,
					             static_cast<int *>(p_value.get_value_ptr()));
				} else {
					throw NotImplemented("Type: " + std::string(typeid(T).name()) + " in " + m_program_name +
					                     " does not have an implementation for use in shader uniforms.");
				}
			} else {
				throw std::runtime_error("Vectors of size " + to_str(N) + " are not supported by OpenGL uniforms");
			}
		}

		template<typename T, size_t H, size_t W>
		inline void set_val(const std::string &p_name, const Matrix<T, H, W> &p_value) const {
			if constexpr (std::is_same<T, float>::value) {
				if constexpr (H == 2) {
					if constexpr (W == 2) {
						glUniformMatrix2fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, false,
						                   p_value.get_value_ptr());
					} else if constexpr (W == 3) {
						glUniformMatrix2x3fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, false,
						                     p_value.get_value_ptr());
					} else if constexpr (W == 4) {
						glUniformMatrix2x4fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, false,
						                     p_value.get_value_ptr());
					} else {
						throw std::runtime_error(
								"Only matrices with a width between 2 and 4 are supported in OpenGL uniforms");
					}
				} else if constexpr (H == 3) {
					if constexpr (W == 2) {
						glUniformMatrix3x2fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, false,
						                     p_value.get_value_ptr());
					} else if constexpr (W == 3) {
						glUniformMatrix3fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, false,
						                   p_value.get_value_ptr());
					} else if constexpr (W == 4) {
						glUniformMatrix3x4fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, false,
						                     p_value.get_value_ptr());
					} else {
						throw std::runtime_error(
								"Only matrices with a width between 2 and 4 are supported in OpenGL uniforms");
					}
				} else if constexpr (H == 4) {
					if constexpr (W == 2) {
						glUniformMatrix4x2fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, false,
						                     p_value.get_value_ptr());
					} else if constexpr (W == 3) {
						glUniformMatrix4x3fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, false,
						                     p_value.get_value_ptr());
					} else if constexpr (W == 4) {
						glUniformMatrix4fv(glGetUniformLocation(m_shader_program, p_name.c_str()), 1, false,
						                   p_value.get_value_ptr());
					} else {
						throw std::runtime_error(
								"Only matrices with a width between 2 and 4 are supported in OpenGL uniforms");
					}
				} else {
					throw std::runtime_error(
							"Only matrices with a height between 2 and 4 are supported in OpenGL uniforms");
				}
			} else {
				throw std::runtime_error("You cannot load matrices of any other type than float into OpenGL uniforms");
			}
		}

		void use() {
			glUseProgram(m_shader_program);
		}
	};
}
#endif //MACH_OPENGLSHADER_HPP
