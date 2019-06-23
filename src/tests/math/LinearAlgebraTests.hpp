//
// Created by mtesseract on 22-6-19.
//

#ifndef MACH_LINEARALGEBRATESTS_HPP
#define MACH_LINEARALGEBRATESTS_HPP

#include <iostream>
#include <math/linalg/LinAlgTypes.hpp>
#include <auxiliary/logging/LogUtils.hpp>
#include <auxiliary/MachAssertion.hpp>
#include <math/util/MathUtils.hpp>

namespace mach::tests::math {
	class LinearAlgebraTests {
	public:
		static void run_tests();

	private:
		static void vector_tests();

		static void matrix_tests();

		static void quaternion_tests();

		static void rotation_tests();

		static void other_tests();
	};

	void LinearAlgebraTests::run_tests() {
		Logger::log("LINEAR ALGEBRA TESTS:");

		vector_tests();
		matrix_tests();
		quaternion_tests();
		rotation_tests();
		other_tests();
	}

	void LinearAlgebraTests::vector_tests() {
		Logger::log("VECTOR TESTS");

		Vec3 v_a(-0.5, 75, -20);
		Vec3 v_b(10.5, -10, 30);
		float s = 100.0f;

		std::string info =
				"Test variables: v_a = " + to_str(v_a) + ", v_b = " + to_str(v_b) + ", s = " + to_str(s) + ".";
		Logger::log(info);

		Vec2 vec2(10, -15);
		mach_assert(vec2.x == 10.f && vec2.y == -15.f, "");
		Vec3 vec3(-123, 75, 21);
		mach_assert(vec3.x == -123.f && vec3.y == 75.f && vec3.z == 21.f, "");
		Vec4 vec4(12345, -1345, 2895, -12983);
		mach_assert(vec4.x == 12345.f && vec4.y == -1345.f && vec4.z == 2895.f && vec4.w == -12983.f, "");
		Logger::log("Initialization: OK");

		static_assert(sizeof(Vec2) == sizeof(float) * 2, "");
		static_assert(sizeof(Vec3) == sizeof(float) * 3, "");
		static_assert(sizeof(Vec4) == sizeof(float) * 4, "");
		static_assert(sizeof(Vec2h) == sizeof(double) * 2, "");
		static_assert(sizeof(Vec3h) == sizeof(double) * 3, "");
		static_assert(sizeof(Vec4h) == sizeof(double) * 4, "");
		Logger::log("Vector size: OK");

		mach_assert(vec2[0] == 10.f && vec2[1] == -15.f, "");
		mach_assert(vec3[0] == -123.f && vec3[1] == 75.f && vec3[2] == 21.f, "");
		mach_assert(vec4[0] == 12345.f && vec4[1] == -1345.f && vec4[2] == 2895.f && vec4[3] == -12983.f, "");
		Logger::log("Index operators: OK");

		Vec2 v2_zero = Vec2::zero();
		Vec4 v4_one = Vec4::one();
		mach_assert(v2_zero.x == 0.f && v2_zero.y == 0.f, "");
		mach_assert(v4_one.x == 1.f && v4_one.y == 1.f && v4_one.z == 1.f && v4_one.w == 1.f, "");
		Logger::log("Zero/One: OK");

		Vec3 v_a_plus_b(10, 65, 10);
		mach_assert(v_a + v_b == v_a_plus_b, "");
		Logger::log("Addition: OK");

		Vec3 v_a_minus_b(-11, 85, -50);
		mach_assert(v_a - v_b == v_a_minus_b, "");
		Logger::log("Subtraction: OK");

		Vec3 v_a_times_b(-5.25, -750, -600);
		mach_assert(v_a * v_b == v_a_times_b, "");
		Logger::log("Memberwise Multiplication tests: OK");

		Vec3 v_a_div_b(-0.04761904761, -7.5, -0.66666666666);
		mach_assert(v_a / v_b == v_a_div_b, "");
		Logger::log("Memberwise Division: OK");

		Vec3 v_a_scaled_by_s(-50, 7500, -2000);
		mach_assert(v_a * s == v_a_scaled_by_s, "");
		Logger::log("Scaling: OK");

		Vec3 v_a_divided_by_s(-0.005, 0.75, -0.2);
		mach_assert(v_a / s == v_a_divided_by_s, "");
		Logger::log("Division scaling: OK");

		mach_assert(Vec3::dot(Vec3::up(), Vec3::right()) == 0.0, "");
		mach_assert(Vec3::dot(Vec3::up(), Vec3::up()) == 1.0, "");
		mach_assert(Vec3::dot(Vec3::up(), -Vec3::up()) == -1.0, "");
		Logger::log("Dot product: OK");

		mach_assert(Vec3::cross(Vec3::up(), Vec3::right()) == -Vec3::forward(), "");
		Logger::log("Cross product: OK");

		Vec3 backward(0, 0, -1);
		mach_assert(-backward == Vec3::forward(), "");
		Logger::log("Negation: OK");

		Vec2 vec_mag_5(3, 4);
		mach_assert(vec_mag_5.length_squared() == 25.0f, "");
		mach_assert(vec_mag_5.length() == 5.0f, "");
		Logger::log("Magnitude: OK");

		Vec2 thirty_deg_vec_n = vec_mag_5.normalized();
		mach_assert(thirty_deg_vec_n.x == 3.0f / 5.0f && thirty_deg_vec_n.y == 4.0f / 5.0f, "");
		mach_assert(thirty_deg_vec_n.length_squared() == 1.0f, "");
		mach_assert(thirty_deg_vec_n.length() == 1.0f, "");
		Logger::log("Normalization: OK");


		mach_assert(Vec3::distance(v_a, v_b) == Vec3::distance(v_b, v_a) && (v_b - v_a).length(), "");
		Logger::log("Distance: OK");

		mach_assert(Vec3::reflect(Vec3(0, -1, 0), Vec3::up()) == Vec3::up(), "");
		mach_assert(Vec3::reflect(Vec3(0, -1, -1).normalized(), Vec3::up()) == Vec3(0, 1, -1).normalized(), "");
		mach_assert(Vec3::reflect(Vec3(0, -1, -1).normalized(), -Vec3::right()) == Vec3(0, -1, -1).normalized(), "");
		Logger::log("Reflect: OK");

		mach_assert(Vec3::refract(Vec3(-1, -1, 0).normalized(), Vec3::up(), 1.0) == Vec3(-1, -1, 0).normalized(), "");
		Logger::log("Refract: OK");

		mach_assert(Vec3::clamp(Vec3(50, 32, -210), -10, 35) == Vec3(35, 32, -10), "");
		Logger::log("Clamp: OK");

		mach_assert(Vec3::mix(v_a, v_b, 0.5) == v_a + ((v_b - v_a) / 2), "");
		mach_assert(Vec3::mix(v_a, v_b, Vec3(0.2, 0.5, 0.7)) == v_a + ((v_b - v_a) * Vec3(0.2, 0.5, 0.7)), "");
		Logger::log("Mix/interpolation: OK");

		mach_assert(v_a.get_largest() == 75.0f, "");
		mach_assert(v_b.get_smallest() == -10.0f, "");
		mach_assert(v_a.get_smallest_index() == 2, "");
		mach_assert(v_b.get_largest_index() == 2, "");
		Logger::log("Getting largest/smallest indices: OK");


		Logger::log("VECTOR TESTS: PASSED");
	}

