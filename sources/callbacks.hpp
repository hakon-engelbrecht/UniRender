#ifndef UNIRENDER_CALLBACKS_HPP
#define UNIRENDER_CALLBACKS_HPP

#include "common.h"

namespace callbacks {

    /**
     * @brief Callback for GLFW errors.
     * This function prints the error to the console.
     *
     * @param error_id error id
     * @param description error description
     */
    static void glfw_error(int error_id, const char* description) {
        std::cerr << "GLFW Error (" << error_id << "): " << description << std::endl;
    }

    /**
     * @brief Callback for closing the application.
     * This ensures that glfw is terminated.
     */
    static void exit() {
        glfwTerminate();
        std::cout << "Exiting..." << std::endl;
    }

    /**
     * @brief Callback for size changes of the framebuffer.
     * This handles the resizing of the viewport.
     *
     * @param window reference to the window
     * @param width new width
     * @param height new height
     */
    static void framebuffer_size(GLFWwindow* window, int width, int height) {
        (void) window;
        UniRender app = common::get_app();
        app.get_window().set_size(width, height);
        glViewport(0, 0, width, height);

        // todo rendering.resize()

    }

    static void window_size(GLFWwindow* window, int width, int height) {
        (void) window;
        UniRender app = common::get_app();
        app.get_window().set_real_size(width, height);
    }

    static void keyboard_event(GLFWwindow* window, int key, int scancode, int action, int mods) {
        (void) window;
        (void) key;
        (void) scancode;
        (void) action;
        (void) mods;
    }

    static void mouse_movement(GLFWwindow* window, double x_pos, double y_pos) {
        (void) window;
        (void) x_pos;
        (void) y_pos;
    }

    static void drop_path(GLFWwindow* window, int count, const char** paths) {
        (void) window;
        (void) count;
        (void) paths;
    }
}

#endif // UNIRENDER_CALLBACKS_HPP