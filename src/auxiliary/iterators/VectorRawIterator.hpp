//
// Created by mtesseract on 6/3/19.
//

#ifndef MACH_VECTORRAWITERATOR_HPP
#define MACH_VECTORRAWITERATOR_HPP

#include <iterator>

namespace mach {
    template<typename T>
    class VectorRawIterator : public std::iterator<std::random_access_iterator_tag, T, ptrdiff_t, T *, T &> {
    public:

        VectorRawIterator(T *ptr = nullptr) { m_ptr = ptr; }

        VectorRawIterator(const VectorRawIterator<T> &rawIterator) = default;

        ~VectorRawIterator() {}

        VectorRawIterator<T> &operator=(const VectorRawIterator<T> &rawIterator) = default;

        VectorRawIterator<T> &operator=(T *ptr) {
            m_ptr = ptr;
            return (*this);
        }

        operator bool() const {
            return m_ptr != nullptr;
        }

        bool operator==(const VectorRawIterator<T> &rawIterator) const {
            return (m_ptr == rawIterator.getConstPtr());
        }

        bool operator!=(const VectorRawIterator<T> &rawIterator) const {
            return (m_ptr != rawIterator.getConstPtr());
        }

        VectorRawIterator<T> &operator+=(const ptrdiff_t &movement) {
            m_ptr += movement;
            return (*this);
        }

        VectorRawIterator<T> &operator-=(const ptrdiff_t &movement) {
            m_ptr -= movement;
            return (*this);
        }

        VectorRawIterator<T> &operator++() {
            ++m_ptr;
            return (*this);
        }

        VectorRawIterator<T> &operator--() {
            --m_ptr;
            return (*this);
        }

        VectorRawIterator<T> operator++(int) {
            auto temp(*this);
            ++m_ptr;
            return temp;
        }

        VectorRawIterator<T> operator--(int) {
            auto temp(*this);
            --m_ptr;
            return temp;
        }

        VectorRawIterator<T> operator+(const ptrdiff_t &movement) {
            auto oldPtr = m_ptr;
            m_ptr += movement;
            auto temp(*this);
            m_ptr = oldPtr;
            return temp;
        }

        VectorRawIterator<T> operator-(const ptrdiff_t &movement) {
            auto oldPtr = m_ptr;
            m_ptr -= movement;
            auto temp(*this);
            m_ptr = oldPtr;
            return temp;
        }

        ptrdiff_t operator-(const VectorRawIterator<T> &rawIterator) {
            return std::distance(rawIterator.getPtr(), this->getPtr());
        }

        T &operator*() { return *m_ptr; }

        const T &operator*() const { return *m_ptr; }

        T *operator->() { return m_ptr; }

        T *getPtr() const { return m_ptr; }

        const T *getConstPtr() const { return m_ptr; }

    protected:

        T *m_ptr;
    };
}

#endif //MACH_VECTORRAWITERATOR_HPP
