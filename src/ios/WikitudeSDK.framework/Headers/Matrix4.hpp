//
//  Matrix4.hpp
//
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#ifndef Matrix4_hpp
#define Matrix4_hpp

#ifdef __cplusplus

#include <iostream>
#include <iomanip>

#include "CompilerAttributes.hpp"


namespace wikitude::sdk {

        /**
        * A four by four, float based matrix providing methods for spatial transformations in three dimensions. The matrix data is arranged in column-major order.
        */
        class WT_EXPORT_API Matrix4
        {
        public:
            static constexpr float EPSILON = 0.00001f;
#ifdef DEG2RAD
#undef DEG2RAD
#endif
            static constexpr float DEG2RAD = 3.141593f / 180.0f;

            /**
            * Initializes the matrix to the identity.
            */
            Matrix4();

            /**
            * Initializes the matrix using a float pointer.
            *
            * @param src A pointer-to-float to be used to initialize the matrix. The data pointed to is required to be 16 consecutive float values.
            */
            explicit Matrix4(const float* const src);

            /**
            * Initializes the matrix using 16 distinct float values
            *
            * @param m00 The float value to be applied to the element at index 0.
            * @param m01 The float value to be applied to the element at index 1.
            * @param m02 The float value to be applied to the element at index 2.
            * @param m03 The float value to be applied to the element at index 3.
            * @param m04 The float value to be applied to the element at index 4.
            * @param m05 The float value to be applied to the element at index 5.
            * @param m06 The float value to be applied to the element at index 6.
            * @param m07 The float value to be applied to the element at index 7.
            * @param m08 The float value to be applied to the element at index 8.
            * @param m09 The float value to be applied to the element at index 9.
            * @param m10 The float value to be applied to the element at index 10.
            * @param m11 The float value to be applied to the element at index 11.
            * @param m12 The float value to be applied to the element at index 12.
            * @param m13 The float value to be applied to the element at index 13.
            * @param m14 The float value to be applied to the element at index 14.
            * @param m15 The float value to be applied to the element at index 15.
            */
            Matrix4(float m00, float m01, float m02, float m03, float m04, float m05, float m06, float m07, float m08, float m09, float m10, float m11, float m12, float m13, float m14, float m15);

            /**
            * Sets the matrix data using a float pointer.
            *
            * @param src A pointer-to-float to be used to set the matrix data. The data pointed to is required to be 16 consecutive float values.
            */
            void set(const float* const src);

            /**
            * Sets the matrix data using 16 distinct float values
            *
            * @param m00 The float value to be applied to the element at index 0.
            * @param m01 The float value to be applied to the element at index 1.
            * @param m02 The float value to be applied to the element at index 2.
            * @param m03 The float value to be applied to the element at index 3.
            * @param m04 The float value to be applied to the element at index 4.
            * @param m05 The float value to be applied to the element at index 5.
            * @param m06 The float value to be applied to the element at index 6.
            * @param m07 The float value to be applied to the element at index 7.
            * @param m08 The float value to be applied to the element at index 8.
            * @param m09 The float value to be applied to the element at index 9.
            * @param m10 The float value to be applied to the element at index 10.
            * @param m11 The float value to be applied to the element at index 11.
            * @param m12 The float value to be applied to the element at index 12.
            * @param m13 The float value to be applied to the element at index 13.
            * @param m14 The float value to be applied to the element at index 14.
            * @param m15 The float value to be applied to the element at index 15.
            */
            void set(float m00, float m01, float m02, float m03, float m04, float m05, float m06, float m07, float m08, float m09, float m10, float m11, float m12, float m13, float m14, float m15);

            /**
            * Sets the matrix data for the specified row.
            *
            * @param index The zero based index specifying the row to be set. The index is required to be within the interval [0, 3].
            * @param row A pointer-to-float to be used to set the row data. The data pointed to is required to be 4 consecutive float values.
            */
            void setRow(int index, const float* const row);

            /**
            * Sets the matrix data for the specified row.
            *
            * @param index The zero based index specifying the row to be set. The index is required to be within the interval [0, 3].
            * @param x The first element of the row to be set.
            * @param y The second element of the row to be set.
            * @param z The third element of the row to be set.
            * @param w The fourth element of the row to be set.
            */
            void setRow(int index, float x, float y, float z, float w);

