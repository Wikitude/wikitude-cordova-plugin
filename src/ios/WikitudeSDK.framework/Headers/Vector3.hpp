//
//  Vector3.hpp
//  CommonLibrary
//
//  Created by Alexandru Florea on 30/11/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef Vector3_hpp
#define Vector3_hpp

#ifdef __cplusplus

#include <iostream>
#include <iomanip>

#include "CompilerAttributes.hpp"


namespace wikitude { namespace sdk {
    
    namespace impl {
        
        /**
         * A three component float based vector providing utility methods for working with and manipulating 3D vectors. Compatible with Matrix4.
         */
        class Matrix4;
        class WT_EXPORT_API Vector3
        {
        public:
            
            /**
             * Initializes the vector to 0.
             */
            Vector3();
            
            /**
             * Initializes the vector using a float pointer.
             *
             * @param src_ A pointer-to-float to be used to initialize the vector. The data pointed to is required to be at least 3 consecutive float values.
             */
            explicit Vector3(const float* const src_);
            
            /**
             * Initializes the vector using 3 distinct float values.
             *
             * @param x_ The float value to be applied to the x component.
             * @param y_ The float value to be applied to the y component.
             * @param z_ The float value to be applied to the z component.
             */
            Vector3(float x_, float y_, float z_);
            
            /**
             * Sets the vector using a float pointer.
             *
             * @param src_ A pointer-to-float to be used to initialize the vector. The data pointed to is required to be at least 3 consecutive float values.
             */
            void set(const float* const src_);
            
            /**
             * Sets the vector using 3 distinct float values.
             *
             * @param x_ The float value to be applied to the x component.
             * @param y_ The float value to be applied to the y component.
             * @param z_ The float value to be applied to the z component.
             */
            void set(float x_, float y_, float z_);
            
            /**
             * Provides a copy of a single value of the vector.
             *
             * @param index_ The zero based index specifying the component to be accessed. The index is required to be within the interval [0, 2].
             *
             * @return The copy of a value from the vector.
             */
            float operator[](int index_) const;
            
            /**
             * Provides a reference to a single value of the vector.
             *
             * @param index_ The zero based index specifying the component to be accessed. The index is required to be within the interval [0, 2].
             *
             * @return The reference to a value from the vector.
             */
            float& operator[](int index_);
            
            /**
             * Performs component-wise comparison of two vectors.
             *
             * @param rhs_ A reference to the vector this vector should be compared to.
             *
             * @return True if all the components are equal.
             */
            bool operator==(const Vector3& rhs_) const;
            
            /**
             * Performs component-wise addition between two vectors. The state of this vector is not changed. Returns a copy of the result.
             *
             * @param rhs_ A reference to the other operand.
             *
             * @return The sum of the two vectors.
             */
            Vector3 operator+(const Vector3& rhs_) const;
            
            /**
             * Adds another vector to this one. The state of this vector is changed. Returns a reference to itself.
             *
             * @param rhs_ A reference to the other operand.
             *
             * @return A reference to *this.
             */
            Vector3& operator+=(const Vector3& rhs_);
            
            /**
             * Adds a float value to each component of the vector. The state of this vector is not changed. Returns a copy of the result.
             *
             * @param rhs_ The float to be added.
             *
             * @return The sum between this vector and a scalar.
             */
            Vector3 operator+(const float rhs_) const;
            
            /**
             * Adds a float value to each component of this vector. The state of this vector is changed. Returns a reference to itself.
             *
             * @param rhs_ The float to be added.
             *
             * @return A reference to *this.
             */
            Vector3& operator+=(const float rhs_);
            
            /**
             * Performs component-wise subtraction between two vectors. The state of this vector is not changed. Returns a copy of the result.
             *
             * @param rhs_ A reference to the other operand.
             *
             * @return The difference between the two vectors.
             */
            Vector3 operator-(const Vector3& rhs_) const;
            
