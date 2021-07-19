#if!defined(MYMATH_H)
#define MYMATH_H

#include <cmath>

#include "Math/Math_Constants.h"

#include "Math/LMVector2.h"
#include "Math/LMVector3.h"
#include "Math/LMVector4.h"

#include "Math/LMMatrix2.h"
#include "Math/LMMatrix3.h"
#include "Math/LMMatrix4.h"

namespace MyMath
{
    inline LMVector3 cross(LMVector3 const& x, LMVector3 const& y)
    {
        return LMVector3(
            x.y * y.z - y.y * x.z,
            x.z * y.x - y.z * x.x,
            x.x * y.y - y.x * x.y);
    }

    inline float dot(LMVector3 const& x, LMVector3 const& y)
    {
        LMVector3 tmp(x * y);
        return tmp.x + tmp.y + tmp.z;
    }


    inline LMVector3 inversesqrt(LMVector3 const& x)
    {
        float sx = 0.0f, sy = 0.0f, sz = 0.0f;

        if (x.x != 0.0f) { sx = x.x / x.x; sx = 1 / sx; }
        if (x.y != 0.0f) { sy = x.y / x.y; sy = 1 / sy; }
        if (x.z != 0.0f) { sz = x.z / x.z; sz = 1 / sz; }

        return LMVector3(sx, sy, sz);
    }

   /* inline LMVector3 normalize(LMVector3 const& x)
    {
        return LMVector3(inversesqrt(LMVector3::dot(x, x)) * x);
    }*/

    inline LMVector3 MyNormalize(LMVector3 const& x)
    {
        LMVector3 v = x;

        float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

        if (length != 0.0f)
        {
            return LMVector3(v.x /= length, v.y /= length, v.z /= length);
        }

        return LMVector3(0.0f);

    }

    inline LMMatrix4 lookAtRH
    (
        LMVector3 const& eye,
        LMVector3 const& center,
        LMVector3 const& up
    )
    {
        LMVector3 const f(MyNormalize(center - eye));
        LMVector3 const s(MyNormalize(cross(f, up)));
        LMVector3 const u(cross(s, f));

        LMMatrix4 Result(1.0f);
        Result.m[0+0*4] = s.x;
        Result.m[0+1*4] = s.y;
        Result.m[0+2*4] = s.z;
        Result.m[1+0*4] = u.x;
        Result.m[1+1*4] = u.y;
        Result.m[1+2*4] = u.z;
        Result.m[2+0*4] = -f.x;
        Result.m[2+1*4] = -f.y;
        Result.m[2+2*4] = -f.z;
        Result.m[0+3*4] = -dot(s, eye);
        Result.m[1+3*4] = -dot(u, eye);
        Result.m[2+3*4] = dot(f, eye);

        return Result;
    }

    inline LMMatrix4 lookAtRH2
    (
        LMVector3 const& eye,
        LMVector3 const& center,
        LMVector3 const& up
    )
    {
        LMVector3 const f(MyNormalize(center - eye));
        LMVector3 const s(MyNormalize(cross(f, up)));
        LMVector3 const u(cross(s, f));

        LMMatrix4 Result(1.0f);
        Result.m[0 + 0 * 4] = s.x;
        Result.m[0 + 1 * 4] = s.y;
        Result.m[0 + 2 * 4] = s.z;
        Result.m[1 + 0 * 4] = u.x;
        Result.m[1 + 1 * 4] = u.y;
        Result.m[1 + 2 * 4] = u.z;
        Result.m[2 + 0 * 4] = -f.x;
        Result.m[2 + 1 * 4] = -f.y;
        Result.m[2 + 2 * 4] = -f.z;
        Result.m[0 + 3 * 4] = -dot(s, eye);
        Result.m[1 + 3 * 4] = -dot(u, eye);
        Result.m[2 + 3 * 4] = dot(f, eye);

        return Result;
    }

    inline void BuildPerspectiveFovLHMatrix(float* matrix, float fieldOfView, float screenAspect, float screenNear, float screenDepth)
    {
        matrix[0] = 1.0f / (screenAspect * tan(fieldOfView * 0.5f));
        matrix[1] = 0.0f;
        matrix[2] = 0.0f;
        matrix[3] = 0.0f;

        matrix[4] = 0.0f;
        matrix[5] = 1.0f / tan(fieldOfView * 0.5f);
        matrix[6] = 0.0f;
        matrix[7] = 0.0f;

        matrix[8] = 0.0f;
        matrix[9] = 0.0f;
        matrix[10] = screenDepth / (screenDepth - screenNear);
        matrix[11] = 1.0f;

        matrix[12] = 0.0f;
        matrix[13] = 0.0f;
        matrix[14] = (-screenNear * screenDepth) / (screenDepth - screenNear);
        matrix[15] = 0.0f;

        return;
    }