	void LinearAlgebraTests::matrix_tests() {
		Logger::log("MATRIX TESTS");

		Mat4 m_4_i(1.0, 0.0, 0.0, 0.0,
		           0.0, 1.0, 0.0, 0.0,
		           0.0, 0.0, 1.0, 0.0,
		           0.0, 0.0, 0.0, 1.0);
		Mat2x3 m_23(1.0, 2.0, 3.0,
		            4.0, 5.0, 6.0);
		Mat3x2 m_32(1.0, 2.0,
		            3.0, 4.0,
		            5.0, 6.0);
		Mat3 m_3(2, 8, 4,
		         4, 2, 8,
		         8, 4, 2);

		std::string info =
				"Test variables: \nm_4_i = " + to_str(m_4_i) +
				", \nm_23 = \n" + to_str(m_23) +
				", \nm_32 = \n" + to_str(m_32) +
				", \nm_3 = \n" + to_str(m_3) + ".";
		Logger::log(info);

		static_assert(sizeof(Mat2) == sizeof(float) * 4, "");
		static_assert(sizeof(Mat3) == sizeof(float) * 9, "");
		static_assert(sizeof(Mat4) == sizeof(float) * 16, "");
		static_assert(sizeof(Mat2h) == sizeof(double) * 4, "");
		static_assert(sizeof(Mat3h) == sizeof(double) * 9, "");
		static_assert(sizeof(Mat4h) == sizeof(double) * 16, "");

		Logger::log("Initialization: DONE");

		mach_assert(m_32.width() == 2, "");
		mach_assert(m_32.height() == 3, "");
		mach_assert(m_4_i.size() == 16, "");
		Logger::log("Dimensions: DONE");

		mach_assert(m_23[1][0] == 4.0, "");
		mach_assert(m_32[1][0] == 3.0, "");
		Logger::log("Index operators: DONE");

		mach_assert(m_23.row(1) == Vec3(4, 5, 6), "");
		mach_assert(m_32.row(1) == Vec2(3, 4), "");
		Logger::log("Row/column getters: DONE");

		mach_assert(m_4_i == Mat4::identity(), "");
		mach_assert(Mat4(0.0) == Mat4::zero(), "");
		Logger::log("Identity/zero: DONE");

		Mat3x2 m_23_t(1.0, 4.0,
		              2.0, 5.0,
		              3.0, 6.0);
		mach_assert(m_23.transpose() == m_23_t, "");
		mach_assert(Mat4::identity().transpose() == Mat4::identity(), "");
		Logger::log("Transpose: DONE");


		Mat2 m_23_times_m_32(22, 28,
		                     49, 64);
		mach_assert(m_23 * m_32 == m_23_times_m_32, "");
		mach_assert(m_23_times_m_32 * Mat2::identity() == m_23_times_m_32, "");
		Logger::log("Matrix Multiplication: DONE");

		Vec4 v_4(1, 2, 3, 4);
		Mat4 m_4_2i(2, 0, 0, 0,
		            0, 2, 0, 0,
		            0, 0, 2, 0,
		            0, 0, 0, 2);
		mach_assert(m_4_2i * v_4 == v_4 * 2, "");
		Logger::log("Matrix-Vector product: DONE");

		mach_assert(Mat4::identity() * 2.0 == m_4_2i, "");
		Logger::log("Matrix-Scalar product: DONE");

		mach_assert(m_4_2i / 2.0 == Mat4::identity(), "");
		Logger::log("Matrix-Scalar division: DONE");

		mach_assert(m_3.determinant() == 392, "");
		Logger::log("Determinant: DONE");

		mach_assert(m_3 * m_3.inverse() == Mat3::identity(), "");
		Logger::log("Inverse: DONE");

//		Logger::log("Rotation matrix: DONE");
//		throw NotImplemented("Missing tests");
//
//		Logger::log("Translation matrix: DONE");
//		throw NotImplemented("Missing tests");
//
//		Logger::log("Scaling matrix: DONE");
//		throw NotImplemented("Missing tests");

		Logger::log("MATRIX TESTS: PASSED");
	}

