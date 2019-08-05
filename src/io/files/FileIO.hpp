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
#include <optional>


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
				Logger::log(ss.str(), Error);
				return "";
			}
		}

		static std::optional<std::string> read_file_opt(const std::string &p_filename) {
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
				ss << "Failed to read the file, returning an empty optional '" << p_filename << "': "
				   << std::strerror(errno);
				return {};
			}
		}

		static bool file_exists(const std::string &p_filename) {
			if (FILE *file = fopen(p_filename.c_str(), "r")) {
				fclose(file);
				return true;
			} else {
				return false;
			}
		}
	};
}

#endif //MACH_FILEIO_HPP
