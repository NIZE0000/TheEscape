// -*- c++ -*-
#ifndef CAMERA_H
#define CAMERA_H

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
const float SPEED = 4.5f;
const float ZOOM = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // Camera Attributes
    float pos[3] = {
        0.0, 0.0, 0.0};
    float dir[3] = {
        0.0, 0.0, 0.0};
    float rot[3] = {
        0.0, 0.0, 0.0};

    // float Front[3] = {0.0f, 0.0f, -1.0f};
    // float WorldUp[3] = {0.0, 1.0, 0.0};
    // float Right[3] = {1.0, 0.0, 0.0};

    // Eular Angles
    // float Yaw;
    // float Pitch;

    // Camera options
    float MovementSpeed;

    // Constructor with vectors
    Camera() : MovementSpeed(SPEED)
    {

        // Yaw = YAW;
        // Pitch = PITCH;
        updateCamera();
    }

    void ProcessKeyboard(int key)
    {

        if (key == GLFW_KEY_W)
        {
            move(FORWARD, 1);
        }
        if (key == GLFW_KEY_S)
        {
            move(BACKWARD, 1);
        }
        if (key == GLFW_KEY_D)
        {
            move(RIGHT, 1);
        }
        if (key == GLFW_KEY_A)
        {
            move(LEFT, 1);
        }
        if (key == GLFW_KEY_RIGHT)
        {
            this->rot[1] += 2;
        }
        if (key == GLFW_KEY_LEFT)
        {
            this->rot[1] -= 2;
        }
        if (key == GLFW_KEY_UP)
        {
            this->rot[0] += 5;
        }
        if (key == GLFW_KEY_DOWN)
        {
            this->rot[0] -= 5;
        }
    }

    void move(Camera_Movement direction, float deltaTime)
    {
        if (direction == FORWARD or direction == BACKWARD)
        {
            this->dir[0] = sin((rot[1] * 3.145 / 180));    // X
            this->dir[2] = -cos(((rot[1]) * 3.145 / 180)); // Z
        }
        if (direction == LEFT or direction == RIGHT)
        {
            this->dir[0] = cos((rot[1] * 3.145 / 180));    // X
            this->dir[2] = -sin(((rot[1]) * 3.145 / 180)); // Z
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

    void updateCamera()
    {
        render();

        // this->dir[1] = sin((rot[1] * 3.145 / 360));
        std::cout << (90 * 3.145 / 180) << std::endl;
        std::cout << " dir " << this->dir[0] << " " << this->dir[1] << " " << this->dir[2] << std::endl;
        std::cout << " pos ," << this->pos[0] << " " << this->pos[1] << ", " << this->pos[2] << std::endl;
        std::cout << " rot " << this->rot[0] << " " << this->rot[1] << " " << this->rot[2] << std::endl;

        glPushMatrix();
        // glRotatef(this->rot[0], 1.0, 0.0, 1.0);
        glRotatef(this->rot[1], 0.0, 1.0, 0.0);
        // glRotatef(this->rot[2], 0.0, 0.0, 1.0);
        
        glTranslatef(0.0, -50.0, 0.0);

        glTranslatef(this->pos[0], this->pos[1], this->pos[2]);
        glPopMatrix;
    }

    void render() // angle lines
    {

        glColor4f(1.0, 0.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(10.0, 0.0, 0.0);
        glEnd();

        glColor4f(0.0, 1.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 10.0, 0.0);
        glEnd();

        glColor4f(0.0, 0.0, 1.0, 1.0);
        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 10.0);
        glEnd();
    }

    // Processes input received from a mouse input system.
    // Expects the offset value in both the x and y direction.
    // void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    // {
    //     xoffset *= MouseSensitivity;
    //     yoffset *= MouseSensitivity;

    //     Yaw += xoffset;
    //     Pitch += yoffset;

    //     // Make sure that when pitch is out of bounds, screen doesn't get flipped
    //     if (constrainPitch)
    //     {
    //         if (Pitch > 89.0f)
    //             Pitch = 89.0f;
    //         if (Pitch < -89.0f)
    //             Pitch = -89.0f;
    //     }

    //     // Update Front, Right and Up Vectors using the updated Eular angles
    //     updateCamera();
    // }

    // private:
    //     // Calculates the front vector from the Camera's (updated) Eular Angles
    //     void updateCamera()
    //     {
    //         // Calculate the new Front vector
    //         glm::vec3 front;
    //         front.x = cos(Yaw) * cos(Pitch);
    //         front.y = sin(Pitch);
    //         front.z = sin(Yaw) * cos(Pitch);
    //         Front = glm::normalize(front);
    //         // Also re-calculate the Right and Up vector
    //         // Normalize the vectors, because their length gets closer to 0
    //         // the more you look up or down which results in slower movement.
    //         Right = glm::normalize(glm::cross(Front, WorldUp));
    //         Up = glm::normalize(glm::cross(Right, Front));
    //     }
};
#endif
