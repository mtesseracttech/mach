//
// Created by mtesseract on 6/27/19.
//

#ifndef MACH_VECTORUTILS_HPP
#define MACH_VECTORUTILS_HPP

#include <vector>
#include <iostream>

namespace mach {
	class VectorUtils {
	public:
		template<typename T>
		static void print(std::vector<T> const &p_v) {
			for (auto i: p_v) {
				std::cout << '[' << i << "]";
			}
			std::cout << std::endl;
		}

		template<typename T>
		static std::vector<T> slice(std::vector<T> const &p_v, size_t p_m, size_t p_n) {
			auto first = p_v.cbegin() + p_m;
			auto last = p_v.cbegin() + p_n + 1;

			std::vector<T> vec(first, last);
			return vec;
		}
	};
}


#endif //MACH_VECTORUTILS_HPP
