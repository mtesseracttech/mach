//
// Created by mtesseract on 7/16/19.
//

#ifndef MACH_MEMORY_HPP
#define MACH_MEMORY_HPP

#include <memory>

namespace mach {
	template<typename T, typename U>
	inline bool equals(const std::weak_ptr<T> &t, const std::weak_ptr<U> &u) {
		return !t.owner_before(u) && !u.owner_before(t);
	}


	template<typename T, typename U>
	inline bool equals(const std::weak_ptr<T> &t, const std::shared_ptr<U> &u) {
		return !t.owner_before(u) && !u.owner_before(t);
	}
}

#endif //MACH_MEMORY_HPP
