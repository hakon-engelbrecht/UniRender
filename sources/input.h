#ifndef UNIRENDER_INPUT_H
#define UNIRENDER_INPUT_H

#include "camera.h"

class Input {
    bool _show_help;
    bool _show_menu;
    bool _show_stats;

    bool _show_wireframe;
    bool _show_skybox;

    bool _tesselate;
    bool _use_heightmap;

    bool _paused;
    bool _mouse_looking;

    float _mouse_last_x;
    float _mouse_last_y;

    Camera _camera;

public:

    Input();

    void process();
    void event(int key, int action, int mods);
    void mouse_move(double x_pos, double y_pos);
    void mouse_action(int button, int action, int mods);
    void mouse_scroll(double x_offset, double y_offset);
    void user_selected_file(const char* path);

};


#endif //UNIRENDER_INPUT_H