            /**
            * Sets the matrix data for the specified column.
            *
            * @param index The zero based index specifying the column to be set. The index is required to be within the interval [0, 3].
            * @param col A pointer-to-float to be used to set the column data. The data pointed to is required to be 4 consecutive float values.
            */
            void setColumn(int index, const float* const col);

            /**
            * Sets the matrix data for the specified column.
            *
            * @param index The zero based index specifying the column to be set. The index is required to be within the interval [0, 3].
            * @param x The first element of the column to be set.
            * @param y The second element of the column to be set.
            * @param z The third element of the column to be set.
            * @param w The fourth element of the column to be set.
            */
            void setColumn(int index, float x, float y, float z, float w);

            /**
             * Returns a pointer-to-float to the matrix data.
             *
             * @return The pointer-to-const float to the matrix data. The data pointer to is 16 consecutive float values.
             */
            float* get();
            
            /**
            * Returns a pointer-to-const float to the matrix data.
            *
            * @return The pointer-to-const float to the matrix data. The data pointer to is 16 consecutive float values.
            */
            const float* get() const;

            /**
            * Computes the determinant of the matrix using cofactor expansion.
            *
            * @return The determinant of the matrix.
            */
            float getDeterminant();

            /**
            * Sets the matrix to the identity and returns a reference to itself.
            *
            * @return The reference to *this.
            */
            Matrix4& identity();

            /**
            * Transposes the matrix and returns a reference to itself.
            *
            * @return The reference to *this.
            */
            Matrix4& transpose();

            /**
            * Inverts the matrix and returns a reference to itself. The inversion is performed using the determinant and does not consider special cases that would allow less computationally expensive algorithms to be used. It does, however, return the identity if the determinant is below the value specified by Matrix::EPSILON.
            *
            * @return The reference to *this.
            */
            Matrix4& invert();

            /**
            * Translates the matrix using the supplied values and returns a reference to itself.
            * @param x The translation in X to applied.
            * @param y The translation in Y to applied.
            * @param z The translation in Z to applied.
            *
            * @return The reference to *this.
            */
            Matrix4& translate(float x, float y, float z);

            /**
            * Rotates the matrix using the supplied angle about the axis defined by the remaining values. Returns a reference to itself.
            *
            * @param angle The angle used for the rotation in degrees.
            * @param x The x-component of the rotation axis to be used.
            * @param y The y-component of the rotation axis to be used.
            * @param z The z-component of the rotation axis to be used.
            *
            * @return The reference to *this.
            */
            Matrix4& rotate(float angle, float x, float y, float z);

            /**
            * Rotates the matrix using the supplied angle about the x-axis. Returns a reference to itself.
            *
            * @param angle The angle used for the rotation in degrees.
            *
            * @return The reference to *this.
            */
            Matrix4& rotateX(float angle);

            /**
            * Rotates the matrix using the supplied angle about the y-axis. Returns a reference to itself.
            *
            * @param angle The angle used for the rotation in degrees.
            *
            * @return The reference to *this.
            */
            Matrix4& rotateY(float angle);

            /**
            * Rotates the matrix using the supplied angle about the z-axis. Returns a reference to itself.
            *
            * @param angle The angle used for the rotation in degrees.
            *
            * @return The reference to *this.
            */
            Matrix4& rotateZ(float angle);

            /**
            * Scales the matrix using the supplied uniform scale. Returns a reference to itself.
            *
            * @param scale The scale value used.
            *
            * @return The reference to *this.
            */
            Matrix4& scale(float scale);

            /**
            * Scales the matrix using the scale values. Returns a reference to itself.
            *
            * @param sx The scale value used for the X axis.
            * @param sy The scale value used for the Y axis.
            * @param sz The scale value used for the Z axis.
            *
            * @return The reference to *this.
            */
            Matrix4& scale(float sx, float sy, float sz);

