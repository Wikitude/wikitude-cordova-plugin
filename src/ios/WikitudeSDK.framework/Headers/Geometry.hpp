//
//  Geometry.h
//
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#ifndef CommonLibrary_Rectangle_h
#define CommonLibrary_Rectangle_h

#ifdef __cplusplus

#include <iostream>
#include <iomanip>
#include <limits>


namespace wikitude { namespace sdk {

    template <typename T>
    struct Point {
        Point() : x(0), y(0) {}
        Point(T x_, T y_) : x(x_), y(y_) {}
        T x;
        T y;

        friend std::ostream& operator<<(std::ostream& os_, const Point& point_) {
            os_ << std::fixed << std::setprecision(3);
            os_ << "{" << std::setw(5) << point_.x << ", " << std::setw(5) << point_.y << "}";
            os_ << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
            return os_;
        }
    };
    
    template <typename T>
    struct Point3D {
        T x;
        T y;
        T z;
    };

    template <typename T>
    struct Size {
        Size() : width(0), height(0) {}
        Size(T width_, T height_) : width(width_), height(height_) {}

        T width;
        T height;

        bool operator==(const Size<T>& rhs_) {
            if ( width == rhs_.width && height == rhs_.height ) {
                return true;
            } else {
                return false;
            }
        }

        bool operator!=(const Size<T>& rhs_) {
            if ( width != rhs_.width && height != rhs_.height ) {
                return true;
            } else {
                return false;
            }
        }

        bool operator > (const Size<T>& rhs_) {
            if ( width > rhs_.width && height > rhs_.height ) {
                return true;
            } else {
                return false;
            }
        }

        friend std::ostream& operator<<(std::ostream& os_, const Size& size_) {
            os_ << std::fixed << std::setprecision(3);
            os_ << "{" << size_.width << ", " << size_.height << "}";
            os_ << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
            return os_;
        }
    };

    template <typename T>
    struct Rectangle {
        Rectangle() : origin({0, 0}), size(0, 0) {}
        Rectangle(Point<T> origin_, Size<T> size_) : origin(origin_), size(size_) {}

        Point<T>   origin;
        Size<T>    size;

        friend std::ostream& operator<<(std::ostream& os_, const Rectangle& rectangle_) {
            os_ << std::fixed << std::setprecision(3);
            os_ << "{{" << std::setw(5) << rectangle_.origin.x << ", " << std::setw(5) << rectangle_.origin.y << "}, {" << std::setw(5) << rectangle_.size.width << ", " << std::setw(5) << rectangle_.size.height << "}}";
            os_ << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
            return os_;
        }
    };

    template<typename T>
    struct Rectangle3D {
        Point3D<T>  min;
        Point3D<T>  max;
    };

    template <typename T>
    struct Scale2D {
        Scale2D()
        :
        x(0),
        y(0)
        { /* Intentionally Left Blank */ }

        Scale2D(T x_, T y_)
        :
        x(x_),
        y(y_)
        { /* Intentionally Left Blank */ }

        friend std::ostream& operator<<(std::ostream& os_, const Scale2D& scale_) {
            os_ << std::fixed << std::setprecision(3);
            os_ << "{" << std::setw(5) << scale_.x << ", " << std::setw(5) << scale_.y << "}";
            os_ << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
            return os_;
        }

        T x;
        T y;
    };

    template<typename T>
    bool isScale2DContainingPositiveAndValidValues(const Scale2D<T>& scale_) {
        if ( scale_.x <= 0 || scale_.y <= 0 ) {
            return false;
        }
        if ( scale_.x == std::numeric_limits<T>::infinity() || scale_.y == std::numeric_limits<T>::infinity() ) {
            return false;
        }
        if ( scale_.x == std::numeric_limits<T>::quiet_NaN() || scale_.y == std::numeric_limits<T>::quiet_NaN() ) {
            return false;
        }
        return true;
    }
    
    template <typename T>
    struct Scale3D {
        Scale3D()
            :
            x(0),
            y(0),
            z(0)
        { /* Intentionally Left Blank */
        }

        Scale3D(T x_, T y_, T z_)
            :
            x(x_),
            y(y_),
            z(z_)
        { /* Intentionally Left Blank */
        }

        friend std::ostream& operator<<(std::ostream& os_, const Scale3D& scale_) {
            os_ << std::fixed << std::setprecision(3);
            os_ << "{" << std::setw(5) << scale_.x << ", " << std::setw(5) << scale_.y << ", " << std::setw(5) << scale_.z << "}";
            os_ << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
            return os_;
        }

        T x;
        T y;
        T z;
    };

    template <typename T>
    bool operator==(const Scale3D<T>& a, const Scale3D<T>& b) {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
    
    template <typename T>
    struct Extent {
        Extent()
        :
        min(0),
        max(0)
        { /* Intentionally Left Blank */ }
        
        Extent(T min_, T max_)
        :
        min(min_),
        max(max_)
        { /* Intentionally Left Blank */ }

        Extent(const Extent& extent_)
        :
        min(extent_.min),
        max(extent_.max)
        { /* Intentionally Left Blank */ }
        
        friend std::ostream& operator<<(std::ostream& os_, const Extent& extent_) {
            os_ << std::fixed << std::setprecision(3);
            os_ << "{" << std::setw(5) << extent_.min << ", " << std::setw(5) << extent_.max << "}";
            os_ << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
            return os_;
        }

        T min;
        T max;
    };

    template <typename T>
    bool operator==(const Extent<T>& a, const Extent<T>& b) {
        return a.min == b.min && a.max == b.max;
    }
}}

#endif /* __cplusplus */

#endif
