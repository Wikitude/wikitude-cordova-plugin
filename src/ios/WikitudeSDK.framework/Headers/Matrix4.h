//
//  Matrix4.h
//
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#ifndef __CommonLibrary__Matrix4__
#define __CommonLibrary__Matrix4__

#ifdef __cplusplus

#include <iostream>
#include <iomanip>

namespace wikitude { namespace sdk {
    
    namespace impl {

        class Matrix4
        {
        public:
            static constexpr float EPSILON = 0.00001f;
            static constexpr float DEG2RAD = 3.141593f / 180.0f;
            
            Matrix4();
            explicit Matrix4(const float* const src);
            Matrix4(float m00, float m01, float m02, float m03, float m04, float m05, float m06, float m07, float m08, float m09, float m10, float m11, float m12, float m13, float m14, float m15);

            void set(const float* const src);
            void set(float m00, float m01, float m02, float m03, float m04, float m05, float m06, float m07, float m08, float m09, float m10, float m11, float m12, float m13, float m14, float m15);
            void setRow(int index, const float* const row);
            void setRow(int index, float x, float y, float z, float w);
            void setColumn(int index, const float* const col);
            void setColumn(int index, float x, float y, float z, float w);

            const float* get() const;
            float getDeterminant();

            float getRotationX() const;
            float getRotationY() const;
            float getRotationZ() const;

            Matrix4& identity();
            Matrix4& transpose();
            Matrix4& invert();

            Matrix4& translate(float x, float y, float z);
            Matrix4& rotate(float angle, float x, float y, float z);
            Matrix4& rotateX(float angle);
            Matrix4& rotateY(float angle);
            Matrix4& rotateZ(float angle);
            Matrix4& scale(float scale);
            Matrix4& scale(float sx, float sy, float sz);

            Matrix4& perspective(float fovY, float aspect, float front, float back);
            
            Matrix4 operator+(const Matrix4& rhs) const;
            Matrix4& operator+=(const Matrix4& rhs);
            Matrix4 operator-(const Matrix4& rhs) const;
            Matrix4& operator-=(const Matrix4& rhs);
            Matrix4 operator*(const Matrix4& rhs) const;
            Matrix4& operator*=(const Matrix4& rhs);
            float operator[](int index) const;
            float& operator[](int index);

            friend Matrix4 operator-(const Matrix4& m);
            friend Matrix4 operator*(float scalar, const Matrix4& m);
            friend std::ostream& operator<<(std::ostream& os, const Matrix4& m);

        private:
            float getCofactor(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8);

            Matrix4 setFrustum(float left, float right, float bottom, float top, float near, float far);
            Matrix4 setFrustum(float fovY, float aspect, float front, float back);
            
            float m[16];
        };
    }
    using impl::Matrix4;
}}

#endif /* __cplusplus */

#endif /* defined(__CommonLibrary__Matrix4__) */
