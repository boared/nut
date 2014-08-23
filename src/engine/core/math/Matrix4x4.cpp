#include "FenMatrix4x4.h"

namespace fen
{

    const Matrix4x4 Matrix4x4::IDENTITY(1.f, 0.f, 0.f, 0.f,
                                        0.f, 1.f, 0.f, 0.f,
                                        0.f, 0.f, 1.f, 0.f,
                                        0.f, 0.f, 0.f, 1.f);

    const Matrix4x4 Matrix4x4::ZERO(0.f, 0.f, 0.f, 0.f,
                                    0.f, 0.f, 0.f, 0.f,
                                    0.f, 0.f, 0.f, 0.f,
                                    0.f, 0.f, 0.f, 0.f);

    const Matrix4x4 Matrix4x4::ZEROAFFINE(0.f, 0.f, 0.f, 0.f,
                                          0.f, 0.f, 0.f, 0.f,
                                          0.f, 0.f, 0.f, 0.f,
                                          0.f, 0.f, 0.f, 1.f);



    void Matrix4x4::setRotation(F32 rx, F32 ry, F32 rz)
    {
        F32 cosx = cos(rx);
        F32 cosy = cos(ry);
        F32 cosz = cos(rz);

        F32 sinx = sin(rx);
        F32 siny = sin(ry);
        F32 sinz = sin(rz);

        setIdentity();

        _m[ 0] = cosz * cosy;
        _m[ 1] = cosz * siny * sinx - sinz * cosx;
        _m[ 2] = cosz * siny * cosx + sinz * sinx;
        _m[ 3] = 0.0f;
        _m[ 4] = sinz * cosy;
        _m[ 5] = sinz * siny * sinx + cosz * cosx;
        _m[ 6] = sinz * siny * cosx - cosz * sinx;
        _m[ 7] = 0.0f;
        _m[ 8] = -siny;
        _m[ 9] = cosy * sinx;
        _m[10] = cosy * cosx;
        _m[11] = 0.0f;
    }



    void Matrix4x4::appendRotation(F32 rx, F32 ry, F32 rz)
    {
        F32 cosx = cos(rx);
        F32 cosy = cos(ry);
        F32 cosz = cos(rz);

        F32 sinx = sin(rx);
        F32 siny = sin(ry);
        F32 sinz = sin(rz);

        _m[ 0] = cosz * cosy * _m[0] + (cosz * siny * sinx - sinz * cosx) * _m[4] + (cosz * siny * cosx + sinz * sinx) * _m[ 8];
        _m[ 1] = cosz * cosy * _m[1] + (cosz * siny * sinx - sinz * cosx) * _m[5] + (cosz * siny * cosx + sinz * sinx) * _m[ 9];
        _m[ 2] = cosz * cosy * _m[2] + (cosz * siny * sinx - sinz * cosx) * _m[6] + (cosz * siny * cosx + sinz * sinx) * _m[10];
        _m[ 3] = cosz * cosy * _m[3] + (cosz * siny * sinx - sinz * cosx) * _m[7] + (cosz * siny * cosx + sinz * sinx) * _m[11];

        _m[ 4] = sinz * cosy * _m[0] + (sinz * siny * sinx + cosz * cosx) * _m[4] + (sinz * siny * cosx - cosz * sinx) * _m[ 8];
        _m[ 5] = sinz * cosy * _m[1] + (sinz * siny * sinx + cosz * cosx) * _m[5] + (sinz * siny * cosx - cosz * sinx) * _m[ 9];
        _m[ 6] = sinz * cosy * _m[2] + (sinz * siny * sinx + cosz * cosx) * _m[6] + (sinz * siny * cosx - cosz * sinx) * _m[10];
        _m[ 7] = sinz * cosy * _m[3] + (sinz * siny * sinx + cosz * cosx) * _m[7] + (sinz * siny * cosx - cosz * sinx) * _m[11];

        _m[ 8] = (-siny) * _m[0] + cosy * sinx * _m[4] + cosy * cosx * _m[ 8];
        _m[ 9] = (-siny) * _m[1] + cosy * sinx * _m[5] + cosy * cosx * _m[ 9];
        _m[10] = (-siny) * _m[2] + cosy * sinx * _m[6] + cosy * cosx * _m[10];
        _m[11] = (-siny) * _m[3] + cosy * sinx * _m[7] + cosy * cosx * _m[11];
    }



