//
//  ColorSpace.h
//  FoundationSDK
//
//  Created by Andreas Schacherbauer on 22/03/16.
//  Copyright © 2016 Wikitude. All rights reserved.
//

#ifndef ColorSpace_h
#define ColorSpace_h

#ifdef __cplusplus

#include "CompilerAttributes.hpp"


namespace wikitude { namespace sdk {

    namespace impl {


        enum WT_EXPORT_API ColorSpace {
            /**
             * Represents a color space where image data is given in a YUV 420 format, arranged to be compliant to the NV21 standard.
             * The data size is frame width * frame height * 3/2, meaning full luminance resolution and half the size for chroma red * chroma blue
             *
             * On iOS this is represented by the kCVPixelFormatType_420YpCbCr8BiPlanarFullRange constant
             * On Android this is represented by the ImageFormat.NV21 constant.
             */
            YUV_420_NV21,

            /**
             * Represents a color space where image data is given in a YUV 420 format, arranged to be compliant to the YV12 standard.
             * The data size is frame width * frame height * 3/2, meaning full luminance resolution and half the size for chroma red * chroma blue
             *
             * On Android this is represented by the ImageFormat.YV12 constants.
             */
            YUV_420_YV12,

            /**
             * Represents a color space where image data is given in a YUV 420 format, arranged in three planes.
             * The data data may contain a row stride for the luminance plane and pixel and row strides for the chroma planes.
             * The size of usable data is frame width * frame height * 3/2, meaning full luminance resolution and half the size for chroma red * chroma blue.
             *
             * On Android this is represented by the ImageFormat.YUV_420_888 constant.
             */
            YUV_420_888,

            /**
            * Represents a color space where image data is given in a YUV 420 format, arranged to be compliant to the NV12 standard.
            * The data size is frame width * frame height * 3/2, meaning full luminance resolution and half the size for chroma red * chroma blue
            * Chroma planes are interleaved.
            *
            * On Windows, this is represented by the BitmapPixelFormat::Nv12 constant.
            */
            YUV_420_NV12,

            /**
             * Represents a color space where image data is given in a RGB format.
             * The data size is frame width * frame height * 3 (R, G and B channel).
             *
             * On iOS this is represented by the kCVPixelFormatType_24RGB constant
             * On Android this is represented by the ImageFormat.FLEX_RGB_888 constant
             *
             * On iOS, it is not recommended to use this Color Space with Input Plugins when rendering with Metal because of additional overhead. 
             * If possible, please use RGBA instead.
             */
            RGB,
            
            /**
             * Represents a color space where image data is given in a RGBA format.
             * The data size is frame width * frame height * 4 (R, G, B and A channel).
             *
             * On iOS this is represented by the kCVPixelFormatType_32RGBA constant
             * On Android this is represented by the ImageFormat.FLEX_RGBA_8888 constant
             *
             * On iOS, when using Input Plugins and rendering with Metal, it is recommended to use this Color Space, instead of RGB.
             */
            RGBA,

            /**
            * Represents colorspace unknown by te SDK.
            */
            UNKNOWN
        };
    }
    using impl::ColorSpace;
}}

#endif /* __cplusplus */

#endif /* ColorSpace_h */
