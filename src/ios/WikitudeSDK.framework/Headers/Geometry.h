//
//  Rectangle.h
//
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#ifndef CommonLibrary_Rectangle_h
#define CommonLibrary_Rectangle_h

#ifdef __cplusplus


namespace wikitude { namespace sdk {

    template <typename T>
    struct Point {
        T x;
        T y;
    };

    template <typename T>
    struct Size {
        T width;
        T height;
    };

    template <typename T>
    struct Rectangle {
        Point<T>   origin;
        Size<T>    size;
    };

    template <typename T>
    struct Scale2D {
        T x;
        T y;
    };
    
    template <typename T>
    struct Scale3D {
        T x;
        T y;
        T z;
    };
}}

#endif /* __cplusplus */

#endif
