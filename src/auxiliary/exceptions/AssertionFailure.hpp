//
// Created by MTesseracT on 2019-06-22.
//

#ifndef MACH_ASSERTIONFAILURE_HPP
#define MACH_ASSERTIONFAILURE_HPP

namespace mach {

#include <exception>
#include <string>
#include <sstream>
#include <iostream>

/// Exception type for assertion failures
    class AssertionFailure : public std::exception {
    private:
        const char *m_expression;
        const char *m_file;
        int m_line;
        std::string m_message;
        std::string m_report;

    public:

        /// Helper class for formatting assertion message
        class StreamFormatter {
        private:
            std::ostringstream m_stream;

        public:
            operator std::string() const {
                return m_stream.str();
            }

            template<typename T>
            StreamFormatter &operator<<(const T &value) {
                m_stream << value;
                return *this;
            }
        };

        /// Log error before throwing
        void log_error() {
#ifdef THROWASSERT_LOGGER
            THROWASSERT_LOGGER(report);
#else
            std::cerr << m_report << std::endl;
#endif
        }

        AssertionFailure(const char *p_expression, const char *p_file, int p_line, const std::string &p_message)
                : m_expression(p_expression), m_file(p_file), m_line(p_line), m_message(p_message) {
            std::ostringstream output_stream;

            if (!p_message.empty()) {
                output_stream << p_message << ": ";
            }

            std::string expression_string = p_expression;

            if (expression_string == "false" || expression_string == "0" || expression_string == "FALSE") {
                output_stream << "Unreachable code assertion";
            } else {
                output_stream << "Assertion '" << p_expression << "'";
            }

            output_stream << " failed in file '" << p_file << "' line " << p_line;
            m_report = output_stream.str();

            log_error();
        }

        /// The assertion message
        virtual const char *what() const throw() {
            return m_report.c_str();
        }

        /// The expression which was asserted to be true
        const char *Expression() const throw() {
            return m_expression;
        }

        /// Source file
        const char *File() const throw() {
            return m_file;
        }

        /// Source line
        int Line() const throw() {
            return m_line;
        }

        /// Description of failure
        const char *Message() const throw() {
            return m_message.c_str();
        }

        ~AssertionFailure() throw() {
        }
    };


/// Assert that EXPRESSION evaluates to true, otherwise raise AssertionFailureException with associated MESSAGE (which may use C++ stream-style message formatting)
#define mach_assert(EXPRESSION, MESSAGE) if(!(EXPRESSION)) { throw AssertionFailure(#EXPRESSION, __FILE__, __LINE__, (AssertionFailure::StreamFormatter() << MESSAGE)); }
}

#endif //MACH_ASSERTIONFAILURE_HPP
