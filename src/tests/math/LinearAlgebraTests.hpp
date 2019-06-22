//
// Created by mtesseract on 22-6-19.
//

#ifndef MACH_LINEARALGEBRATESTS_HPP
#define MACH_LINEARALGEBRATESTS_HPP

#include <iostream>
#include <math/linalg/LinMatTypes.hpp>
#include <cassert>

namespace mach::tests::math {
    class LinearAlgebraTests {
    public:
        static void run_tests();

    private:
        static void vector_tests();

        static void matrix_tests();

        static void quaternion_tests();
    };

    void LinearAlgebraTests::run_tests() {
        std::cout << "Linear Algebra tests running:" << std::endl;

        vector_tests();
        matrix_tests();
        quaternion_tests();
    }

    void LinearAlgebraTests::vector_tests() {
        std::cout << "Running vector tests" << std::endl;

        std::cout << "Initialization tests running:" << std::endl;
        Vec2 vec2(10, -15);
        assert(vec2.x == 10.f && vec2.y == -15.f);
        Vec3 vec3(-123, 75, 21);
        assert(vec3.x == -123.f && vec3.y == 75.f && vec3.z == 21.f);
        Vec4 vec4(12345, -1345, 2895, -12983);
        assert(vec4.x == 12345.f && vec4.y == -1345.f && vec4.z == 2895.f && vec4.w == -12983.f);

        std::cout << "Vector size tests running. " << std::endl;
        assert(sizeof(Vec2) == sizeof(float) * 2);
        assert(sizeof(Vec3) == sizeof(float) * 3);
        assert(sizeof(Vec4) == sizeof(float) * 4);
        assert(sizeof(Vec2h) == sizeof(double) * 2);
        assert(sizeof(Vec3h) == sizeof(double) * 3);
        assert(sizeof(Vec4h) == sizeof(double) * 4);
        std::cout << "Vector size tests passed. " << std::endl;

        std::cout << "Index operator tests: " << std::endl;
        assert(vec2[0] == 10.f && vec2[1] == -15.f);
        assert(vec3[0] == -123.f && vec3[1] == 75.f && vec3[2] == 21.f);
        assert(vec4[0] == 12345.f && vec4[1] == -1345.f && vec4[2] == 2895.f && vec4[3] == -12983.f);

        std::cout << "Zero/One tests:" << std::endl;
        Vec2 v2_zero = Vec2::zero();
        Vec4 v4_one = Vec4::one();
        assert(v2_zero.x == 0.f && v2_zero.y == 0.f);
        assert(v4_one.x == 1.f && v4_one.y == 1.f && v4_one.z == 1.f && v4_one.w == 1.f);

        Vec3 v_a(-0.5, 75, -20);
        Vec3 v_b(10.5, -10, 30);
        float s = 100.0f;

        std::cout << "Addition tests:" << std::endl;
        Vec3 v_a_plus_b(10, 65, 10);
        assert(v_a + v_b == v_a_plus_b);

        std::cout << "Subtraction tests:" << std::endl;
        Vec3 v_a_minus_b(-11, 85, -50);
        assert(v_a - v_b == v_a_minus_b);

        std::cout << "Memberwise Multiplication tests:" << std::endl;
        Vec3 v_a_times_b(-5.25, -750, -600);
        assert(v_a * v_b == v_a_times_b);

        std::cout << "Memberwise Division tests:" << std::endl;
        Vec3 v_a_div_b(-0.04761904761, -7.5, -0.66666666666);
        assert(v_a / v_b == v_a_div_b);

        std::cout << "Scaling tests:" << std::endl;
        Vec3 v_a_scaled_by_s(-50, 7500, -2000);
        assert(v_a * s == v_a_scaled_by_s);

        std::cout << "Division scaling tests:" << std::endl;
        Vec3 v_a_divided_by_s(-0.005, 0.75, -0.2);
        assert(v_a / s == v_a_divided_by_s);

        std::cout << "Dot product tests:" << std::endl;
        assert(Vec3::dot(Vec3::up(), Vec3::right()) == 0.0);
        assert(Vec3::dot(Vec3::up(), Vec3::up()) == 1.0);
        assert(Vec3::dot(Vec3::up(), -Vec3::up()) == -1.0);

        std::cout << "Cross product tests:" << std::endl;
        assert(Vec3::cross(Vec3::up(), Vec3::right()) == -Vec3::forward());

        std::cout << "Negation tests:" << std::endl;
        Vec3 backward(0, 0, -1);
        assert(-backward == Vec3::forward());

        std::cout << "Magnitude tests:" << std::endl;
        Vec2 vec_mag_5(3, 4);
        assert(vec_mag_5.length_squared() == 25.0f);
        assert(vec_mag_5.length() == 5.0f);

        std::cout << "Normalization tests:" << std::endl;
        Vec2 thirty_deg_vec_n = vec_mag_5.normalized();
        assert(thirty_deg_vec_n.x == 3.0f / 5.0f && thirty_deg_vec_n.y == 4.0f / 5.0f);
        assert(thirty_deg_vec_n.length_squared() == 1.0f);
        assert(thirty_deg_vec_n.length() == 1.0f);

        std::cout << "Distance tests:" << std::endl;
        assert(Vec3::distance(v_a, v_b) == Vec3::distance(v_b, v_a) && (v_b - v_a).length());

        std::cout << "Reflect tests:" << std::endl;
        assert(Vec3::reflect(Vec3(0, -1, 0), Vec3::up()) == Vec3::up());
        assert(Vec3::reflect(Vec3(0, -1, -1).normalized(), Vec3::up()) == Vec3(0, 1, -1).normalized());
        assert(Vec3::reflect(Vec3(0, -1, -1).normalized(), -Vec3::right()) == Vec3(0, -1, -1).normalized());

        std::cout << "Refract tests:" << std::endl;
        assert(Vec3::refract(Vec3(-1, -1, 0).normalized(), Vec3::up(), 1.0) == Vec3(-1, -1, 0).normalized());

        std::cout << "Clamp tests:" << std::endl;
        assert(Vec3::clamp(Vec3(50, 32, -210), -10, 35) == Vec3(35, 32, -10));

        std::cout << "Mix/interpolation tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Clamp tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Getting largest/smallest indices tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Vector tests done!" << std::endl;
    }

