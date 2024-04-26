#ifndef UNIRENDER_CAMERA_H
#define UNIRENDER_CAMERA_H

#include <glm/glm.hpp>

#define CAMERA_SPEED 2.5f
#define CAMERA_FAST_SPEED 8.2f
#define CAMERA_SENSITIVITY 0.1f

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    float yaw;
    float pitch;
    float zoom;

public:
    Camera();

    glm::mat4 get_view_matrix();
    float get_zoom();
    glm::vec3 get_position();
    void process_keyboard(CameraMovement movement, bool fast, float delta_time);
    void process_mouse_input(float x, float y);
    void process_mouse_zoom(float offset);

private:
    void update_vectors();
};


#endif //UNIRENDER_CAMERA_H
