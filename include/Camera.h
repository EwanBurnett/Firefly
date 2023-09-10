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
            const Viewport& GetViewport() const;
 
            Vector3 PixelDeltaU(const uint32_t width) const;
            Vector3 PixelDeltaV(const uint32_t height) const; 
            Vector3 PixelOrigin(const uint32_t width, const uint32_t height) const;        

        private:
            Vector3 m_Position;

            Vector3 m_UpVector; 
            Vector3 m_RightVector;
            Vector3 m_ForwardsVector;
            
            Viewport m_Viewport;
            float m_FocalLength;
    };

    inline Camera::Camera(){

        m_Position = {0.0f, 0.0f, 0.0f};

        m_UpVector = {0.0f, 1.0f, 0.0f};
        m_RightVector = {1.0f, 0.0f, 0.0f};
        m_ForwardsVector = {0.0f, 0.0f, 1.0f}; //TODO: -Z Forwards?

        m_FocalLength = 1.0f;
    }

    inline Camera::Camera(const Vector3& origin, const Viewport& viewPort, const float focalLength, const Vector3& upVector){
        m_Position = origin;

        m_Viewport = viewPort;
        m_UpVector = upVector; //TODO: Find Right and Forwards vectors
        m_RightVector = {1.0f, 0.0f, 0.0f};
        m_ForwardsVector = {0.0f, 0.0f, 1.0f}; //TODO: -Z Forwards?

        m_FocalLength = focalLength;
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

    inline const Viewport& Camera::GetViewport() const{
        return m_Viewport;
    }

    inline Vector3 Camera::PixelDeltaU(const uint32_t width) const{
        return (m_Viewport.ViewportU() / (float)width);
    }

    inline Vector3 Camera::PixelDeltaV(const uint32_t height) const{
        return (m_Viewport.ViewportV() / (float)height);
    }

    inline Vector3 Camera::PixelOrigin(const uint32_t width, const uint32_t height) const{
        return m_Viewport.TopLeft(GetPosition(), GetFocalLength()) + (0.5f * (PixelDeltaU(width) + PixelDeltaV(height))); 
    }
}

#endif
