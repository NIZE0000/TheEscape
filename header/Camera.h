#ifndef CAMERA_H
#define CAMERA_H

#include <pch.h>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float SPEED = 80;
const float MouseSensitivity = 0.1;
const float DEG_TO_RED = 0.017453293;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    Camera() : MovementSpeed(SPEED)
    {
    }

    void setPosition(float x, float y, float z)
    {
        this->pos[0] = x;
        this->pos[1] = y;
        this->pos[2] = z;
    }

    void getPosition(float *x, float *y, float *z)
    {
        *x = this->pos[0];
        *y = this->pos[1];
        *z = this->pos[2];
    }

    void setDegree(float x, float y, float z)
    {
        this->rot[0] = x;
        this->rot[1] = y;
        this->rot[2] = z;
    }

    void ProcessKeyboard(GLFWwindow *wnd)
    {

        if (this->collision) // Bullshit check
        {
            this->pos[0] -= (this->pos[0] - this->lastPos[0]) * 0.51;
            this->pos[2] -= (this->pos[2] - this->lastPos[2]) * 0.51;

            // this->collision = false;
            return;
        }
        else
        {
            this->lastPos[0] = this->pos[0];
            this->lastPos[2] = this->pos[2];
        }

        float delta = this->deltatime;

        if (glfwGetKey(wnd, GLFW_KEY_W) == GLFW_PRESS)
        {
            move(FORWARD, delta);
        }
        if (glfwGetKey(wnd, GLFW_KEY_S) == GLFW_PRESS)
        {
            move(BACKWARD, delta);
        }
        if (glfwGetKey(wnd, GLFW_KEY_D) == GLFW_PRESS)
        {
            move(RIGHT, delta);
        }
        if (glfwGetKey(wnd, GLFW_KEY_A) == GLFW_PRESS)
        {
            move(LEFT, delta);
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
            this->rot[0] -= 2;
        }
        if (glfwGetKey(wnd, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            this->rot[0] += 2;
        }
    }

    void move(Camera_Movement direction, float deltaTime)
    {

        float velocity = MovementSpeed * deltaTime;

        if (direction == FORWARD)
        {
            this->pos[0] += this->dir[0] * velocity;
            this->pos[2] += this->dir[2] * velocity;
        }

        if (direction == BACKWARD)
        {
            this->pos[0] -= this->dir[0] * velocity;
            this->pos[2] -= this->dir[2] * velocity;
        }
        if (direction == LEFT)
        {
            this->pos[0] += this->dir[2] * velocity;
            this->pos[2] -= this->dir[0] * velocity;
        }
        if (direction == RIGHT)
        {
            this->pos[0] -= this->dir[2] * velocity;
            this->pos[2] += this->dir[0] * velocity;
        }
    }

    void render()
    {
        if (this->rot[0] > 89)
        {
            this->rot[0] = 89;
        }
        if (this->rot[0] < -89)
        {
            this->rot[0] = -89;
        }

        // calculate direction
        this->dir[0] = -cos((rot[1] - 90) * DEG_TO_RED); // X
        this->dir[2] = -sin((rot[1] - 90) * DEG_TO_RED); // Z

        glRotatef(this->rot[0], 1.0, 0.0, 0.0);
        glRotatef(this->rot[1], 0.0, 1.0, 0.0);
        glRotatef(this->rot[2], 0.0, 0.0, 1.0);
        glTranslatef(this->pos[0], -this->pos[1], this->pos[2]);
    }

    // Processes input received from a mouse input.
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
    }

    void Debug()
    {
        std::cout << " Player camera: " << std::endl;

        // Debug dir pos rot
        std::cout << " dir " << this->dir[0] << ", " << this->dir[1] << ", " << this->dir[2] << std::endl;
        std::cout << " pos " << this->pos[0] << ", " << this->pos[1] << ", " << this->pos[2] << std::endl;
        std::cout << " rot " << this->rot[0] << ", " << this->rot[1] << ", " << this->rot[2] << std::endl;
    }

    void updateCollision(bool check)
    {
        this->collision = check; // Assign check value
    }

    void updateDeltatime(float Deltatime)
    {
        this->deltatime = Deltatime;
    }

private:
    // Camera Attributes
    float pos[3];
    float dir[3];
    float rot[3];

    bool collision = false;
    float lastPos[3];
    float deltatime = 0.03;

    // Camera options
    float MovementSpeed;
};
#endif
