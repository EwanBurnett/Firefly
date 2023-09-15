#ifndef _FIREFLY_VECTOR3_H
#define _FIREFLY_VECTOR3_H

#include <cmath> 
#include "RNG.h"

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

        static Vector3 Random();

        static bool NearlyEqual(const Vector3& a, const Vector3& b);
        
        static Vector3 Reflect(const Vector3& vector, const Vector3& normal);

        static Vector3 Refract(const Vector3& vector, const Vector3& normal, float etai_over_etat);

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

        inline Vector3 Vector3::Random(){
            static RNG rng; 
            return {
                rng.RandomFloat(),
                rng.RandomFloat(),
                rng.RandomFloat()
            };
        }

        inline bool Vector3::NearlyEqual(const Vector3& a, const Vector3& b)
        {
            float s = 1e-8;
            return ((a.x < (b.x + s)) && (a.y < (b.y + s)) && (a.z < (b.z + s)));
        }

        inline Vector3 Vector3::Reflect(const Vector3& vector, const Vector3& normal)
        {
            return vector - (2.0f * Vector3::Dot(vector, normal) * normal); 
        }

        inline Vector3 Vector3::Refract(const Vector3& vector, const Vector3& normal, float etai_over_etat)
        {
            float cosTheta = fminf(Vector3::Dot(-vector, normal), 1.0f);
            Vector3 perpendicularRefraction = etai_over_etat * (vector + cosTheta * normal);

            Vector3 parallelRefraction = -sqrtf(fabsf(1.0f - perpendicularRefraction.LengthSquared())) * normal; 

            return perpendicularRefraction + parallelRefraction; 
        }
}

#endif
