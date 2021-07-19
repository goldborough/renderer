#ifndef CAMERA_H
#define CAMERA_H

//#include <glad/glad.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "EngineUtilities/Math.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    LMVector3 Position;
    LMVector3 Front;
    LMVector3 Up;
    LMVector3 Right;
    LMVector3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(
        LMVector3 position = LMVector3(0.0f, 0.0f, 0.0f),
        LMVector3 up = LMVector3(0.0f, 1.0f, 0.0f),
        float yaw = YAW, float pitch = PITCH) : Front(LMVector3(0.0f, 0.0f, -1.0f)),
            MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(LMVector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = LMVector3(posX, posY, posZ);
        WorldUp = LMVector3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix


    
    LMMatrix4 GetViewMatrix()
    {
        return MyMath::lookAtRH(Position, Position + Front, Up);


        /*
        glm::mat4 m = glm::lookAt(
            glm::vec3(Position.x, Position.y, Position.z), 
            glm::vec3(Position.x + Front.x, Position.y + Front.y, Position.z + Front.z),
            glm::vec3(Up.x, Up.y, Up.z)
        
        );

        return LMMatrix4(
            m[0][0],
            m[0][1],
            m[0][2],
            m[0][3],

            m[1][0],
            m[1][1],
            m[1][2],
            m[1][3],

            m[2][0],
            m[2][1],
            m[2][2],
            m[2][3],

            m[3][0],
            m[3][1],
            m[3][2],
            m[3][3] );
        */

    }


    
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:

     /*void updateCameraVectors()
    {
    
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        glm::vec3 F = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Front = LMVector3(F.x, F.y, F.z);


        glm::vec3 R = glm::normalize(glm::cross(F, glm::vec3(WorldUp.x, WorldUp.y, WorldUp.z) ));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.

        Right = LMVector3(R.x, R.y, R.z);

        glm::vec3 U = glm::normalize(glm::cross(R, F));
        
        Up = LMVector3(U.x, U.y, U.z);


    }
        */

    
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        LMVector3 front;
        //front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        //front.y = sin(glm::radians(Pitch));
        //front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.x = cos(DEG2RAD * Yaw) * cos(DEG2RAD*Pitch);
        front.y = sin(DEG2RAD *Pitch);
        front.z = sin(DEG2RAD*Yaw) * cos(DEG2RAD*Pitch);
        Front = front;
        Front.Normalize();
        // also re-calculate the Right and Up vector
        Right = MyMath::cross(Front, WorldUp);
        Right.Normalize();
        
        //Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        //Up = glm::normalize(glm::cross(Right, Front));

        Up = MyMath::cross(Right, Front);
        Up.Normalize();


    }



};

#endif