            /**
            * Sets the matrix data to a perspective projection. Returns a reference to itself.
            *
            * @param fovY The vertical field of view in degrees.
            * @param aspect The aspect ratio.
            * @param front The near plane distance.
            * @param back The far plane distance.
            *
            * @return The reference to *this.
            */
            Matrix4& perspective(float fovY, float aspect, float front, float back);

            /**
            * Performs addition using this matrix and another. The state of this matrix is unchanged. Returns a copy of the result.
            *
            * @param rhs A reference to the other operand.
            *
            * @return The sum of the two matrices.
            */
            Matrix4 operator+(const Matrix4& rhs) const;

            /**
            * Adds another matrix to this matrix. The state of this matrix is changed. Returns a reference to itself.
            *
            * @param rhs A reference to the other operand.
            *
            * @return The reference to *this.
            */
            Matrix4& operator+=(const Matrix4& rhs);

            /**
            * Performs subtraction using this matrix and another. The state of this matrix is unchanged. Returns a copy of the result.
            *
            * @param rhs A reference to the other operand.
            *
            * @return The difference of the two matrices.
            */
            Matrix4 operator-(const Matrix4& rhs) const;

            /**
            * Subtracts another matrix from this matrix. The state of this matrix is changed. Returns a reference to itself.
            *
            * @param rhs A reference to the other operand.
            *
            * @return The reference to *this.
            */
            Matrix4& operator-=(const Matrix4& rhs);

            /**
            * Performs multiplication using this matrix and another. The state of this matrix is unchanged. Returns a copy of the result.
            *
            * @param rhs A reference to the other operand.
            *
            * @return The product of the two matrices.
            */
            Matrix4 operator*(const Matrix4& rhs) const;

            /**
            * Multiplies another matrix into this matrix. The state of this matrix is changed. Returns a reference to itself.
            *
            * @param rhs A reference to the other operand.
            *
            * @return The reference to *this.
            */
            Matrix4& operator*=(const Matrix4& rhs);

            /**
            * Provides a copy of a single value of the matrix.
            *
            * @param index The zero based index specifying the element to be accessed. The index is required to be within the interval [0, 15].
            *
            * @return The copy of a value of the matrix.
            */
            float operator[](int index) const;

            /**
            * Provides a reference to a single value of the matrix.
            *
            * @param index The zero based index specifying the element to be accessed. The index is required to be within the interval [0, 15].
            *
            * @return The reference to a value of the matrix.
            */
            float& operator[](int index);

            /**
             * Provides a copy of a single value of the matrix.
             *
             * @param row The zero based index specifying the row to be accessed. The row is required to be within the interval [0, 3].
             * @param column The zero based index specifying the column to be accessed. The column is required to be within the interval [0, 3].
             *
             * @return The copy of a value of the matrix.
             */
            float operator()(int row, int column) const;

            /**
             * Provides a reference to a single value of the matrix.
             *
             * @param row The zero based index specifying the row to be accessed. The row is required to be within the interval [0, 3].
             * @param column The zero based index specifying the column to be accessed. The column is required to be within the interval [0, 3].
             *
             * @return The reference to a value of the matrix.
             */
            float& operator()(int row, int column);

            /**
            * Negates the supplied matrix.
            *
            * @param m The matrix to be negated.
            *
            * @return The negated matrix.
            */
            friend WT_EXPORT_API Matrix4 operator-(const Matrix4& m);

            /**
            * Multiplies a scalar and a matrix.
            *
            * @param scalar The scalar operand.
            * @param m The matrix operand.
            *
            * @return The product of the scalar and the matrix.
            */
            friend WT_EXPORT_API Matrix4 operator*(float scalar, const Matrix4& m);

            /**
            * A stream operator to allow convenient printing of the matrix content.
            *
            * @param os The stream to add the matrix content to.
            * @param m The matrix to add to the stream.
            *
            * @return The reference to the resulting stream.
            */
            friend WT_EXPORT_API std::ostream& operator<<(std::ostream& os, const Matrix4& m);

        private:
            float getCofactor(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8);

            Matrix4 setFrustum(float left, float right, float bottom, float top, float near, float far);
            Matrix4 setFrustum(float fovY, float aspect, float front, float back);

            float m[16];
        };
}
            
#endif /* __cplusplus */

#endif /* defined(Matrix4_hpp) */
