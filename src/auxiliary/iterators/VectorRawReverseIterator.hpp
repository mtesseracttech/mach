//
// Created by mtesseract on 6/4/19.
//

#ifndef MACH_VECTORRAWREVERSEITERATOR_HPP
#define MACH_VECTORRAWREVERSEITERATOR_HPP

#include "VectorRawIterator.hpp"

namespace mach {
    template<typename T>
    class VectorReverseRawIterator : public VectorRawIterator<T> {
    public:

        VectorReverseRawIterator(T *ptr = nullptr) : VectorRawIterator<T>(ptr) {}

        VectorReverseRawIterator(
                const VectorRawIterator<T> &rawIterator) { this->m_ptr = rawIterator.getPtr(); }

        VectorReverseRawIterator(const VectorReverseRawIterator<T> &rawReverseIterator) = default;

        ~VectorReverseRawIterator() {}

        VectorReverseRawIterator<T> &
        operator=(const VectorReverseRawIterator<T> &rawReverseIterator) = default;

        VectorReverseRawIterator<T> &operator=(const VectorRawIterator<T> &rawIterator) {
            this->m_ptr = rawIterator.getPtr();
            return (*this);
        }

        VectorReverseRawIterator<T> &operator=(T *ptr) {
            this->setPtr(ptr);
            return (*this);
        }

        VectorReverseRawIterator<T> &operator+=(const ptrdiff_t &movement) {
            this->m_ptr -= movement;
            return (*this);
        }

        VectorReverseRawIterator<T> &operator-=(const ptrdiff_t &movement) {
            this->m_ptr += movement;
            return (*this);
        }

        VectorReverseRawIterator<T> &operator++() {
            --this->m_ptr;
            return (*this);
        }

        VectorReverseRawIterator<T> &operator--() {
            ++this->m_ptr;
            return (*this);
        }

        VectorReverseRawIterator<T> operator++(int) {
            auto temp(*this);
            --this->m_ptr;
            return temp;
        }

        VectorReverseRawIterator<T> operator--(int) {
            auto temp(*this);
            ++this->m_ptr;
            return temp;
        }

        VectorReverseRawIterator<T> operator+(const int &movement) {
            auto oldPtr = this->m_ptr;
            this->m_ptr -= movement;
            auto temp(*this);
            this->m_ptr = oldPtr;
            return temp;
        }

        VectorReverseRawIterator<T> operator-(const int &movement) {
            auto oldPtr = this->m_ptr;
            this->m_ptr += movement;
            auto temp(*this);
            this->m_ptr = oldPtr;
            return temp;
        }

        ptrdiff_t operator-(const VectorReverseRawIterator<T> &rawReverseIterator) {
            return std::distance(this->getPtr(), rawReverseIterator.getPtr());
        }

        VectorRawIterator<T> base() {
            VectorRawIterator<T> forwardIterator(this->m_ptr);
            ++forwardIterator;
            return forwardIterator;
        }
    };
}


#endif //MACH_VECTORRAWREVERSEITERATOR_HPP
