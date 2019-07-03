//
// Created by mtesseract on 7/2/19.
//

#ifndef MACH_OPENGLTEXTURE_HPP
#define MACH_OPENGLTEXTURE_HPP

#define STB_IMAGE_IMPLEMENTATION

#include <string>
#include <glad/glad.h>
#include <auxiliary/logging/Logger.hpp>
#include <io/files/FileIO.hpp>
#include "stb/stb_image.h"
#include "auxiliary/Properties.hpp"

namespace mach::gfx {
	class OpenGLTexture {
		uint32_t m_texture_id = 0;
		uint32_t m_width = 0;
		uint32_t m_height = 0;
		uint32_t m_channels = 0;

	public:
		bool load_from_file(const std::string &p_filepath) {
			std::stringstream ss;
			ss << "../res/textures/" << p_filepath;
			std::string filepath = ss.str();

			bool exists = io::FileIO::file_exists(filepath);

			std::cout << exists << std::endl;

			if (!exists) {
				std::cout << filepath << std::endl;
				Logger::log("Texture file '" + p_filepath + "' does not exist", Error);
				return false;
			}

			glGenTextures(1, &m_texture_id);
			glBindTexture(GL_TEXTURE_2D, m_texture_id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			int width, height, nr_channels;
			unsigned char *data = stbi_load(ss.str().c_str(), &width, &height, &nr_channels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
				m_width = static_cast<uint32_t>(width);
				m_height = static_cast<uint32_t>(height);
				m_channels = static_cast<uint32_t>(nr_channels);
				stbi_image_free(data);
				return true;
			} else {
				Logger::log("Failed to load texture", Error);
				stbi_image_free(data);
				return false;
			}
		}

		void bind_texture() {
			glBindTexture(GL_TEXTURE_2D, m_texture_id);
		}

		uint32_t get_width() {
			return m_texture_id;
		}

		uint32_t get_height() {
			return m_texture_id;
		}

		uint32_t get_channels() {
			return m_texture_id;
		}
	};
}

#endif //MACH_OPENGLTEXTURE_HPP
