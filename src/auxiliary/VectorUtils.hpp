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
		static std::vector<T> slice(std::vector<T> const &p_v, size_t p_m, size_t p_n) {
			auto first = p_v.cbegin() + p_m;
			auto last = p_v.cbegin() + p_n + 1;

			std::vector<T> vec(first, last);
			return vec;
		}

		template<typename T>
		static void remove_all_instances_of_val(std::vector<T> &p_vec, const T &p_val) {
			p_vec.erase(std::remove(p_vec.begin(), p_vec.end(), p_val), p_vec.end());
		}
	};

	template<class T>
	std::ostream &operator<<(std::ostream &p_os, const std::vector<T> &p_v) {
		p_os << "[";
		for (typename std::vector<T>::const_iterator ii = p_v.begin(); ii != p_v.end(); ++ii) {
			p_os << " " << *ii;
		}
		p_os << "]";
		return p_os;
	}


}


#endif //MACH_VECTORUTILS_HPP
