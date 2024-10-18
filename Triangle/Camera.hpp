#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.hpp"

class Camera {
public:
    // main vectors of the camera
    glm::vec3 position;
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 camMatrix = glm::mat4(1.0f);

    // used to stop the camera from jumping around when clicking
    bool firstClick = true;

    // width and height of the window
    int width;
    int height;

    // parameters for nice movement speeds
    float speed = 0.005f;
    float sensitivity = 80.0f;

    Camera(int width, int height, glm::vec3 position);

    // update the camera matrix given information about the viewing frustrum
    void updateMatrix(float FOVrad, float nearPlane, float farPlane);
    // exports the camera matrix to the vertex shader
    void exportMatrix(Shader& shader, const char* uniform);
    // takes in movement inputs
    void Inputs(GLFWwindow* window);
};

#endif // !CAMERA_CLASS_H
