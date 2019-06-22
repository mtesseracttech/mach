//
// Created by MTesseracT on 2019-06-22.
//

#ifndef MACH_MACHASSERTION_HPP
#define MACH_MACHASSERTION_HPP

#include <exception>
#include <string>
#include <sstream>
#include <iostream>
#include <auxiliary/logging/Logger.hpp>
#include <cassert>

namespace mach {
	// Exception type for assertion failures
	class MachAssertionException : public std::exception {
	private:
		const char *m_expression;
		const char *m_file;
		int m_line;
		std::string m_message;
		std::string m_report;

	public:
		class StreamFormatter {

		private:
			std::ostringstream m_stream;

		public:
			operator std::string() const {
				return m_stream.str();
			}

			template<typename T>
			StreamFormatter &operator<<(const T &p_value) {
				m_stream << p_value;
				return *this;
			}
		};

		// Log error before throwing
		void log_error() {
			Logger::log(m_report, LogError);
		}

		MachAssertionException(const char *p_expression, const char *p_file, int p_line, const std::string &p_message)
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

		virtual const char *what() const noexcept {
			return m_report.c_str();
		}

		const char *expression() const noexcept {
			return m_expression;
		}

		const char *file() const noexcept {
			return m_file;
		}

		int line() const noexcept {
			return m_line;
		}

		const char *message() const noexcept {
			return m_message.c_str();
		}

		~MachAssertionException() noexcept {}

		static void
		__mach_assert_fail(const char *p_expression, const char *p_file, int p_line, const std::string &p_message) {
			throw MachAssertionException(p_expression, p_file, p_line, p_message);
		}

		//mach_assert does not exist during release
#ifdef NDEBUG
#define mach_assert(expr, mess) ((void)0)
#else
		// Assert that expr evaluates to true, otherwise raise AssertionFailureException with associated MESSAGE (which may use C++ stream-style message formatting)
#define mach_assert(expr, message) \
    (static_cast<bool> (expr) \
    ? (void(0)) \
    : mach::MachAssertionException::__mach_assert_fail(#expr, __FILE__, __LINE__, (mach::MachAssertionException::StreamFormatter() << message)))
#endif
	};
}

#endif //MACH_MACHASSERTION_HPP