//
// Created by mtesseract on 6/9/19.
//

#ifndef MACH_VECTORTRAITS_HPP
#define MACH_VECTORTRAITS_HPP

#include "../LinMatTypes.hpp"

namespace mach {
    template<typename T>
    struct VectorTraits {
    };

    template<typename T>
    struct VectorTraits<Vector2<T>> {
        using LowerDim = T;
        using UpperDim = Vector3<T>;
    };

    template<typename T>
    struct VectorTraits<Vector3<T>> {
        using LowerDim = Vector2<T>;
        using UpperDim = Vector4<T>;
    };

    template<typename T>
    struct VectorTraits<Vector4<T>> {
        using LowerDim = Vector3<T>;
    };
}


#endif //MACH_VECTORTRAITS_HPP
