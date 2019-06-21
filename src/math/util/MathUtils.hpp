//
// Created by mtesseract on 6/17/19.
//

#ifndef MACH_MATHUTILS_HPP
#define MACH_MATHUTILS_HPP

namespace mach {
    template<typename T>
    class MathUtils {
        static inline T lerp(T p_start, T p_end, T p_t) {
            return p_start + (p_end - p_start) * p_t;
        }
    };
}

#endif //MACH_MATHUTILS_HPP
