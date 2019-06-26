//
// Created by mtesseract on 6/26/19.
//

#ifndef MACH_FILEIO_HPP
#define MACH_FILEIO_HPP

#include <fstream>
#include <string>
#include <cerrno>
#include <auxiliary/logging/Logger.hpp>
#include <cstring>
#include <sstream>
#include <filesystem>


namespace mach::io {
	class FileIO {
	public:
		static std::string read_file(const std::string &p_filename) {
			std::ifstream file_stream(p_filename, std::ios::in | std::ios::binary);
			if (file_stream) {
				std::string contents;
				file_stream.seekg(0, std::ios::end);
				contents.resize(file_stream.tellg());
				file_stream.seekg(0, std::ios::beg);
				file_stream.read(&contents[0], contents.size());
				file_stream.close();
				return contents;
			} else {
				std::stringstream ss;
				ss << "Failed to read the file '" << p_filename << "': " << std::strerror(errno);
				Logger::log(ss.str(), LogError);
				return "";
			}
		}

		static bool file_exists(const std::string &p_filename) {
			return std::filesystem::exists(p_filename);
		}
	};
}

#endif //MACH_FILEIO_HPP
