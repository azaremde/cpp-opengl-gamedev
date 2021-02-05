#pragma once

namespace math
{
    using mat4x4 = float[4][4];
    using vec4 = float[4];
    using vec3 = float[3];
    using vec2 = float[2];

    inline static const mat4x4 identity = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    inline void mul_mat4x4_vec4(vec4 R, const mat4x4 A, const vec4 B)
    {
        R[0] = A[0][0] * B[0] + A[1][0] * B[1] + A[2][0] * B[2] + A[3][0] * B[3];
        R[1] = A[0][1] * B[0] + A[1][1] * B[1] + A[2][1] * B[2] + A[3][1] * B[3];
        R[2] = A[0][2] * B[0] + A[1][2] * B[1] + A[2][2] * B[2] + A[3][2] * B[3];
        R[3] = A[0][3] * B[0] + A[1][3] * B[1] + A[2][3] * B[2] + A[3][3] * B[3];
    }

    inline void mul(vec4 R, vec4 a, vec4 b)
    {
        R[0] = a[0] * b[0];
        R[1] = a[1] * b[1];
        R[2] = a[2] * b[2];
        R[3] = a[3] * b[3];
    }

    inline void mul(vec4 R, vec4 a, float b, vec4 a1, float b1, vec4 a2, float b2)
    {
        R[0] = a[0] * b + a1[0] * b1 + a2[0] * b2;
        R[1] = a[1] * b + a1[1] * b1 + a2[1] * b2;
        R[2] = a[2] * b + a1[2] * b1 + a2[2] * b2;
        R[3] = a[3] * b + a1[3] * b1 + a2[3] * b2;
    }

    inline void identify(mat4x4& R)
    {
        R[0][0] = 1;
        R[0][1] = 0;
        R[0][2] = 0;
        R[0][3] = 0;
        R[1][0] = 0;
        R[1][1] = 1;
        R[1][2] = 0;
        R[1][3] = 0;
        R[2][0] = 0;
        R[2][1] = 0;
        R[2][2] = 1;
        R[2][3] = 0;
        R[3][0] = 0;
        R[3][1] = 0;
        R[3][2] = 0;
        R[3][3] = 1;
    }

    inline void nullify(mat4x4& R)
    {
        R[0][0] = 0;
        R[0][1] = 0;
        R[0][2] = 0;
        R[0][3] = 0;
        R[1][0] = 0;
        R[1][1] = 0;
        R[1][2] = 0;
        R[1][3] = 0;
        R[2][0] = 0;
        R[2][1] = 0;
        R[2][2] = 0;
        R[2][3] = 0;
        R[3][0] = 0;
        R[3][1] = 0;
        R[3][2] = 0;
        R[3][3] = 0;
    }

    inline void perspective(mat4x4& R, float fov, float aspect, float zNear, float zFar)
    {
        nullify(R);

		float const tanHalfFovy = tan(fov / 2.0f);

		R[0][0] = 1.0f / (aspect * tanHalfFovy);
		R[1][1] = 1.0f / (tanHalfFovy);
		R[2][2] = - (zFar + zNear) / (zFar - zNear);
		R[2][3] = - 1.0f;
		R[3][2] = - (2.0f * zFar * zNear) / (zFar - zNear);
    }

    inline void mul_mat4x4_mat4x4(mat4x4 R, const mat4x4 A, const mat4x4 B)
    {
        R[0][0] = B[0][0] * A[0][0] + B[0][1] * A[1][0] + B[0][2] * A[2][0] + B[0][3] * A[3][0];
        R[0][1] = B[0][0] * A[0][1] + B[0][1] * A[1][1] + B[0][2] * A[2][1] + B[0][3] * A[3][1];
        R[0][2] = B[0][0] * A[0][2] + B[0][1] * A[1][2] + B[0][2] * A[2][2] + B[0][3] * A[3][2];
        R[0][3] = B[0][0] * A[0][3] + B[0][1] * A[1][3] + B[0][2] * A[2][3] + B[0][3] * A[3][3];

        R[1][0] = B[1][0] * A[0][0] + B[1][1] * A[1][0] + B[1][2] * A[2][0] + B[1][3] * A[3][0];
        R[1][1] = B[1][0] * A[0][1] + B[1][1] * A[1][1] + B[1][2] * A[2][1] + B[1][3] * A[3][1];
        R[1][2] = B[1][0] * A[0][2] + B[1][1] * A[1][2] + B[1][2] * A[2][2] + B[1][3] * A[3][2];
        R[1][3] = B[1][0] * A[0][3] + B[1][1] * A[1][3] + B[1][2] * A[2][3] + B[1][3] * A[3][3];

        R[2][0] = B[2][0] * A[0][0] + B[2][1] * A[1][0] + B[2][2] * A[2][0] + B[2][3] * A[3][0];
        R[2][1] = B[2][0] * A[0][1] + B[2][1] * A[1][1] + B[2][2] * A[2][1] + B[2][3] * A[3][1];
        R[2][2] = B[2][0] * A[0][2] + B[2][1] * A[1][2] + B[2][2] * A[2][2] + B[2][3] * A[3][2];
        R[2][3] = B[2][0] * A[0][3] + B[2][1] * A[1][3] + B[2][2] * A[2][3] + B[2][3] * A[3][3];

        R[3][0] = B[3][0] * A[0][0] + B[3][1] * A[1][0] + B[3][2] * A[2][0] + B[3][3] * A[3][0];
        R[3][1] = B[3][0] * A[0][1] + B[3][1] * A[1][1] + B[3][2] * A[2][1] + B[3][3] * A[3][1];
        R[3][2] = B[3][0] * A[0][2] + B[3][1] * A[1][2] + B[3][2] * A[2][2] + B[3][3] * A[3][2];
        R[3][3] = B[3][0] * A[0][3] + B[3][1] * A[1][3] + B[3][2] * A[2][3] + B[3][3] * A[3][3];
    }

    inline void rotate(mat4x4& result, float alpha, float ux, float uy, float uz)
    {
        float cosa = cos(alpha);
        float sina = sin(alpha);

        result[0][0] = cosa + ux * ux * (1 - cosa);
        result[1][0] = ux * uy * (1 - cosa) - uz * sina;
        result[2][0] = ux * uz * (1 - cosa) + uy * sina;

        result[0][1] = uy * ux * (1 - cosa) + uz * sina;
        result[1][1] = cosa + uy * uy * (1 - cosa);
        result[2][1] = uy * uz * (1 - cosa) - ux * sina;

        result[0][2] = uz * ux * (1 - cosa) - uy * sina;
        result[1][2] = uz * uy * (1 - cosa) + ux * sina;
        result[2][2] = cosa + uz * uz * (1 - cosa);
    }

    inline void translate(mat4x4& result, float ux, float uy, float uz)
    {        
        result[3][0] = result[0][0] * ux + result[1][0] * uy + result[2][0] * uz + result[3][0];
        result[3][1] = result[0][1] * ux + result[1][1] * uy + result[2][1] * uz + result[3][1];
        result[3][2] = result[0][2] * ux + result[1][2] * uy + result[2][2] * uz + result[3][2];
        result[3][3] = result[0][3] * ux + result[1][3] * uy + result[2][3] * uz + result[3][3];
    }
}