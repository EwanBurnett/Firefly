#ifndef _FIREFLY_CAMERA_H
#define _FIREFLY_CAMERA_H

#include "../include/MathHelper.h"
#include "../include/Vector3.h"
#include "../include/Viewport.h"

namespace Firefly{
    class Camera{
        public:
            Camera();
            Camera(const Vector3& origin, const Viewport& viewPort, const float focalLength = 1.0f, const float defocusAngle = 0.0f, const float FoV = 900.0f, const Vector3& orientation = {0.0f, 0.0f, 1.0f});

            Vector3 GetPosition() const;
            void SetPosition(const Vector3& position);

            float GetFocalDistance() const;
            float GetDefocusAngle() const;
            Vector3 GetDefocusDiskU() const;
            Vector3 GetDefocusDiskV() const;

            Vector3 TopLeftPixel() const; 

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
            float m_FoV; //Vertical Field of View

            float m_FocalDistance; //Distance from camera in direction of its forwards vector to the plane of perfect focus
            float m_DefocusAngle;  //Variation angle of Rays through each pixel

            Vector3 m_DefocusDisk_U; //Defocus disk horizontal radius
            Vector3 m_DefocusDisk_V; //Defocus disk Vertical radius
    };

    inline Camera::Camera(){

        m_Position = {0.0f, 0.0f, 0.0f};

        m_UpVector = {0.0f, 1.0f, 0.0f};
        m_RightVector = {1.0f, 0.0f, 0.0f};
        m_ForwardsVector = {0.0f, 0.0f, -1.0f};

        m_FoV = 90.0f; 

        m_FocalDistance = 10.0f;
        m_DefocusAngle = 0.0f;
    }

    inline Camera::Camera(const Vector3& origin, const Viewport& viewPort, const float focalLength, const float defocusAngle, const float FoV, const Vector3& orientation){
        m_Position = origin;
        m_Viewport = viewPort;
        m_FocalDistance = focalLength;
        m_DefocusAngle = defocusAngle;
        m_FoV = FoV;

        //Compute Orientation
        {
            Vector3 o = orientation;
            Vector3 rotNorm = Vector3::Normalize(o);
            Vector3 forwards = origin - (origin + rotNorm); 
            m_ForwardsVector = Vector3::Normalize(forwards);
            m_RightVector = Vector3::Cross({0.0f, 1.0f, 0.0f}, m_ForwardsVector);
            m_UpVector = Vector3::Cross(m_ForwardsVector, m_RightVector);
        }
        //Compute Viewport Vertical Height
        {
            float theta = DegToRad(m_FoV);
            float h = tanf(theta / 2.0f);

            m_Viewport.m_ViewportHeight = 2 * h * m_FocalDistance; 
        }

        //Compute Defocus Disk
        float defocusRadius = m_FocalDistance * tanf(DegToRad(m_DefocusAngle / 2.0f));
        m_DefocusDisk_U = m_RightVector * defocusRadius; 
        m_DefocusDisk_V = m_UpVector * defocusRadius; 

    }


    inline Vector3 Camera::GetPosition() const{
        return m_Position;
    }

    inline void Camera::SetPosition(const Vector3& position){
        m_Position = position;
    }

    inline const Viewport& Camera::GetViewport() const{
        return m_Viewport;
    }

    inline Vector3 Camera::TopLeftPixel() const{
        return m_Position - (m_FocalDistance * m_ForwardsVector) - m_Viewport.ViewportU() / 2.0f - m_Viewport.ViewportV() / 2.0f; 
    }

    inline Vector3 Camera::PixelDeltaU(const uint32_t width) const{
        return (m_Viewport.ViewportU() / (float)width);
    }

    inline Vector3 Camera::PixelDeltaV(const uint32_t height) const{
        return (m_Viewport.ViewportV() / (float)height);
    }

    inline Vector3 Camera::PixelOrigin(const uint32_t width, const uint32_t height) const{
        return TopLeftPixel() + (0.5f * (PixelDeltaU(width) + PixelDeltaV(height))); 
    }

    inline float Camera::GetFocalDistance() const{
        return m_FocalDistance;
    }

    inline float Camera::GetDefocusAngle() const{
        return m_DefocusAngle;
    }
            
    inline Vector3 Camera::GetDefocusDiskU() const{
        return m_DefocusDisk_U;
    }
            
    inline Vector3 Camera::GetDefocusDiskV() const{
        return m_DefocusDisk_V;
    }
}

#endif