    void Matrix4x4::multVectors3(F32* __restrict vectors, U32 size) const
    {
        if ((size % 3) != 0 || vectors == NULL)
            return;

        F32 x, y, z;

        for (U32 i = 0; i < size; i += 3)
        {
            x = _m[ 0] * vectors[i] + _m[ 1] * vectors[i + 1] + _m[ 2] * vectors[i + 2] + _m[ 3];
            y = _m[ 4] * vectors[i] + _m[ 5] * vectors[i + 1] + _m[ 6] * vectors[i + 2] + _m[ 7];
            z = _m[ 8] * vectors[i] + _m[ 9] * vectors[i + 1] + _m[10] * vectors[i + 2] + _m[11];

            vectors[i]     = x;
            vectors[i + 1] = y;
            vectors[i + 2] = z;
        }
    }



    void Matrix4x4::multVectors4(F32* __restrict vectors, U32 size) const
    {
        if ((size % 4) != 0 || vectors == NULL)
            return;

        F32 result[4];

        for (U32 i = 0; i < size; i += 4)
        {
            result[0] = _m[ 0] * vectors[i] + _m[ 1] * vectors[i + 1] + _m[ 2] * vectors[i + 2] + _m[ 3] * vectors[i + 3];
            result[1] = _m[ 4] * vectors[i] + _m[ 5] * vectors[i + 1] + _m[ 6] * vectors[i + 2] + _m[ 7] * vectors[i + 3];
            result[2] = _m[ 8] * vectors[i] + _m[ 9] * vectors[i + 1] + _m[10] * vectors[i + 2] + _m[11] * vectors[i + 3];
            result[3] = _m[12] * vectors[i] + _m[13] * vectors[i + 1] + _m[14] * vectors[i + 2] + _m[15] * vectors[i + 3];

            vectors[i]     = result[0];
            vectors[i + 1] = result[1];
            vectors[i + 2] = result[2];
            vectors[i + 3] = result[3];
        }
    }



