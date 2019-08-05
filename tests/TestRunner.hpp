//
// Created by mtesseract on 22-6-19.
//

#ifndef MACH_TESTRUNNER_HPP
#define MACH_TESTRUNNER_HPP

#include "LinearAlgebraTests.hpp"
#include "CoreEngineTests.hpp"

namespace mach::tests {
	static void run_tests() {
		Logger::log("RUNNING TEST SUITES:");

		math::LinearAlgebraTests::run_tests();
		core::CoreEngineTests::run_tests();
	}
}

#endif //MACH_TESTRUNNER_HPP
