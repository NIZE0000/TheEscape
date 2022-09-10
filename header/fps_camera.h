// -*- c++ -*-
#ifndef CAMERA_H
#define CAMERA_H

#include <pch.h>
#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float MouseSensitivity = 0.1;
const float DEG_TO_RED = 0.017453293;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Camera Attributes
    float pos[3] = {
        -230.0, -50.0, 220.0};
    float dir[3] = {
        0.0, 0.0, 0.0};
    float rot[3] = {
        0.0, -90.0, 0.0};

    // Camera options
    float MovementSpeed;

    Camera() : MovementSpeed(SPEED)
    {

        updateCamera();
    }

    void ProcessKeyboard(GLFWwindow *wnd)
    {

        if (glfwGetKey(wnd, GLFW_KEY_W) == GLFW_PRESS)
        {
            move(FORWARD, 1);
        }
        if (glfwGetKey(wnd, GLFW_KEY_S) == GLFW_PRESS)
        {
            move(BACKWARD, 1);
        }
        if (glfwGetKey(wnd, GLFW_KEY_D) == GLFW_PRESS)
        {
            move(RIGHT, 1);
        }
        if (glfwGetKey(wnd, GLFW_KEY_A) == GLFW_PRESS)
        {
            move(LEFT, 1);
        }
        if (glfwGetKey(wnd, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            this->rot[1] += 2;
        }
        if (glfwGetKey(wnd, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            this->rot[1] -= 2;
        }
        if (glfwGetKey(wnd, GLFW_KEY_UP) == GLFW_PRESS)
        {
            this->rot[0] -= 5;
        }
        if (glfwGetKey(wnd, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            this->rot[0] += 5;
        }
    }

    void move(Camera_Movement direction, float deltaTime)
    {
        if (direction == FORWARD || direction == BACKWARD)
        {
            this->dir[0] = sin(rot[1] * DEG_TO_RED);  // X
            this->dir[2] = -cos(rot[1] * DEG_TO_RED); // Z
        }
        if (direction == LEFT || direction == RIGHT)
        {
            this->dir[0] = cos(rot[1] * DEG_TO_RED);  // X
            this->dir[2] = -sin(rot[1] * DEG_TO_RED); // Z
        }

        float velocity = MovementSpeed * deltaTime;

        if (direction == FORWARD)
        {
            this->pos[0] -= this->dir[0] * velocity;
            this->pos[2] -= this->dir[2] * velocity;
        }

        if (direction == BACKWARD)
        {
            this->pos[0] += this->dir[0] * velocity;
            this->pos[2] += this->dir[2] * velocity;
        }
        if (direction == LEFT)
        {
            this->pos[0] += this->dir[0] * velocity;
            this->pos[2] -= this->dir[2] * velocity;
        }
        if (direction == RIGHT)
        {
            this->pos[0] += -this->dir[0] * velocity;
            this->pos[2] += this->dir[2] * velocity;
        }
    }

    void render() // angle lines X Y Z
    {

        // glColor4f(1.0, 0.0, 0.0, 1.0);
        // glBegin(GL_LINES);
        // glVertex3f(0.0, 0.0, 0.0);
        // glVertex3f(10.0, 0.0, 0.0);
        // glEnd();

        // glColor4f(0.0, 1.0, 0.0, 1.0);
        // glBegin(GL_LINES);
        // glVertex3f(0.0, 0.0, 0.0);
        // glVertex3f(0.0, 10.0, 0.0);
        // glEnd();

        // glColor4f(0.0, 0.0, 1.0, 1.0);
        // glBegin(GL_LINES);
        // glVertex3f(0.0, 0.0, 0.0);
        // glVertex3f(0.0, 0.0, 10.0);
        // glEnd();

        updateCamera();
    }

    // Processes input received from a mouse input system.
    // Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        this->rot[1] += xoffset;
        this->rot[0] += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (this->rot[0] > 89.0f)
                this->rot[0] = 89.0f;
            if (this->rot[0] < -89.0f)
                this->rot[0] = -89.0f;
        }

        updateCamera();
    }

private:
    void updateCamera()
    {

        if (this->rot[0] > 89)
        {
            this->rot[0] = 89;
        }
        if (this->rot[0] < -89)
        {
            this->rot[0] = -89;
        }

        // debug
        // std::cout << " dir " << this->dir[0] << " " << this->dir[1] << " " << this->dir[2] << std::endl;
        // std::cout << " pos ," << this->pos[0] << " " << this->pos[1] << ", " << this->pos[2] << std::endl;
        // std::cout << " rot " << this->rot[0] << " " << this->rot[1] << " " << this->rot[2] << std::endl;

        glPushMatrix();
        glRotatef(this->rot[0], 1.0, 0.0, 0.0);
        glRotatef(this->rot[1], 0.0, 1.0, 0.0);
        glTranslatef(this->pos[0], this->pos[1], this->pos[2]);
        glPopMatrix;
    }
};
#endif
