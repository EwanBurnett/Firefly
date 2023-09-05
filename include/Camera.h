#ifndef _FIREFLY_CAMERA_H
#define _FIREFLY_CAMERA_H

#include "../include/Vector3.h"
#include "../include/Viewport.h"

namespace Firefly{
    class Camera{
        public:
            Camera();
            Camera(const Vector3& origin, const Viewport& viewPort, const float focalLength = 1.0f, const Vector3& upVector = {0.0f, 1.0f, 0.0f});

            Vector3 GetPosition() const;
            void SetPosition(const Vector3& position);

            float GetFocalLength() const;
        private:
            Vector3 m_Position;

            Vector3 m_UpVector; 
            Vector3 m_RightVector;
            Vector3 m_ForwardsVector;
            
            Viewport m_Viewport;
            float m_FocalLength;
    };

    inline Camera::Camera(){

        m_UpVector = {0.0f, 1.0f, 0.0f};
        m_RightVector = {1.0f, 0.0f, 0.0f};
        m_ForwardsVector = {0.0f, 0.0f, 1.0f}; //TODO: -Z Forwards?
    }

    inline Camera::Camera(const Vector3& origin, const Viewport& viewPort, const float focalLength, const Vector3& upVector){
        m_Position = origin;
        m_Viewport = viewPort;
        m_UpVector = upVector; //TODO: Find Right and Forwards vectors

    }


    inline Vector3 Camera::GetPosition() const{
        return m_Position;
    }

    inline void Camera::SetPosition(const Vector3& position){
        m_Position = position;
    }

    inline float Camera::GetFocalLength() const{
        return m_FocalLength;
    }
}

#endif
