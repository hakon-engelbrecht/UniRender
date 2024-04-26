#include "camera.h"
#include "glm/ext/matrix_transform.hpp"

Camera::Camera() {
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->right = glm::vec3(1.0f, 0.0f, 0.0f);
    this->world_up = glm::vec3(0.0f, 1.0f, 0.0f);

    this->yaw = -90.0f;
    this->pitch = 0.0f;
    this->zoom = 45.0f;

    this->update_vectors();
}

glm::mat4 Camera::get_view_matrix() {
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

float Camera::get_zoom() {
    return this->zoom;
}

glm::vec3 Camera::get_position() {
    return this->position;
}

void Camera::process_keyboard(CameraMovement movement, bool fast, float delta_time) {
    float velocity = (fast ? CAMERA_FAST_SPEED : CAMERA_SPEED) * delta_time;

    switch (movement) {
        case FORWARD:
            this->position += this->front * velocity;
            break;
        case BACKWARD:
            this->position -= this->front * velocity;
            break;
        case LEFT:
            this->position -= this->right * velocity;
            break;
        case RIGHT:
            this->position += this->right * velocity;
            break;
        case UP:
            this->position += this->up * velocity;
            break;
        case DOWN:
            this->position -= this->up * velocity;
            break;
    }
}

void Camera::process_mouse_input(float x, float y) {
    x *= CAMERA_SENSITIVITY;
    y *= CAMERA_SENSITIVITY;

    this->yaw += x;
    this->pitch += y;

    if (this->pitch > 89.0f) {
        this->pitch = 89.0f;
    }
    if (this->pitch < -89.0f) {
        this->pitch = -89.0f;
    }

    this->update_vectors();
}

void Camera::process_mouse_zoom(float offset) {
    if (this->zoom >= 1.0f && this->zoom <= 45.0f) {
        this->zoom -= offset;
    }
    if (this->zoom <= 1.0f) {
        this->zoom = 1.0f;
    }
    if (this->zoom >= 45.0f) {
        this->zoom = 45.0f;
    }
}

/**********************************************************************************************************************/
// private

void Camera::update_vectors() {
    glm::vec3 new_front;
    new_front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    new_front.y = sin(glm::radians(this->pitch));
    new_front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(new_front);

    this->right = glm::normalize(glm::cross(this->front, this->world_up));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}
