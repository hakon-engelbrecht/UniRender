#ifndef UNIRENDER_COMMON_H
#define UNIRENDER_COMMON_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <iostream>
#include "window.h"


class UniRender {

    /**
     * The window object.
     */
    Window _window;

public:
    UniRender() {
        this->_window = Window();
    }

    void mainloop() {
        _window.mainloop();
    }

    Window get_window() {
        return _window;
    }
};

UniRender APP = UniRender();

namespace common {

    static UniRender get_app() {
        return APP;
    }
};


#endif //UNIRENDER_COMMON_H