            /**
             * Subtracts another vector from this one. The state of this vector is changed. Returns a reference to itself.
             *
             * @param rhs_ A reference to the other operand.
             *
             * @return A reference to *this.
             */
            Vector3& operator-=(const Vector3& rhs_);
            
            /**
             * Subtracts a float value from each component of the vector. The state of this vector is not changed. Returns a copy of the result.
             *
             * @param rhs_ The float to be subtracted.
             *
             * @return The difference between this vector and a scalar.
             */
            Vector3 operator-(const float rhs_) const;
            
            /**
             * Subtracts a float value to each component of this vector. The state of this vector is changed. Returns a reference to itself.
             *
             * @param rhs_ The float to be subtracted.
             *
             * @return A reference to *this.
             */
            Vector3& operator-=(const float rhs_);
            
            /**
             * Multiplies a float value to each component of the vector. The state of this vector is not changed. Returns a copy of the result.
             *
             * @param rhs_ The float to be multiplied.
             *
             * @return The multiplication between this vector and a scalar.
             */
            Vector3 operator*(const float rhs_) const;
            
            /**
             * Multiplies a float value to each component of this vector. The state of this vector is changed. Returns a reference to itself.
             *
             * @param rhs_ The float to be multiplied.
             *
             * @return A reference to *this.
             */
            Vector3& operator*=(const float rhs_);
            
            /**
             * Divides each component of the vector by a float value. The state of this vector is not changed. Returns a copy of the result.
             *
             * @param rhs_ The float value by which the components should be divided.
             *
             * @return The division between this vector and a scalar.
             */
            Vector3 operator/(const float rhs_) const;
            
            /**
             * Divides each component of this vector by a float value. The state of this vector is changed. Returns a reference to itself.
             *
             * @param rhs_ The float value by which the components should be divided.
             *
             * @return A reference to *this.
             */
            Vector3& operator/=(const float rhs_);
            
            /**
             * Returns the magnitude, or length of this vector.
             *
             * @return The magnitude of the vector.
             */
            float getMagnitude() const;
            
            /**
             * Normalizes this vector, so that it has the same direction, but a magnitude of exactly 1.0. The state of this vector is changed. Returns a reference to itself.
             * If the magnitude of the vector is very close to 0, it sets the whole vector to exactly 0 instead of doing the normalization.
             *
             * @return A reference to *this.
             */
            Vector3& normalize();
            
            /**
             * Computes the dot product between two vectors.
             *
             * @param rhs_ A reference to the other operand.
             *
             * @return The dot product between the two vectors.
             */
            float dot(const Vector3& rhs_) const;
            
            /**
             * Computes the cross product between two vectors.
             *
             * @param rhs_ A reference to the other operand.
             *
             * @return The cross product between the two vectors.
             */
            Vector3 cross(const Vector3& rhs_) const;
            
            /**
             * Applies the transformation from a Matrix4 to this vector. The state of this vector is changed. Returns a reference to itself.
             * For the purpose of vector-matrix multiplication, this vector is consedered to be in the form of (x, y, z, 1), so tranlation is applied.
             * Perspective division is also applied automatically.
             *
             * @param transform_ The transformation that should be applied.
             *
             * @return A reference to *this.
             */
            Vector3& apply(const Matrix4& transform_);
            
            /**
             * A stream operator to allow convenient printing of the vector.
             *
             * @param os_ The stream to add the vector content to.
             * @param v_ The vector to add to the stream.
             *
             * @return The reference to the resulting stream.
             */
            friend WT_EXPORT_API std::ostream& operator<<(std::ostream& os_, const Vector3& v_);
            
        public:
            /**
             * The x or first component of the vector.
             */
            float x;
            
            /**
             * The y or second component of the vector.
             */
            float y;
            
            /**
             * The z or third component of the vector.
             */
            float z;
        };
    }
    using impl::Vector3;
}}

#endif /* __cplusplus */

#endif /* Vector3_hpp */
