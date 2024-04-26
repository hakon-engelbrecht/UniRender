#include "common.h"
#include "input.h"

Input::Input() {
    this->_show_help = false;
    this->_show_menu = false;
    this->_show_stats = false;

    this->_show_wireframe = false;
    this->_show_skybox = true;

    this->_tesselate = false;
    this->_use_heightmap = false;

    this->_paused = false;
    this->_mouse_looking = false;

    this->_mouse_last_x = 0.0f;
    this->_mouse_last_y = 0.0f;
}

void Input::process() {
    UniRender app = common::get_app();
    Camera camera = this->_camera;
    GLFWwindow* glfw_window = app.get_window().get_glfw_window();
    const float delta_time = (float ) app.get_window().get_delta_time();
    const bool shift = glfwGetKey(glfw_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

    if (glfwGetKey(glfw_window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.process_keyboard(FORWARD, shift, delta_time);
    }

    if (glfwGetKey(glfw_window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.process_keyboard(BACKWARD, shift, delta_time);
    }

    if (glfwGetKey(glfw_window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.process_keyboard(LEFT, shift, delta_time);
    }

    if (glfwGetKey(glfw_window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.process_keyboard(RIGHT, shift, delta_time);
    }

    if (glfwGetKey(glfw_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.process_keyboard(UP, shift, delta_time);
    }

    if (glfwGetKey(glfw_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        camera.process_keyboard(DOWN, shift, delta_time);
    }
}

void Input::event(int key, int action, int mods) {
    (void) mods;
    Window window = common::get_app().get_window();

    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window.get_glfw_window(), GLFW_TRUE);
                break;
            case GLFW_KEY_F1:
                this->_show_help = !this->_show_help;
                break;
            case GLFW_KEY_F2:
                window.set_fullscreen(!window.get_fullscreen());
                window.update_fullscreen();
                break;
            case GLFW_KEY_F3:
                this->_show_wireframe = !this->_show_wireframe;
                break;
            case GLFW_KEY_F4:
                this->_show_menu = !this->_show_menu;
                break;
            case GLFW_KEY_F5:
                this->_show_stats = !this->_show_stats;
                break;
            case GLFW_KEY_F6:
                // todo screenshot
                break;
            case GLFW_KEY_P:
                this->_paused = !this->_paused;
                break;
            default:
                break;
        }
    }
}

void Input::mouse_move(double x_pos, double y_pos) {
    if (this->_mouse_looking) {
        Camera camera = this->_camera;
        GLFWwindow *glfw_window = common::get_app().get_window().get_glfw_window();

        const double x_offset = x_pos - this->_mouse_last_x;
        const double y_offset = this->_mouse_last_y - y_pos;

        this->_mouse_last_x = x_pos;
        this->_mouse_last_y = y_pos;

        camera.process_mouse_input(x_offset, y_offset);

        this->_mouse_looking = glfwGetMouseButton(glfw_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    }
}

void Input::mouse_action(int button, int action, int mods) {
    (void) mods;

    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            this->_mouse_looking = true;
            GLFWwindow *glfw_window = common::get_app().get_window().get_glfw_window();
            double x_pos, y_pos;
            glfwGetCursorPos(glfw_window, &x_pos, &y_pos);
            this->_mouse_last_x = x_pos;
            this->_mouse_last_y = y_pos;
        } else {
            this->_mouse_looking = false;
        }
    }
}

void Input::mouse_scroll(double x_offset, double y_offset) {
    (void) x_offset;
    this->_camera.process_mouse_zoom(y_offset);
}

void Input::user_selected_file(const char *path) {
    (void) path;

    // todo implement
}
