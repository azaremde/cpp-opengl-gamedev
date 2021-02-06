#pragma once

namespace math
{
    using mat4x4 = float[4][4];
    using vec4 = float[4];
    using vec3 = float[3];
    using vec2 = float[2];

    inline void identify(mat4x4& output)
    {
        output[0][0] = 1; output[0][1] = 0; output[0][2] = 0; output[0][3] = 0;
        output[1][0] = 0; output[1][1] = 1; output[1][2] = 0; output[1][3] = 0;
        output[2][0] = 0; output[2][1] = 0; output[2][2] = 1; output[2][3] = 0;
        output[3][0] = 0; output[3][1] = 0; output[3][2] = 0; output[3][3] = 1;
    }

    inline void nullify(mat4x4& output)
    {
        output[0][0] = 0; output[0][1] = 0; output[0][2] = 0; output[0][3] = 0;
        output[1][0] = 0; output[1][1] = 0; output[1][2] = 0; output[1][3] = 0;
        output[2][0] = 0; output[2][1] = 0; output[2][2] = 0; output[2][3] = 0;
        output[3][0] = 0; output[3][1] = 0; output[3][2] = 0; output[3][3] = 0;
    }

    inline void mul_mat4x4_vec4(vec4 R, const mat4x4 A, const vec4 B)
    {
        R[0] = A[0][0] * B[0] + A[1][0] * B[1] + A[2][0] * B[2] + A[3][0] * B[3];
        R[1] = A[0][1] * B[0] + A[1][1] * B[1] + A[2][1] * B[2] + A[3][1] * B[3];
        R[2] = A[0][2] * B[0] + A[1][2] * B[1] + A[2][2] * B[2] + A[3][2] * B[3];
        R[3] = A[0][3] * B[0] + A[1][3] * B[1] + A[2][3] * B[2] + A[3][3] * B[3];
    }

    inline void dot_vec4_vec4(vec4& output, const vec4& a, const vec4& b)
    {
        output[0] = a[0] * b[0];
        output[1] = a[1] * b[1];
        output[2] = a[2] * b[2];
        output[3] = a[3] * b[3];
    }

    inline void perspective(mat4x4& output, const float& fov, const float& aspect, const float& zNear, const float& zFar)
    {
        nullify(output);

		float const tanHalfFovy = tan(fov / 2.0f);

		output[0][0] = 1.0f / (aspect * tanHalfFovy);
		output[1][1] = 1.0f / (tanHalfFovy);
		output[2][2] = - (zFar + zNear) / (zFar - zNear);
		output[2][3] = - 1.0f;
		output[3][2] = - (2.0f * zFar * zNear) / (zFar - zNear);
    }

    inline void mul_mat4x4_mat4x4(mat4x4& output, const mat4x4& a, const mat4x4& b)
    {
        output[0][0] = b[0][0] * a[0][0] + b[0][1] * a[1][0] + b[0][2] * a[2][0] + b[0][3] * a[3][0];
        output[0][1] = b[0][0] * a[0][1] + b[0][1] * a[1][1] + b[0][2] * a[2][1] + b[0][3] * a[3][1];
        output[0][2] = b[0][0] * a[0][2] + b[0][1] * a[1][2] + b[0][2] * a[2][2] + b[0][3] * a[3][2];
        output[0][3] = b[0][0] * a[0][3] + b[0][1] * a[1][3] + b[0][2] * a[2][3] + b[0][3] * a[3][3];

        output[1][0] = b[1][0] * a[0][0] + b[1][1] * a[1][0] + b[1][2] * a[2][0] + b[1][3] * a[3][0];
        output[1][1] = b[1][0] * a[0][1] + b[1][1] * a[1][1] + b[1][2] * a[2][1] + b[1][3] * a[3][1];
        output[1][2] = b[1][0] * a[0][2] + b[1][1] * a[1][2] + b[1][2] * a[2][2] + b[1][3] * a[3][2];
        output[1][3] = b[1][0] * a[0][3] + b[1][1] * a[1][3] + b[1][2] * a[2][3] + b[1][3] * a[3][3];

        output[2][0] = b[2][0] * a[0][0] + b[2][1] * a[1][0] + b[2][2] * a[2][0] + b[2][3] * a[3][0];
        output[2][1] = b[2][0] * a[0][1] + b[2][1] * a[1][1] + b[2][2] * a[2][1] + b[2][3] * a[3][1];
        output[2][2] = b[2][0] * a[0][2] + b[2][1] * a[1][2] + b[2][2] * a[2][2] + b[2][3] * a[3][2];
        output[2][3] = b[2][0] * a[0][3] + b[2][1] * a[1][3] + b[2][2] * a[2][3] + b[2][3] * a[3][3];

        output[3][0] = b[3][0] * a[0][0] + b[3][1] * a[1][0] + b[3][2] * a[2][0] + b[3][3] * a[3][0];
        output[3][1] = b[3][0] * a[0][1] + b[3][1] * a[1][1] + b[3][2] * a[2][1] + b[3][3] * a[3][1];
        output[3][2] = b[3][0] * a[0][2] + b[3][1] * a[1][2] + b[3][2] * a[2][2] + b[3][3] * a[3][2];
        output[3][3] = b[3][0] * a[0][3] + b[3][1] * a[1][3] + b[3][2] * a[2][3] + b[3][3] * a[3][3];
    }

    inline void rotate(mat4x4& output, const mat4x4& input, const float& alpha, const float& ux, const float& uy, const float& uz)
    {
        float cosa = cos(alpha);
        float sina = sin(alpha);

        mat4x4 rotate;
        identify(rotate);

        rotate[0][0] = cosa + ux * ux * (1 - cosa);
        rotate[1][0] = ux * uy * (1 - cosa) - uz * sina;
        rotate[2][0] = ux * uz * (1 - cosa) + uy * sina;

        rotate[0][1] = uy * ux * (1 - cosa) + uz * sina;
        rotate[1][1] = cosa + uy * uy * (1 - cosa);
        rotate[2][1] = uy * uz * (1 - cosa) - ux * sina;

        rotate[0][2] = uz * ux * (1 - cosa) - uy * sina;
        rotate[1][2] = uz * uy * (1 - cosa) + ux * sina;
        rotate[2][2] = cosa + uz * uz * (1 - cosa);
        
        mul_mat4x4_mat4x4(output, input, rotate);
    }

    inline void translate(mat4x4& output, const mat4x4& input, float ux, float uy, float uz)
    {
        output[3][0] = input[0][0] * ux + input[1][0] * uy + input[2][0] * uz + input[3][0];
        output[3][1] = input[0][1] * ux + input[1][1] * uy + input[2][1] * uz + input[3][1];
        output[3][2] = input[0][2] * ux + input[1][2] * uy + input[2][2] * uz + input[3][2];
        output[3][3] = input[0][3] * ux + input[1][3] * uy + input[2][3] * uz + input[3][3];
    }
}