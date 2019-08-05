//
// Created by mtesseract on 7/16/19.
//

#ifndef MACH_MEMORY_HPP
#define MACH_MEMORY_HPP

#include <memory>

namespace mach {
	template<typename T, typename U>
	inline bool equals(const std::weak_ptr<T> &p_t, const std::weak_ptr<U> &p_u) {
		return !p_t.owner_before(p_u) && !p_u.owner_before(p_t);
	}


	template<typename T, typename U>
	inline bool equals(const std::weak_ptr<T> &p_t, const std::shared_ptr<U> &p_u) {
		return !p_t.owner_before(p_u) && !p_u.owner_before(p_t);
	}

	template<class T, class U>
	std::weak_ptr<T> static_pointer_cast(std::weak_ptr<U> const &p_r) {
		return std::static_pointer_cast<T>(p_r.lock());
	}
}

#endif //MACH_MEMORY_HPP
