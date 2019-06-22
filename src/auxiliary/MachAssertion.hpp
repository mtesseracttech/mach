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

		// Helper class for formatting assertion message
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

		// Log error before throwing
		void log_error() {
			Logger::log(m_report, LogError);
			//std::cerr << m_report << std::endl;
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

		~MachAssertionException() noexcept {
		}
	};

	//MACH_ASSERT does not exist during release
#ifdef NDEBUG
#define MACH_ASSERT(EXPRESSION, MESSAGE) ((void)0)
#else
	// Assert that EXPRESSION evaluates to true, otherwise raise AssertionFailureException with associated MESSAGE (which may use C++ stream-style message formatting)
#define MACH_ASSERT(EXPRESSION, MESSAGE) if(!(EXPRESSION)) { throw mach::MachAssertionException(#EXPRESSION, __FILE__, __LINE__, (mach::MachAssertionException::StreamFormatter() << MESSAGE)); }
#endif
}

#endif //MACH_MACHASSERTION_HPP
