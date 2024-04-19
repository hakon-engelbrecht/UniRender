#ifndef UNIRENDER_CALLBACKS_HPP
#define UNIRENDER_CALLBACKS_HPP

#include "common.h"

namespace callbacks {

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
        glViewport(0, 0, width, height);
    }
}

#endif // UNIRENDER_CALLBACKS_HPP