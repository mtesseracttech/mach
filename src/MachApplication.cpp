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


        Vec3 v5 = v2.cross(v4);
        Vec3 v6 = Vec3::cross(v2, v4);

        std::cout << v5 << std::endl;
        std::cout << v6 << std::endl;
        std::cout << Vec3::distance(v5, v6 + Vec3(30, 40, 50)) << std::endl;

        Mat2 m0;

        std::cout << "sizeof float: " << sizeof(float) << std::endl;
        std::cout << "sizeof Vec2: " << sizeof(v1) << std::endl;

        std::cout << m0 << std::endl;

        Mat2x2 m1(1.0, 2.0, 3.0, 4.0);
        Mat2x2 m2(3.0, 4.0, 5.0, 6.0);

        Mat2x2 m3 = m1 * m2;


        std::cout << m1 << std::endl;

        std::cout << "Math test end" << std::endl;
    }
}

int main() {
    mach::MachApplication app;
    app.test();
    app.run();
}