	void LinearAlgebraTests::quaternion_tests() {
		Logger::log("QUATERNION TESTS");

		Quat q_i(1, 0, 0, 0);
		Quat q_u(std::sqrt(2) / 2, 0, 0, std::sqrt(2) / 2);
		Logger::log("Initialization: DONE");

		mach_assert(Quat::identity() == q_i, "");
		Logger::log("Identity: DONE");

		mach_assert(q_u * Quat::identity() == q_u, "");
		mach_assert(q_u * q_u == Quat(0, 0, 0, 1), "");
		Logger::log("Multiplication: DONE");

		mach_assert(Quat::identity() + q_u == Quat(1 + std::sqrt(2) / 2, 0, 0, std::sqrt(2) / 2), "");
		Logger::log("Addition: DONE");

		mach_assert(Quat::identity() - q_u == Quat(1 - std::sqrt(2) / 2, 0, 0, -std::sqrt(2) / 2), "");
		Logger::log("Subtraction: DONE");

		mach_assert(-q_u == Quat(-std::sqrt(2) / 2, 0, 0, -std::sqrt(2) / 2), "");
		Logger::log("Negation: DONE");

		mach_assert(q_u.conjugate() == Quat(std::sqrt(2) / 2, 0, 0, -std::sqrt(2) / 2), "");
		Logger::log("Conjugate: DONE");

		mach_assert(q_u * q_u.inverse() == Quat::identity(), "");
		Logger::log("Inverse: DONE");

		mach_assert(Vec3::right() * q_u == Vec3::up(), "");
		Logger::log("Vector-Quaternion transformation: DONE");

		mach_assert(approx_eq<float>(Quat::dot(Quat::identity(), q_u), std::sqrt(2.0) / 2.0), "");
		mach_assert(approx_eq<float>(Quat::dot(q_u, q_u), 1), "");
		Logger::log("Dot product: DONE");

		mach_assert(approx_eq<float>(q_u.magnitude_squared(), 1), "");
		mach_assert(approx_eq<float>(q_u.magnitude(), 1), "");
		Logger::log("Magnitude: DONE");

		mach_assert(Quat(1, 0, 0, 1).normalized() == q_u, "");
		Logger::log("Normalization: DONE");

		auto w = MathUtils<float>::lerp(1.0, std::sqrt(2.0) / 2, 0.5);
		auto z = MathUtils<float>::lerp(0.0, std::sqrt(2.0) / 2, 0.5);
		mach_assert(Quat::lerp(Quat::identity(), q_u, 0.5) == Quat(w, 0, 0, z), "");
		Logger::log("Lerp: DONE");

		mach_assert(Quat::lerp_norm(Quat::identity(), q_u, 0.5) == Quat(w, 0, 0, z).normalized(), "");
		Logger::log("Lerp Norm: DONE");

		mach_assert(Quat::slerp(Quat::identity(), q_u, 0.0) == Quat::lerp_norm(Quat::identity(), q_u, 0.0), "");
		mach_assert(Quat::slerp(Quat::identity(), q_u, 0.25) != Quat::lerp_norm(Quat::identity(), q_u, 0.25), "");
		mach_assert(Quat::slerp(Quat::identity(), q_u, 0.5) == Quat::lerp_norm(Quat::identity(), q_u, 0.5), "");
		mach_assert(Quat::slerp(Quat::identity(), q_u, 0.75) != Quat::lerp_norm(Quat::identity(), q_u, 0.75), "");
		mach_assert(Quat::slerp(Quat::identity(), q_u, 1.0) == Quat::lerp_norm(Quat::identity(), q_u, 1.0), "");
		Logger::log("Slerp: DONE");

//		throw NotImplemented("Missing tests");
//		Logger::log("Pow: DONE");
//
//		throw NotImplemented("Missing tests");
//		Logger::log("Exp: DONE");
//
//		throw NotImplemented("Missing tests");
//		Logger::log("Log: DONE");
//
//		throw NotImplemented("Missing tests");
//		Logger::log("Fast-Slerp (experimental): DONE");

		Logger::log("QUATERNION TESTS: PASSED");
	}

	void LinearAlgebraTests::rotation_tests() {
		Logger::log("ROTATION CONVERSION TESTS");

//		throw NotImplemented("Missing tests");
//		Logger::log("To Angle Axis: DONE");
//
//		throw NotImplemented("Missing tests");
//		Logger::log("From Angle Axis: DONE");
//
//		throw NotImplemented("Missing tests");
//		Logger::log("From Euler Angles: DONE");
//
//		throw NotImplemented("Missing tests");
//		Logger::log("From Matrix: DONE");

		Logger::log("ROTATION CONVERSION TESTS: PASSED");
	}

	void LinearAlgebraTests::other_tests() {
		Logger::log("MISCELLANEOUS LINEAR ALGEBRA TESTS");
		Logger::log("MISCELLANEOUS LINEAR ALGEBRA TESTS: PASSED");
	}


}

#endif //MACH_LINEARALGEBRATESTS_HPP
