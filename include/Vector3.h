#ifndef _FIREFLY_VECTOR3_H
#define _FIREFLY_VECTOR3_H

#include <cmath> 

namespace Firefly
{
    struct Vector3
    {
        float x, y, z;
        
        Vector3();
        Vector3(float X, float Y, float Z);

        Vector3 operator - () const;
        float Length() const ;

        float LengthSquared() const;

        static float Dot(const Vector3& a, const Vector3& b);

        static Vector3 Cross(const Vector3& a, const Vector3& b);

        static Vector3 Normalize(Vector3& vec);

    };

        inline Vector3 Vector3::operator -() const {
            return Vector3(-x, -y, -z);
        }

        inline Vector3 operator + (const Vector3& a, const Vector3& b){
            return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
        }

        inline Vector3 operator + (float a, const Vector3& b){
            return Vector3(b.x + a, b.y + a, b.z + a);
        }

        inline Vector3 operator - (const Vector3& a, const Vector3& b){
            return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
        }

        inline Vector3 operator / (const Vector3& a, const Vector3& b){
            return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
        }
        
        inline Vector3 operator * (const Vector3& a, const Vector3& b){
            return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
        }

        inline Vector3 operator / (float a, const Vector3& b){
            return Vector3(b.x / a, b.y / a, b.z / a);
        }

        inline Vector3 operator / (const Vector3& a, float b){
            return Vector3(a.x / b, a.y / b, a.z / b);
        }

        inline Vector3 operator * (float a, const Vector3& b){
            return Vector3(b.x * a, b.y * a, b.z * a);
        }

        inline Vector3 operator * (const Vector3& a, float b){
            return Vector3(a.x * b, a.y * b, a.z * b);
        }


        inline Vector3::Vector3(){
            x = 0;
            y = 0;
            z = 0;
        }

        inline Vector3::Vector3(float X, float Y, float Z){
            x = X;
            y = Y;
            z = Z;
        }

        inline float Vector3::Length() const {
            return sqrtf(LengthSquared());
        }

        inline float Vector3::LengthSquared() const{
            return ((x * x) + (y * y) + (z * z));
        }

        inline float Vector3::Dot(const Vector3& a, const Vector3& b){
            return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
        }

        inline Vector3 Vector3::Cross(const Vector3& a, const Vector3& b){
            return Vector3(
                    (a.y * b.z) - (a.z * b.x),
                    (a.z * b.x) - (a.x * b.z),
                    (a.x * b.y) - (a.y * b.x)
                    );
        }

        inline Vector3 Vector3::Normalize(Vector3& vec){
            return vec / vec.Length();
        }

}

#endif
