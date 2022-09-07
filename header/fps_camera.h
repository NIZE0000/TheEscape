// // -*- c++ -*-
// #ifndef CAMERA_H
// #define CAMERA_H

// #include <vector>

// // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
// enum Camera_Movement
// {
//     FORWARD,
//     BACKWARD,
//     LEFT,
//     RIGHT
// };

// // Default camera values
// const float YAW = -90.0f;
// const float PITCH = 0.0f;
// const float SPEED = 4.5f;
// const float SENSITIVTY = 0.05f;

// // An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
// class Camera
// {
// public:
//     // Camera Attributes
//     float pos[3];
//     glm::vec3 Front;
//     glm::vec3 Up;
//     glm::vec3 Right;
//     glm::vec3 WorldUp;
//     // Eular Angles
//     float Yaw;
//     float Pitch;
//     // Camera options
//     float MovementSpeed;
//     float MouseSensitivity;

//     // Constructor with vectors
//     Camera() : Front({0.0f, 0.0f, -1.0f}), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY)
//     {
//         this->Position[0] = 0;
//         Position[1];
//         WorldUp = Up;
//         Yaw = YAW;
//         Pitch = PITCH;
//         updateCameraVectors();
//     }

//     void ProcessKeyboard(int key)
//     {
//         if (key == GLFW_KEY_W)
//         {
//         }
//     }


//     void move(Camera_Movement direction, float deltaTime)
//     {
//         float velocity = MovementSpeed * deltaTime;
//         if (direction == FORWARD)
//             Position += Front * velocity;
//         if (direction == BACKWARD)
//             Position -= Front * velocity;
//         if (direction == LEFT)
//             Position -= Right * velocity;
//         if (direction == RIGHT)
//             Position += Right * velocity;
//         // Make sure the user stays at the ground level
//         // this one-liner keeps the user at the ground level (xz plane)
//         Position.y = 0.0f;
//     }


//     // Processes input received from a mouse input system.
//     // Expects the offset value in both the x and y direction.
//     // void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
//     // {
//     //     xoffset *= MouseSensitivity;
//     //     yoffset *= MouseSensitivity;

//     //     Yaw += xoffset;
//     //     Pitch += yoffset;

//     //     // Make sure that when pitch is out of bounds, screen doesn't get flipped
//     //     if (constrainPitch)
//     //     {
//     //         if (Pitch > 89.0f)
//     //             Pitch = 89.0f;
//     //         if (Pitch < -89.0f)
//     //             Pitch = -89.0f;
//     //     }

//     //     // Update Front, Right and Up Vectors using the updated Eular angles
//     //     updateCamera();
//     // }

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
// };
// #endif
