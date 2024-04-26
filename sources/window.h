#ifndef UNIRENDER_WINDOW_H
#define UNIRENDER_WINDOW_H

#include "common.h"

#define UNIRENDER_OPENGL_MAJOR 4
#define UNIRENDER_OPENGL_MINOR 1

#define DEFAULT_WINDOW_WIDTH 1200
#define DEFAULT_WINDOW_HEIGHT 800

class Window {
    int _width;
    int _height;

    int _real_width;
    int _real_height;

    int _cached_width;
    int _cached_height;

    int _cached_x;
    int _cached_y;

    double _delta_time;
    double _last_frame;
    double _last_fps_update;

    int _fps;
    int _frame_counter;

    bool _is_fullscreen;

    GLFWwindow* _glfw_window;

public:
    Window();
    ~Window();

    void mainloop();
    void update_fullscreen();

    void set_size(int width, int height);
    void set_real_size(int width, int height);
    void set_fullscreen(bool fullscreen);

    double get_delta_time();
    GLFWwindow* get_glfw_window();
    bool get_fullscreen();

private:

    GLFWmonitor* get_current_monitor();
    void init_fps_timer();
    void update_fps_timer();
};


#endif //UNIRENDER_WINDOW_H