    inline void BuildPerspectiveFovRHMatrix(float* matrix, float fieldOfView, float screenAspect, float screenNear, float screenDepth)
    {
        matrix[0] = 1.0f / (screenAspect * tan(fieldOfView * 0.5f));
        matrix[1] = 0.0f;
        matrix[2] = 0.0f;
        matrix[3] = 0.0f;

        matrix[4] = 0.0f;
        matrix[5] = 1.0f / tan(fieldOfView * 0.5f);
        matrix[6] = 0.0f;
        matrix[7] = 0.0f;

        matrix[8] = 0.0f;
        matrix[9] = 0.0f;
        matrix[10] = screenDepth / (screenNear - screenDepth);
        matrix[11] = -1.0f;

        matrix[12] = 0.0f;
        matrix[13] = 0.0f;
        matrix[14] = (-screenNear * screenDepth) / (screenDepth - screenNear);
        matrix[15] = 0.0f;

        return;
    }

    inline LMMatrix4 BuildPerspectiveFovRHMatrix(float fieldOfView, float screenAspect, float screenNear, float screenDepth)
    {
        float matrix[16];

        matrix[0] = 1.0f / (screenAspect * tan(fieldOfView * 0.5f));
        matrix[1] = 0.0f;
        matrix[2] = 0.0f;
        matrix[3] = 0.0f;

        matrix[4] = 0.0f;
        matrix[5] = 1.0f / tan(fieldOfView * 0.5f);
        matrix[6] = 0.0f;
        matrix[7] = 0.0f;

        matrix[8] = 0.0f;
        matrix[9] = 0.0f;
        matrix[10] = screenDepth / (screenNear - screenDepth);
        matrix[11] = -1.0f;

        matrix[12] = 0.0f;
        matrix[13] = 0.0f;
        matrix[14] = (-screenNear * screenDepth) / (screenDepth - screenNear);
        matrix[15] = 0.0f;

        return LMMatrix4(matrix);
    }

    inline float radians(float degrees)
    {
        return degrees * DEG2RAD;
    }

    inline float degrees(float radians)
    {
        return radians * RAD2DEG;
    }

    inline LMMatrix4 StripTranslation(const LMMatrix4& in) // ogl impl from lesson 20
    {
        LMMatrix4 result = in;

        result.m[3] = result.m[7] = result.m[11] = result.m[12] = result.m[13] = result.m[14] = result.m[15] = 0;

        return result;
    }

    inline LMMatrix4 BuildOrtho(
        const float& b, const float& t, const float& l, const float& r,
        const float& n, const float& f)
    {
        //https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/orthographic-projection-matrix

        /*
        void WINAPI glOrtho(
           GLdouble left,
           GLdouble right,
           GLdouble bottom,
           GLdouble top,
           GLdouble zNear,
           GLdouble zFar
        );
        */

        float matrix[16];

        // set OpenGL perspective projection matrix
        matrix[0+0*4] = 2 / (r - l);
        matrix[1+0*4] = 0;
        matrix[2+0*4] = 0;
        matrix[3+0*4] = 0;

        matrix[0+1*4] = 0;
        matrix[1+1*4] = 2 / (t - b);
        matrix[2+1*4] = 0;
        matrix[3+1*4] = 0;

        matrix[0+2*4] = 0;
        matrix[1+2*4] = 0;
        matrix[2+2*4] = -2 / (f - n);
        matrix[3+2*4] = 0;

        matrix[0+3*4] = -(r + l) / (r - l);
        matrix[1+3*4] = -(t + b) / (t - b);
        matrix[2+3*4] = -(f + n) / (f - n);
        matrix[3+3*4] = 1;


        return LMMatrix4(matrix);
    }

    inline LMMatrix4 MultiplyMat4(LMMatrix4& rhs, LMMatrix4& lhs)
    {
        LMMatrix4 result(0.0f);

        for (unsigned int i = 0; i < 16; i++)
        {
            result.m[i] = lhs.m[i] * rhs.m[i];
        }

        return result;
    }


    inline LMVector3 Vec4ToVec3(const LMVector4& v)
    {
        return LMVector3(v.x, v.y, v.z);
    }


    inline float Max(const float x, const float y)
    {
        return (x < y) ? y : x;
    }

    inline float Min(const float x, const float y)
    {
        return (y < x) ? y : x;
    }

    inline float Clamp(float x, float min, float max)
    {
        return Min(Max(x, min), max);
    }

    inline float lerp(float a, float b, float f)
    {
        return a + f * (b - a);
    }
}

#endif