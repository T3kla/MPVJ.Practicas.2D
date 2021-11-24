#include "game.h"
#include "glfw3.h"
#include <iostream>

namespace tkl
{

game game::instance;

game::game()
{
}

game &game::get()
{
    return instance;
}

// void onMouseClicked(GLFWwindow *window, int button, int action, int mods)
//{
//     if (GLFW_PRESS == action) // 0 = released, 1 = pressed
//     {
//     }
// }
//
// void onKeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods)
//{
//     if (GLFW_KEY_F == key) // 0 = released, 1 = pressed, 2 = repetition
//     {
//         std::cout << "Pressed F lol: " << action << std::endl;
//     }
// }

void game::init()
{
}

static auto next = [](auto &it) { it += 1u - TIME_AVG_SAMPLES * (it == TIME_AVG_SAMPLES - 1u); };

void game::loop()
{
    m_time.update();

    auto delta = m_time.get_delta_unscaled();

    m_avg_up[m_avg_up_it] = delta;
    next(m_avg_up_it);

    m_fx_count += delta;
    update(delta);

    if (m_fx_count >= TIME_FIXED_FREQ)
    {
        m_avg_fx[m_avg_fx_it] = m_fx_count;
        next(m_avg_fx_it);

        fixed(m_fx_count * m_time.get_scale());
        m_fx_count = 0;
    }
}

void game::exit()
{
}

void game::update(double dt)
{
}

void game::fixed(double dt)
{
    print_fps();
}

void game::print_fps()
{
    m_avg_buffer_up = 0.;
    m_avg_buffer_fx = 0.;

    for (auto &&i : m_avg_up)
        m_avg_buffer_up += i;
    for (auto &&i : m_avg_fx)
        m_avg_buffer_fx += i;

    m_avg_buffer_up /= (double)TIME_AVG_SAMPLES;
    m_avg_buffer_fx /= (double)TIME_AVG_SAMPLES;

    m_avg_buffer_up = 1. / (m_avg_buffer_up / 1000.);
    m_avg_buffer_fx = 1. / (m_avg_buffer_fx / 1000.);

    // Only works disabling VSync
    std::cout << " fixed: " << m_avg_buffer_fx << std::endl;
    std::cout << "update: " << m_avg_buffer_up << std::endl;
}

} // namespace tkl