    void Matrix4x4::sseMultVectors3(F32* vectors, U32 size) const
    {
        // Check data and address alignment
        if ((size % 3) != 0 || vectors == NULL || ((uintptr_t)vectors & 0xF) != 0 )
            return;

        // The SSE computation loop below needs at least 12 vectors
        if (size < 12)
        {
            multVectors3(vectors, size);
            
            return;
        }
    
        // Because of SSE instructions, 4 coordinates values
        // are loaded at a time.

        __m128 mc1, mc2, mc3, mc4; // Matrix columns
        __m128 x4, y4, z4, x4_, y4_, z4_; // Vector values    
    
        mc1 = _mm_set_ps(_m[12], _m[ 8], _m[4], _m[ 0]);
        mc2 = _mm_set_ps(_m[13], _m[ 9], _m[5], _m[ 1]);
        mc3 = _mm_set_ps(_m[14], _m[10], _m[6], _m[ 2]);
        mc4 = _mm_set_ps(_m[15], _m[11], _m[7], _m[ 3]);

        FEN_ALIGNED_DECL(F32, aux[4], 16);
        __m128* auxp = (__m128*)aux;
        __m128* rp = (__m128*)vectors;

        U32 remaining = size % 12;         // Number of elements that will not be computed in the loop below
        U32 splitPoint = size - remaining; // Last element computed in the loop below

        for (U32 i = 0; i < splitPoint; i += 12)
        {
            // Get coord values
            x4  = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(0, 0, 0, 0));
            y4  = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(1, 1, 1, 1));
            z4  = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(2, 2, 2, 2));
            x4_ = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(3, 3, 3, 3));

            // Compute
            *rp = _mm_add_ps(_mm_mul_ps(mc1, x4), _mm_mul_ps(mc2, y4));
            *rp = _mm_add_ps(*rp, _mm_mul_ps(mc3, z4));
            *rp = _mm_add_ps(*rp, mc4);
    
            // Go to next pack of 4 float values
            rp++;

            // Get coord values
            y4  = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(0, 0, 0, 0));
            z4  = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(1, 1, 1, 1));
            x4  = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(2, 2, 2, 2));
            y4_ = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(3, 3, 3, 3));

            // Compute
            *auxp = _mm_add_ps(_mm_mul_ps(mc1, x4_), _mm_mul_ps(mc2, y4));
            *auxp = _mm_add_ps(*auxp, _mm_mul_ps(mc3, z4));
            *auxp = _mm_add_ps(*auxp, mc4);
            vectors[i + 3] = aux[0];
            vectors[i + 4] = aux[1];
            vectors[i + 5] = aux[2];
    
            // Go to next pack of 4 float values
            rp++;

            // Get coord values
            z4 = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(0, 0, 0, 0));

            // Compute
            *auxp = _mm_add_ps(_mm_mul_ps(mc1, x4), _mm_mul_ps(mc2, y4_));
            *auxp = _mm_add_ps(*auxp, _mm_mul_ps(mc3, z4));
            *auxp = _mm_add_ps(*auxp, mc4);
            vectors[i + 6] = aux[0];
            vectors[i + 7] = aux[1];
            vectors[i + 8] = aux[2];

            // Get coord values
            x4  = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(1, 1, 1, 1));
            y4  = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(2, 2, 2, 2));
            z4_ = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(3, 3, 3, 3));

            // Compute
            *auxp = _mm_add_ps(_mm_mul_ps(mc1, x4), _mm_mul_ps(mc2, y4));
            *auxp = _mm_add_ps(*auxp, _mm_mul_ps(mc3, z4_));
            *auxp = _mm_add_ps(*auxp, mc4);
            vectors[i +  9] = aux[0];
            vectors[i + 10] = aux[1];
            vectors[i + 11] = aux[2];
    
            // Go to next pack of 4 float values
            rp++;
        }

        // Compute the remaining coordinates
        Vector3 vec;
        for (U32 i = splitPoint; i < size; i += 3)
        {
            vec.x = vectors[i];
            vec.y = vectors[i + 1];
            vec.z = vectors[i + 2];

            vec = *this * vec;

            vectors[i    ] = vec.x;
            vectors[i + 1] = vec.y;
            vectors[i + 2] = vec.z;
        }
    }
    
    
    void Matrix4x4::sseMultVectors4(F32* vectors, U32 size) const
    {
        // Check data and address alignment
        if ((size % 4) != 0 || vectors == NULL || ((uintptr_t)vectors & 0xF) != 0 )
            return;
    
        __m128 mc1, mc2, mc3, mc4; // Matrix columns
        __m128 x4, y4, z4, w4; // Vector values
    
        mc1 = _mm_set_ps(_m[12], _m[ 8], _m[4], _m[ 0]);
        mc2 = _mm_set_ps(_m[13], _m[ 9], _m[5], _m[ 1]);
        mc3 = _mm_set_ps(_m[14], _m[10], _m[6], _m[ 2]);
        mc4 = _mm_set_ps(_m[15], _m[11], _m[7], _m[ 3]);
    
        __m128* rp = (__m128*)vectors;

        for (U32 i = 0; i < size / 4; i++)
        {
            x4 = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(0, 0, 0, 0));
            y4 = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(1, 1, 1, 1));
            z4 = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(2, 2, 2, 2));
            w4 = _mm_shuffle_ps(*rp, *rp, _MM_SHUFFLE(3, 3, 3, 3));
    
            *rp = _mm_add_ps(_mm_mul_ps(mc1, x4), _mm_mul_ps(mc2, y4));
            *rp = _mm_add_ps(*rp, _mm_mul_ps(mc3, z4));
            *rp = _mm_add_ps(*rp, _mm_mul_ps(mc4, w4));
    
            rp++;
        }
    }


    Matrix4x4 Matrix4x4::_generalInverse(F32 determinant) const
    {
        if (Math::abs(determinant) < Math::EPSILON)
            return Matrix4x4::ZERO;

        Matrix4x4 inv;

        inv._m[ 0] = _m[ 6]*_m[11]*_m[13] - _m[ 7]*_m[10]*_m[13] + _m[ 7]*_m[ 9]*_m[14] - _m[ 5]*_m[11]*_m[14] - _m[ 6]*_m[ 9]*_m[15] + _m[ 5]*_m[10]*_m[15];
        inv._m[ 1] = _m[ 3]*_m[10]*_m[13] - _m[ 2]*_m[11]*_m[13] - _m[ 3]*_m[ 9]*_m[14] + _m[ 1]*_m[11]*_m[14] + _m[ 2]*_m[ 9]*_m[15] - _m[ 1]*_m[10]*_m[15];
        inv._m[ 2] = _m[ 2]*_m[ 7]*_m[13] - _m[ 3]*_m[ 6]*_m[13] + _m[ 3]*_m[ 5]*_m[14] - _m[ 1]*_m[ 7]*_m[14] - _m[ 2]*_m[ 5]*_m[15] + _m[ 1]*_m[ 6]*_m[15];
        inv._m[ 3] = _m[ 3]*_m[ 6]*_m[ 9] - _m[ 2]*_m[ 7]*_m[ 9] - _m[ 3]*_m[ 5]*_m[10] + _m[ 1]*_m[ 7]*_m[10] + _m[ 2]*_m[ 5]*_m[11] - _m[ 1]*_m[ 6]*_m[11];
        inv._m[ 4] = _m[ 7]*_m[10]*_m[12] - _m[ 6]*_m[11]*_m[12] - _m[ 7]*_m[ 8]*_m[14] + _m[ 4]*_m[11]*_m[14] + _m[ 6]*_m[ 8]*_m[15] - _m[ 4]*_m[10]*_m[15];
        inv._m[ 5] = _m[ 2]*_m[11]*_m[12] - _m[ 3]*_m[10]*_m[12] + _m[ 3]*_m[ 8]*_m[14] - _m[ 0]*_m[11]*_m[14] - _m[ 2]*_m[ 8]*_m[15] + _m[ 0]*_m[10]*_m[15];
        inv._m[ 6] = _m[ 3]*_m[ 6]*_m[12] - _m[ 2]*_m[ 7]*_m[12] - _m[ 3]*_m[ 4]*_m[14] + _m[ 0]*_m[ 7]*_m[14] + _m[ 2]*_m[ 4]*_m[15] - _m[ 0]*_m[ 6]*_m[15];
        inv._m[ 7] = _m[ 2]*_m[ 7]*_m[ 8] - _m[ 3]*_m[ 6]*_m[ 8] + _m[ 3]*_m[ 4]*_m[10] - _m[ 0]*_m[ 7]*_m[10] - _m[ 2]*_m[ 4]*_m[11] + _m[ 0]*_m[ 6]*_m[11];
        inv._m[ 8] = _m[ 5]*_m[11]*_m[12] - _m[ 7]*_m[ 9]*_m[12] + _m[ 7]*_m[ 8]*_m[13] - _m[ 4]*_m[11]*_m[13] - _m[ 5]*_m[ 8]*_m[15] + _m[ 4]*_m[ 9]*_m[15];
        inv._m[ 9] = _m[ 3]*_m[ 9]*_m[12] - _m[ 1]*_m[11]*_m[12] - _m[ 3]*_m[ 8]*_m[13] + _m[ 0]*_m[11]*_m[13] + _m[ 1]*_m[ 8]*_m[15] - _m[ 0]*_m[ 9]*_m[15];
        inv._m[10] = _m[ 1]*_m[ 7]*_m[12] - _m[ 3]*_m[ 5]*_m[12] + _m[ 3]*_m[ 4]*_m[13] - _m[ 0]*_m[ 7]*_m[13] - _m[ 1]*_m[ 4]*_m[15] + _m[ 0]*_m[ 5]*_m[15];
        inv._m[11] = _m[ 3]*_m[ 5]*_m[ 8] - _m[ 1]*_m[ 7]*_m[ 8] - _m[ 3]*_m[ 4]*_m[ 9] + _m[ 0]*_m[ 7]*_m[ 9] + _m[ 1]*_m[ 4]*_m[11] - _m[ 0]*_m[ 5]*_m[11];
        inv._m[12] = _m[ 6]*_m[ 9]*_m[12] - _m[ 5]*_m[10]*_m[12] - _m[ 6]*_m[ 8]*_m[13] + _m[ 4]*_m[10]*_m[13] + _m[ 5]*_m[ 8]*_m[14] - _m[ 4]*_m[ 9]*_m[14];
        inv._m[13] = _m[ 1]*_m[10]*_m[12] - _m[ 2]*_m[ 9]*_m[12] + _m[ 2]*_m[ 8]*_m[13] - _m[ 0]*_m[10]*_m[13] - _m[ 1]*_m[ 8]*_m[14] + _m[ 0]*_m[ 9]*_m[14];
        inv._m[14] = _m[ 2]*_m[ 5]*_m[12] - _m[ 1]*_m[ 6]*_m[12] - _m[ 2]*_m[ 4]*_m[13] + _m[ 0]*_m[ 6]*_m[13] + _m[ 1]*_m[ 4]*_m[14] - _m[ 0]*_m[ 5]*_m[14];
        inv._m[15] = _m[ 1]*_m[ 6]*_m[ 8] - _m[ 2]*_m[ 5]*_m[ 8] + _m[ 2]*_m[ 4]*_m[ 9] - _m[ 0]*_m[ 6]*_m[ 9] - _m[ 1]*_m[ 4]*_m[10] + _m[ 0]*_m[ 5]*_m[10];

        return inv * (1.0f / determinant);
    }

    Matrix4x4 Matrix4x4::_affinelInverse(F32 determinant) const
    {
        if (Math::abs(determinant) < Math::EPSILON)
            return Matrix4x4::ZERO;

        Matrix4x4 inv;

        inv._m[ 0] = _m[ 5]*_m[10] - _m[ 6]*_m[ 9];
        inv._m[ 1] = _m[ 2]*_m[ 9] - _m[ 1]*_m[10];
        inv._m[ 2] = _m[ 1]*_m[ 6] - _m[ 2]*_m[ 5];
        inv._m[ 3] = _m[ 3]*_m[ 6]*_m[ 9] - _m[ 2]*_m[ 7]*_m[ 9] - _m[ 3]*_m[ 5]*_m[10] + _m[ 1]*_m[ 7]*_m[10] + _m[ 2]*_m[ 5]*_m[11] - _m[ 1]*_m[ 6]*_m[11];
        inv._m[ 4] = _m[ 6]*_m[ 8] - _m[ 4]*_m[10];
        inv._m[ 5] = _m[ 0]*_m[10] - _m[ 2]*_m[ 8];
        inv._m[ 6] = _m[ 2]*_m[ 4] - _m[ 0]*_m[ 6];
        inv._m[ 7] = _m[ 2]*_m[ 7]*_m[ 8] - _m[ 3]*_m[ 6]*_m[ 8] + _m[ 3]*_m[ 4]*_m[10] - _m[ 0]*_m[ 7]*_m[10] - _m[ 2]*_m[ 4]*_m[11] + _m[ 0]*_m[ 6]*_m[11];
        inv._m[ 8] = _m[ 4]*_m[ 9] - _m[ 5]*_m[ 8];
        inv._m[ 9] = _m[ 1]*_m[ 8] - _m[ 0]*_m[ 9];
        inv._m[10] = _m[ 0]*_m[ 5] - _m[ 1]*_m[ 4];
        inv._m[11] = _m[ 3]*_m[ 5]*_m[ 8] - _m[ 1]*_m[ 7]*_m[ 8] - _m[ 3]*_m[ 4]*_m[ 9] + _m[ 0]*_m[ 7]*_m[ 9] + _m[ 1]*_m[ 4]*_m[11] - _m[ 0]*_m[ 5]*_m[11];
        inv._m[12] = 0;
        inv._m[13] = 0;
        inv._m[14] = 0;
        inv._m[15] = _m[ 1]*_m[ 6]*_m[ 8] - _m[ 2]*_m[ 5]*_m[ 8] + _m[ 2]*_m[ 4]*_m[ 9] - _m[ 0]*_m[ 6]*_m[ 9] - _m[ 1]*_m[ 4]*_m[10] + _m[ 0]*_m[ 5]*_m[10];

        return inv * (1.0f / determinant);
    }
}