    void LinearAlgebraTests::matrix_tests() {
        std::cout << "Running matrix tests" << std::endl;

        std::cout << "Initialization tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Dimensions tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Index operators tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Row/column getters tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Identity/zero tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Transpose tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Matrix Multiplication tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Matrix-Vector product tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Matrix-Scalar product tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Matrix-Scalar division tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Determinant tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Adjugate tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Inverse tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Rotation matrix tests" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Translation matrix tests" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Scaling matrix tests" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Matrix tests done!" << std::endl;


        Mat2 m0;
        std::cout << m0 << std::endl;

        Mat2x3 m1(1.0, 2.0, 3.0,
                  4.0, 5.0, 6.0);
        std::cout << "m1:" << std::endl << m1 << std::endl;
        Mat3x2 m2(1.0, 2.0,
                  3.0, 4.0,
                  5.0, 6.0);
        std::cout << "m2:" << std::endl << m2 << std::endl;

        auto m2_t = m2.transpose();
        std::cout << "m2 transpose:" << std::endl << m2_t << std::endl;
        std::cout << "m1 * m2:" << std::endl << m1 * m2 << std::endl;

        Mat4x4 m5 = Mat4x4::identity();
        std::cout << "mat4x4 identity:" << std::endl << m5 << std::endl;

        Mat4x2 m6 = Mat4x2::zero();
        std::cout << "mat4x2 zero: " << std::endl << m6 << std::endl;

        Vec4 vec4(-123, 75, 21, 100);
        std::cout << "identity * v3 = " << m5 * vec4 << std::endl;

        Mat2 m7 = Mat2(1, -4,
                       4, -7);

        std::cout << "adj " << std::endl << m7.adjugate() << std::endl;


        Mat3 m8 = Mat3(3, 1, 1,
                       1, 3, -1,
                       2, 4, 1);

        std::cout << "original: " << std::endl << m8 << std::endl;

        std::cout << "adj: " << std::endl << m8.adjugate() << std::endl;

        std::cout << "det: " << m8.determinant() << std::endl;

        std::cout << "inv: " << std::endl << m8.inverse() << std::endl;

        std::cout << "inv * orig = I : " << std::endl << m8 * m8.inverse() << std::endl;

        Mat4 m9 = Mat4(3, 1, 1, 2,
                       1, 3, -1, -9,
                       2, 5.4, 12, 34,
                       2, 4, -1, 13);

        std::cout << "m9: " << std::endl << m9 << "m9 inv: " << std::endl << m9.inverse() << "inv * orig = I : "
                  << std::endl << m9 * m9.inverse() << std::endl;

        std::cout << (((m9 * m9.inverse())) == Mat4::identity()) << std::endl;
    }

    void LinearAlgebraTests::quaternion_tests() {
        std::cout << "Running quaternion tests" << std::endl;

        std::cout << "Identity tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Multiplication tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Addition tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Subtraction tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Negation tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Conjugate tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Inverse tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Quaternion Vector product tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Dot product tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Magnitude tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Normalization tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Pow tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Exp tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Log tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Lerp tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Lerp Norm tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Slerp tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Fast-Slerp (experimental) tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "To Angle Axis tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "From Angle Axis tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "From Euler Angles tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "From Matrix tests:" << std::endl;
        throw NotImplemented("Missing tests");

        std::cout << "Quaternion tests done!" << std::endl;


        Quat q0(1.0, 0.0, 0.0, 0.0);
        Quat q1(1.0, 0.0, 1.0, 0.0);
        q1.normalize();
        Quat q2 = Quat::identity();

        std::cout << "Start: " << q0 << " Ending: " << q1 << std::endl;
        int steps = 20;
        for (int i = 0; i <= steps; ++i) {
            float t = (float) i / steps;
            std::cout << " t: " << t;
            q2 = Quat::lerp_norm(q0, q1, t);
            std::cout << " lerp_norm: " << q2;
            q2 = Quat::slerp(q0, q1, t);
            std::cout << " slerp: " << q2 << std::endl;
        }

        Mat3 m10 = Mat3::identity();
        Quat q4 = Quat::from_matrix(m10);

        std::cout << m10 << std::endl << q4 << std::endl;
        std::cout << sizeof(Quat) << std::endl;
    }


}

#endif //MACH_LINEARALGEBRATESTS_HPP
