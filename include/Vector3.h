#ifndef _FIREFLY_VECTOR3_H
#define _FIREFLY_VECTOR3_H

#include <cmath> 

namespace Firefly
{
    struct Vector3
    {
        Vector3(){
            x = 0;
            y = 0;
            z = 0;
        }
        Vector3(float X, float Y, float Z){
            x = X;
            y = Y;
            z = Z;
        }

        float x, y, z;

        Vector3& operator +(const Vector3& rhs){
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        Vector3& operator -(const Vector3& rhs){
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        Vector3& operator /(const Vector3& rhs){
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            return *this;
        }

        Vector3& operator /(const float rhs){
            x /= rhs;
            y /= rhs;
            z /= rhs;
        }

        Vector3& operator *(const Vector3& rhs){
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            return *this;
        }

        Vector3& operator *(const float rhs){
            x *= rhs;
            y *= rhs;
            z *= rhs;
        }


        float Length() const {
            return sqrtf(LengthSquared());
        }

        float LengthSquared() const{
            return ((x * x) + (y * y) + (z * z));
        }

        static float Dot(const Vector3& a, const Vector3& b){
            return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
        }

        static Vector3 Cross(const Vector3& a, const Vector3& b){
            return {
                    (a.y * b.z) - (a.z * b.x),
                    (a.z * b.x) - (a.x * b.z),
                    (a.x * b.y) - (a.y * b.x)
            };
        }

        static Vector3 Normalize(Vector3& vec){
            return vec / vec.Length();
        }
    };
}

#endif
