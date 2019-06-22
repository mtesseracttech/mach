//
// Created by mtesseract on 22-6-19.
//

#ifndef MACH_TESTRUNNER_HPP
#define MACH_TESTRUNNER_HPP

#include <tests/math/LinearAlgebraTests.hpp>

namespace mach {
	namespace tests {
		static void run_tests() {
			std::cout << "Running test suites:" << std::endl;

			math::LinearAlgebraTests::run_tests();
		}
	}
}

#endif //MACH_TESTRUNNER_HPP
