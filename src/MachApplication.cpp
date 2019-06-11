#include <iostream>
#include <math/linalg/LinMatTypes.hpp>
#include "graphics/window/OpenGLWindow.hpp"
#include "io/KeyInput.hpp"
#include "io/MouseInput.hpp"
#include "MachApplication.hpp"

namespace mach {

    MachApplication::MachApplication() {
        m_window = new OpenGlWindow();
        setup_subsystems();
    }

    void MachApplication::setup_subsystems() {
        mach::KeyInput::setup(*m_window);
        mach::MouseInput::setup(*m_window);
    }

    void MachApplication::run() {
        while (!m_window->is_closing()) {
            m_window->swap_buffers();
            m_window->poll_events();
        }
        shutdown();
    }


    void MachApplication::shutdown() {
        m_window->close();
    }

    void MachApplication::test() {
        std::cout << "Math tests begin" << std::endl;

        Vec2 v1(10, -15);
        Vec3 v2(-123, 75, 21);
        Vec4 v3(12345, -1345, 2895, -12983);
        Vec3 v4(-123, 74, -21);
        Vec3 v7(-.1232, -23, 6603);

        std::cout << v4 << " + " << v7 << " = " << v4 + v7 << std::endl;


        Vec3 v5 = v2.cross(v4);
        Vec3 v6 = Vec3::cross(v2, v4);

        std::cout << v5 << std::endl;
        std::cout << v6 << std::endl;
        std::cout << Vec3::distance(v5, v6 + Vec3(30, 40, 50)) << std::endl;

        Mat2 m0;
        std::cout << m0 << std::endl;

        Mat2x3 m1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
        std::cout << "m1:" << std::endl << m1 << std::endl;
        Mat3x2 m2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
        std::cout << "m2:" << std::endl << m2 << std::endl;

        auto m2_t = m2.transpose();
        std::cout << "m2 transpose:" << std::endl << m2_t << std::endl;
        std::cout << "m1 * m2:" << std::endl << m1 * m2 << std::endl;

        Mat4x4 m5 = Mat4x4::identity();
        std::cout << "mat4x4 identity:" << std::endl << m5 << std::endl;

        Mat4x2 m6 = Mat4x2::zero();
        std::cout << "mat4x2 zero:" << std::endl << m6 << std::endl;


        std::cout << "identity * v3 = " << m5 * v3 << std::endl;

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

        std::cout << std::scientific << "Float min: " << std::numeric_limits<float>::min() << std::endl;

        std::cout << std::scientific << "Float max: " << std::numeric_limits<float>::max() << std::endl;

        std::cout << "Math test end" << std::endl;

        Quat q0 = Quat(1.0, 0.0, 0.0, 0.0);

    }
}

int main() {
    mach::MachApplication app;
    app.test();
    app.run();
}

