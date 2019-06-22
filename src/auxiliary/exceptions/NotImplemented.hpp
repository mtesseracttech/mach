//
// Created by mtesseract on 6/11/19.
//

#ifndef MACH_NOTIMPLEMENTED_HPP
#define MACH_NOTIMPLEMENTED_HPP

#include <string>
#include <stdexcept>

namespace mach {
    class NotImplemented : public std::logic_error {
    private:
        std::string m_text;

        NotImplemented(const char *p_message, const char *p_function) : std::logic_error("Not Implemented") {
            m_text = p_message;
            m_text += " : ";
            m_text += p_function;
        };

    public:

        NotImplemented() : NotImplemented("Not Implememented", __FUNCTION__) {}

        NotImplemented(const char *message) : NotImplemented(message, __FUNCTION__) {}

        virtual const char *what() const throw() { return m_text.c_str(); }
    };
}

#endif //MACH_NOTIMPLEMENTED_HPP
