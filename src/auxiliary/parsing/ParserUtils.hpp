//
// Created by mtesseract on 6/27/19.
//

#ifndef MACH_PARSERUTILS_HPP
#define MACH_PARSERUTILS_HPP

#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <optional>
#include <charconv>

namespace mach {
	class ParserUtils {
	public:
		static std::vector<std::string> tokenize(const std::string &p_line, char p_delimiter) {
			std::vector<std::string> tokens;
			std::istringstream ss(p_line);
			std::string temp;
			while (getline(ss, temp, p_delimiter)) {
				tokens.push_back(temp);
			}
			return tokens;
		}

		template<typename T>
		static bool number_from_string(const std::string &p_in, T *p_out) {
			try {
				*p_out = static_cast<T>(std::stod(p_in));
				return true;
			} catch (const std::invalid_argument &ia) {
				return false;
			}
		}


		template<typename T>
		static std::vector<T>
		numbers_from_strings(const std::vector<std::string> &p_in_strings, int p_base = 10) {
			std::vector<T> results;
			for (const auto &p_in_string : p_in_strings) {
				T res;
				if (number_from_string<T>(p_in_string, &res)) {
					results.push_back(res);
				}
			}
			return results;
		}


	};
}

#endif //MACH_PARSERUTILS_HPP
