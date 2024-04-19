#include <vector>

#include "window.h"
#include "callbacks.hpp"

/**********************************************************************************************************************/
// public

Window::Window() {
    _width = DEFAULT_WINDOW_WIDTH;
    _height = DEFAULT_WINDOW_HEIGHT;
    _real_width = DEFAULT_WINDOW_WIDTH;
    _real_height = DEFAULT_WINDOW_HEIGHT;
    _cached_width = DEFAULT_WINDOW_WIDTH;
    _cached_height = DEFAULT_WINDOW_HEIGHT;
    _cached_x = 0;
    _cached_y = 0;
    _delta_time = 0.0;
    _last_frame = 0.0;
    _last_fps_update = 0.0;
    _fps = 0;
    _frame_counter = 0;
    _is_fullscreen = false;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, UNIRENDER_OPENGL_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, UNIRENDER_OPENGL_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _glfw_window = glfwCreateWindow(_width, _height, "Unirender", nullptr, nullptr);
    if (!_glfw_window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(_glfw_window);
    glfwSetFramebufferSizeCallback(_glfw_window, callbacks::framebuffer_size);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
}

Window::~Window() {
    glfwTerminate();
}

void Window::mainloop() {
    update_fullscreen();

    while (!glfwWindowShouldClose(_glfw_window)) {
        glfwPollEvents();

        // process input
        // render image
        // render gui

        glfwSwapBuffers(_glfw_window);
    }
}

void Window::update_fullscreen() {

    // check if something has to change
    if (_is_fullscreen != (glfwGetWindowMonitor(_glfw_window) != nullptr)) {

        if (_is_fullscreen) {

            // cache current window position and size
            glfwGetWindowPos(_glfw_window, &_cached_x, &_cached_y);
            glfwGetWindowSize(_glfw_window, &_cached_width, &_cached_height);

            // activate fullscreen
            GLFWmonitor* monitor = get_current_monitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(
                    _glfw_window, monitor,
                    0, 0,
                    mode->width, mode->height,
                    mode->refreshRate
            );

        } else {

            // restore windowed mode
            glfwSetWindowMonitor(
                    _glfw_window, nullptr,
                    _cached_x, _cached_y,
                    _cached_width, _cached_height,
                    GLFW_DONT_CARE
            );
        }
    }
}

/**********************************************************************************************************************/
// private

/**
 * @brief Get the monitor that has the most overlap with the window.
 *
 * based on: https://stackoverflow.com/a/31526753
 *
 * @return the monitor with most overlap
 */
GLFWmonitor* Window::get_current_monitor() {
    int win_x, win_y, win_width, win_height;
    int best_overlap = 0;
    GLFWmonitor *best_monitor = nullptr;

    // retrieve all monitors
    int num_monitors;
    GLFWmonitor **monitors_refs = glfwGetMonitors(&num_monitors);
    std::vector<GLFWmonitor *> monitors(monitors_refs, monitors_refs + num_monitors);

    // get size and position of window
    glfwGetWindowPos(_glfw_window, &win_x, &win_y);
    glfwGetWindowSize(_glfw_window, &win_width, &win_height);

    for (auto monitor: monitors) {

        // get size and position of monitor
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        int monitor_width = mode->width;
        int monitor_height = mode->height;
        int monitor_x, monitor_y;
        glfwGetMonitorPos(monitor, &monitor_x, &monitor_y);

        // calculate overlap
        int right_edge = std::min(win_x + win_width, monitor_x + monitor_width);
        int bottom_edge = std::min(win_y + win_height, monitor_y + monitor_height);

        int overlap = std::max(0, right_edge - std::max(win_x, monitor_x)) *
                      std::max(0, bottom_edge - std::max(win_y, monitor_y));

        // update best monitor
        if (best_overlap < overlap) {
            best_overlap = overlap;
            best_monitor = monitor;
        }
    }

    // best monitor is the one with the most overlap
    return best_monitor;
}

void Window::init_fps_timer() {
    _last_fps_update = glfwGetTime();
}